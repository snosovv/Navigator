#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "nmea_parser.h"

/* DEFS */
#define NMEA_TOK_SIZE 16

#define MSG_TYPE_RMC    1
#define MSG_TYPE_GGA    2
#define MSG_TYPE_GSV    4
#define MSG_TYPE_UNK    255

static uint32_t valid_messages = 0;
static uint8_t sync_start = 0;
static int offset = 0;
static char tok_id = 0;
static char token[NMEA_TOK_SIZE+1];
static uint8_t nmea_crc1 = '$';
static uint8_t nmea_crc2 = 0;
static uint8_t msg_type = 0;

static struct gps_info loc_tmp = {0};
struct gps_info loc_current = {0};

/* PROTOS */
static uint8_t hex2val(char a);
static uint8_t stou8( char *s );

/* for 128 sats, 1 bit per sat */
uint8_t sats_id_list_active[16] = { 0 };
uint8_t sats_id_list[16] = { 0 };
uint8_t sat_id_0 = 0;
uint8_t sat_id_1 = 0;
uint8_t sat_id_2 = 0;
uint8_t sat_id_3 = 0;
uint8_t max_sat = 0;

uint32_t nmea_valid_msg( int reset )
{
  uint32_t t = valid_messages;
  if( reset )
  {
    valid_messages = 0;
    memset( sats_id_list_active, 0x00, sizeof( sats_id_list_active ) );
    memset( sats_id_list, 0x00, sizeof( sats_id_list ) ); 
    memset( &loc_current, 0x00, sizeof( struct gps_info ) );
  }
  return t;
}

uint8_t nmea_glonass_sats( void )
{
  uint8_t n;
  uint8_t sats = 0;
  /* glonass ids 66-85 */
  for( n = 66; n < 128; ++n )
  {
    if( sats_id_list_active[n>>3] & (1<<(n&0x07)) )
    {
      ++sats;
    }
  }
  return sats;
}

uint8_t nmea_gps_sats( void )
{
  uint8_t n;
  uint8_t sats = 0;
  /* gps ids 1-32 */
  for( n = 1; n < 33; ++n )
  {
    if( sats_id_list_active[n>>3] & (1<<(n&0x07)) )
    {
      ++sats;
    }
  }
  return sats;  
}

static uint8_t nmea_process_token( int id, char *t )
{
  /* ident token type */
  if(id == 0)
  {  
    if( t[3] == 'G' )
    {
      if( t[4] == 'G' && t[5] == 'A'  )
      {
        return MSG_TYPE_GGA;
      }
      else if( t[4] == 'S' && t[5] == 'V' )
      {
        return MSG_TYPE_GSV;
      }
    }
    else if( t[3] == 'R' && t[4] == 'M' && t[5] == 'C' )
    {
      return MSG_TYPE_RMC;
    }
    return MSG_TYPE_UNK;    
  }
  /* we do not know this token */
  if( msg_type == MSG_TYPE_UNK )
    return MSG_TYPE_UNK; 
  
  switch( msg_type )
  {
    case MSG_TYPE_GGA:
    if( id == 1 )
    /* time  */
    {
      ;
    }   
    else if( id == 7 )
    /* number of satellites */
    {
      loc_tmp.sats = atol( t );  
    }
    else if( id == 8 )
    /* hdop */
    {
      loc_tmp.hdop = (long)(atof( t )*10);   
    }
    else if( id == 9 )
    /* altitude */
    {
      loc_tmp.alt = atol( t );  
    }
    break;
    case MSG_TYPE_GSV:
      /* message id */
      if( id == 2 )
      {
        uint8_t msg_id = atoi( t );
        if( msg_id == 1 )
        {
          if( max_sat & 1 )
          {
            memcpy( sats_id_list_active, sats_id_list, sizeof( sats_id_list ) );
          }
          ++max_sat;
        }
      }
      else if( id == 3 )
      /* number of satellites in view */
      {
        loc_tmp.sats_track = atol( t );
      }
      /* SV PRN #*/
      else if( id == 4 )
      {
        sat_id_0 = atoi( t );
      }
      else if( id == 8 )
      {
        sat_id_1 = atoi( t );
      }
      else if( id == 12 )
      {
        sat_id_2 = atoi( t );
      }
      else if( id == 16 )
      {
        sat_id_3 = atoi( t );
      }
    break;
    case MSG_TYPE_RMC:
    if( id == 1 )
    /* time  */
    {
      /* second */
      loc_tmp.time[2] = stou8( &t[4] );
      /* minute */
      loc_tmp.time[1] = stou8( &t[2] );
      /* hour */
      loc_tmp.time[0] = stou8( &t[0] );
    }   
    else if( id == 2 )
    /* A=active, V=void */
    {
      loc_tmp.loc_valid = (t[0] == 'A');   
    } 
    else if( id == 3 )
    /* latitude */
    {
      double lat = atof( t );
      loc_tmp.lat = ((unsigned long)(lat*10000) % 1000000)*100/6 +((unsigned long)(lat/100)*10000000); 
    } 
    else if( id == 4 )
    /* n/s */
    {
      if( t[0] == 'S' )
      {
        loc_tmp.lat  = -loc_tmp.lat; 
      }
    } 
    else if( id == 5 )
    /* longitude */
    {
      double lon = atof( t );
      loc_tmp.lon = ((unsigned long)(lon*10000) % 1000000)*100/6 +((unsigned long)(lon/100)*10000000);
    } 
    else if( id == 6 )
    /* e/w */
    {
      if( t[0] == 'W' )
      {
        loc_tmp.lon  = -loc_tmp.lon; 
      }
    } 
    else if( id == 7 )
    /* speed over ground in knots */
    {
      loc_tmp.speed = (long)(atol(t) * 1.85200);   
    } 
    else if( id == 8 )
    /* track angle */
    {
      loc_tmp.course = atoi( t );   
    } 
    else if( id == 9 )
    /* date (DDMMYY) */
    {
      /* yy */
      loc_tmp.date[2] = stou8( &t[4] );
      /* mon */
      loc_tmp.date[1] = stou8( &t[2] );
      /* day */
      loc_tmp.date[0] = stou8( &t[0] );
    } 
    break;
  }
  
  return msg_type;
}

uint32_t __stdcall nmea_processor( char c )
{

  if( sync_start == 0 )
  {
    if( c == '$' )
      sync_start = 1;
    else if( c != '\n' )
	  return valid_messages;
  }
  switch(c)
  {
    case '\r':
      break;
    case '\n':  
      if( sync_start && (nmea_crc1 == nmea_crc2) )
      {
		  ++valid_messages;
          if( (msg_type == MSG_TYPE_RMC) )
          {
              loc_current = loc_tmp;
          }
          if( msg_type == MSG_TYPE_GSV )
          {
            /* calculate sat pos in table */
            sats_id_list[(sat_id_0>>3)] |= (1<<(sat_id_0&7));
            sats_id_list[(sat_id_1>>3)] |= (1<<(sat_id_1&7));
            sats_id_list[(sat_id_2>>3)] |= (1<<(sat_id_2&7));
            sats_id_list[(sat_id_3>>3)] |= (1<<(sat_id_3&7));
            sat_id_0 = 0;
            sat_id_1 = 0;
            sat_id_2 = 0;
            sat_id_3 = 0;
          }
      }
      sync_start = 0;
      nmea_crc2 = 0;
      nmea_crc1 = '$';
      offset = 0;
      tok_id = 0;
      msg_type = MSG_TYPE_UNK;   
    break;
    case '*':  
      nmea_crc2 = 1;
      nmea_crc1^=c;
    case ',':
      token[offset] = '\0';
      offset = 0;
      msg_type = nmea_process_token( tok_id, token );
      if( msg_type == MSG_TYPE_UNK )
      {
        sync_start = 0;
        nmea_crc1 = '$';
        break;
      }
      nmea_crc1^=c; /* remove crc from * sym */
      ++tok_id;  
    break;
    default:
      if( nmea_crc2 )
      {
        nmea_crc2 = (nmea_crc2<<4) | hex2val(c); 
      }
      else if( offset < (NMEA_TOK_SIZE) )
      {
        nmea_crc1^=c;
        token[offset++] = c;
      }
  }
  return valid_messages;
}


static uint8_t hex2val(char a)
{
  return ( a > '9') ?(a & 0xDFu ) - 0x37u: (a - '0');
}

/* no params was cheked ! b c */
/* convert 2bytes from accsii to u8 */
static uint8_t stou8( char *s ) 
{
  uint8_t tmp;
  tmp = *s-'0';
  ++s;
  tmp = (tmp<<3)+(tmp<<1);
  tmp+= (*s-'0');
  return tmp;
}
