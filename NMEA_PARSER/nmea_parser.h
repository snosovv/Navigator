#pragma once

struct gps_info
{
  /*lattitude */
  long lat;  
  /*longitude */
  long lon;
  /* visota */
  short alt;
  /* gsp speed in km/h */
  unsigned long speed;
  /* date 6 byte */
  char date[3];  
  /* time in gps format */
  char time[3];
  /* GPS info is valid ? */
  char loc_valid;
  /* sats count */
  char sats;
  char sats_track;
  unsigned char hdop;
  short course;
};

extern struct gps_info loc_current;

uint32_t __stdcall nmea_processor( char c );


uint8_t nmea_glonass_sats( void );
uint8_t nmea_gps_sats( void );
uint32_t nmea_valid_msg( int reset );

