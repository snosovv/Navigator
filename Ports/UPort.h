//---------------------------------------------------------------------------

#ifndef UPortH
#define UPortH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "Unit1.h"

enum DeviceType
{
	GPS, CMPS
};

//---------------------------------------------------------------------------
class TFormPorts : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TComboBox *ComboBox1;
    TLabel* Label5;
    TGroupBox* GroupBox1 ;
    TComboBox* CBBaudRate;
    TLabel* Label1;
    TLabel* Label3;
    TComboBox* CBByteSize;
    TLabel* Label2;
    TComboBox* CBParity;
    TLabel* Label4;
    TComboBox* CBStopBits;
    TGroupBox* GroupBox2;
    TLabel* Label6;
    TLabel* Label7;
    TEdit* EReadIntervalTimeout;
    TEdit* EReadTotalTimeoutMultiplier;
    TLabel* Label10;
    TEdit* EReadTotalTimeoutConstant;
    TLabel* Label9;
    TLabel* Label11;
    TEdit* EWriteTotalTimeoutConstant;
    TEdit* EWriteTotalTimeoutMultiplier;
    TLabel* Label8;
    TLabel* Label12;
    TButton* Button2;
	TTimer *TimerWrite;
	TTimer *TimerRead;
        void __fastcall ttitt(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall ComboBox1CloseUp(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TimerWriteTimer(TObject *Sender);
	void __fastcall TimerReadTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
				__fastcall TFormPorts(TComponent* Owner);

				void __fastcall PortOpen(void);
				void __fastcall PortClose(void);
				void __fastcall PortRead(void);
				void __fastcall PortWrite(AnsiString);

				HANDLE port;
				TDCB lpDCB;
				TCommTimeouts lpCommTimeouts;
				TOverlapped Overlapp;
				AnsiString buf;

				HANDLE __fastcall SerialOpenPort( HANDLE hPort, UnicodeString port);
				void __fastcall SerialClosePort( HANDLE );
				void __fastcall SerialSetBaud( HANDLE hPort, long lRate, int hwflow );
				int __fastcall SerialReceiveChar( HANDLE hPort,long lTimeout);
				int __fastcall SerialReceiveBuffer( HANDLE hPort, char *pcBuf, int len, long lTimeout);
				int __fastcall SerialWriteChar( HANDLE hPort, char cChar );
				int __fastcall SerialWriteBuffer( HANDLE hPort, char *pcBuf, int len );

				void __fastcall ReadSeting( UnicodeString );
				void __fastcall WriteSeting( UnicodeString );

				DeviceType Device;


};
//---------------------------------------------------------------------------
extern PACKAGE TFormPorts *FormPorts;
//---------------------------------------------------------------------------
#endif
