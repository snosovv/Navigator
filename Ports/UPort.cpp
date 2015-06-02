//---------------------------------------------------------------------------

#include <vcl.h>
#include <registry.hpp>
#pragma hdrstop

#include "UPort.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPorts *FormPorts;
//---------------------------------------------------------------------------
__fastcall TFormPorts::TFormPorts(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFormPorts::ttitt(TObject *Sender)
{
 TRegistry* Reg = new TRegistry;
 TStringList *List = new TStringList;
 int i;

 Reg->RootKey = HKEY_LOCAL_MACHINE;
 Reg->OpenKey("HARDWARE\\DEVICEMAP\\SERIALCOMM", false);
 Reg->GetValueNames(List);
 for (i = 0; i< List->Count; i++)
 {
  AnsiString w = Reg->ReadString(List->Strings[i]).SetLength(3);
  if (w.SetLength(3) == "COM")
     ComboBox1->Items->Add(Reg->ReadString(List->Strings[i]));
 }
 List->Free();
 Reg->CloseKey();
 Reg->Free();
 ComboBox1->ItemIndex = 0;
 port = 0;

 Overlapp.Internal = 0;
 Overlapp.InternalHigh = 0;
 Overlapp.Offset = 0;
 Overlapp.OffsetHigh = 0;
 Overlapp.hEvent = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormPorts::FormClose(TObject *Sender, TCloseAction &Action)
{
 if (port != 0)
 {
	 CloseHandle(port);
	 port = 0;
 }

}
//---------------------------------------------------------------------------

void __fastcall TFormPorts::Button1Click(TObject *Sender)
{
 if (port == 0)
		 port = CreateFile(("\\\\.\\"+ComboBox1->Text).c_str(),
                         GENERIC_READ | GENERIC_WRITE, 0,
                         NULL, OPEN_EXISTING, 0, 0);
 if(! GetCommState(port, &lpDCB))
 {
	if(Device == GPS)	
		ShowMessage("Не удалось открыть порт " + ComboBox1->Text + " для GPS/GLONASS");
	else if(Device == CMPS)
		ShowMessage("Не удалось открыть порт " + ComboBox1->Text + " для компаса");
   exit;
  }

 CBBaudRate->ItemIndex = CBBaudRate->Items->IndexOf(
                                      IntToStr((int)lpDCB.BaudRate));
 CBParity->ItemIndex = lpDCB.Parity;
 CBByteSize->ItemIndex = lpDCB.ByteSize - 4;
 CBStopBits->ItemIndex = lpDCB.StopBits;
 GetCommTimeouts(port, &lpCommTimeouts);
 EReadIntervalTimeout->Text = IntToStr((int)lpCommTimeouts.ReadIntervalTimeout);
 EReadTotalTimeoutMultiplier->Text = IntToStr((int)lpCommTimeouts.ReadTotalTimeoutMultiplier);
 EReadTotalTimeoutConstant->Text = IntToStr((int)lpCommTimeouts.ReadTotalTimeoutConstant);
 EWriteTotalTimeoutMultiplier->Text = IntToStr((int)lpCommTimeouts.WriteTotalTimeoutMultiplier);
 EWriteTotalTimeoutConstant->Text = IntToStr((int)lpCommTimeouts.WriteTotalTimeoutConstant);
 Button2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPorts::Button2Click(TObject *Sender)
{
	lpDCB.BaudRate = StrToInt(CBBaudRate->Text);
	lpDCB.ByteSize = CBByteSize->ItemIndex + 4;
	lpDCB.Parity = CBParity->ItemIndex;
	lpDCB.StopBits = CBStopBits->ItemIndex;


	if (!SetCommState(port, &lpDCB))
	{
		if( Device == GPS)
			ShowMessage("Значения параметров COM порта для GPS/GLONASS недопустимые\n"
									 "Установка не произведена");
		else if (Device == CMPS)
			ShowMessage("Значения параметров COM порта для компаса недопустимые\n"
									 "Установка не произведена");

		Button1Click(Sender);
		exit;
	}

	try
	{
		lpCommTimeouts.ReadIntervalTimeout = StrToInt(EReadIntervalTimeout->Text);
		lpCommTimeouts.ReadTotalTimeoutMultiplier = StrToInt(EReadTotalTimeoutMultiplier->Text);
		lpCommTimeouts.ReadTotalTimeoutConstant = StrToInt(EReadTotalTimeoutConstant->Text);
		lpCommTimeouts.WriteTotalTimeoutMultiplier = StrToInt(EWriteTotalTimeoutMultiplier->Text);
		lpCommTimeouts.WriteTotalTimeoutConstant = StrToInt(EWriteTotalTimeoutConstant->Text);
	}
	catch(EConvertError&)
	{
		if( Device == GPS)
			ShowMessage("Ошибочное значение временного интервала COM порта для GPS/GLONASS недопустимые\n"
									 "Установка не произведена");
		else if (Device == CMPS)
			ShowMessage("Ошибочное значение временного интервала COM порта для компаса недопустимые\n"
									 "Установка не произведена");
		exit;
	}

	if (!SetCommTimeouts(port, &lpCommTimeouts))
	{
		if( Device == GPS)
			ShowMessage("Значения временных параметров COM порта для GPS/GLONASS недопустимые\n"
									 "Установка не произведена");
		else if (Device == CMPS)
			ShowMessage("Значения временных параметров COM порта для компаса недопустимые\n"
									 "Установка не произведена");
		Button1Click(Sender);
		exit;
	}


	Button1Click(Sender);
	if(Sender == Button2)
	{

		if(Device == GPS)
			WriteSeting("GPS");
		else
			WriteSeting("CMPS");
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormPorts::ComboBox1CloseUp(TObject *Sender)
{
	Button2->Enabled = false;

	if (port != 0)
	{
		CBBaudRate->ItemIndex = -1;
		CBByteSize->ItemIndex = -1;
		CBParity->ItemIndex = -1;
		CBStopBits->ItemIndex = -1;
		EReadIntervalTimeout->Text = "";
		EReadTotalTimeoutMultiplier->Text = "";
		EReadTotalTimeoutConstant->Text = "";
		EWriteTotalTimeoutMultiplier->Text = "";
		EWriteTotalTimeoutConstant->Text = "";
		CloseHandle(port);
		port = 0;

		Button1Click(NULL);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormPorts::FormShow(TObject *Sender)
{
	if(Device == GPS)
		ReadSeting("GPS");
	else
		ReadSeting("CMPS");

	Button1Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormPorts::PortOpen(void)
{
	if (port != 0)
		PortClose();

	if (port == 0)
		 port = CreateFile(
												("\\\\.\\"+ComboBox1->Text).c_str(),
												GENERIC_READ | GENERIC_WRITE,
												0,
												NULL,
												OPEN_EXISTING,
												FILE_FLAG_OVERLAPPED,
												0);
	if(! GetCommState(port, &lpDCB))
	{
		if(Device == GPS)
			ShowMessage("Не удалось открыть порт " + ComboBox1->Text + " GPS/GLONASS");
		else if(Device == CMPS)
			ShowMessage("Не удалось открыть порт " + ComboBox1->Text + " компаса");
		exit;
	}

	lpDCB.BaudRate = StrToInt(CBBaudRate->Text);
	lpDCB.ByteSize = CBByteSize->ItemIndex + 4;
	lpDCB.Parity = CBParity->ItemIndex;
	lpDCB.StopBits = CBStopBits->ItemIndex;

	if (!SetCommState(port, &lpDCB))
	{
		if(Device == GPS)
			ShowMessage("Значения параметров COM порта GPS/GLONASS недопустимые\n"
								 "Установка не произведена");
		else if(Device == CMPS)
			ShowMessage("Значения параметров COM порта компаса недопустимые\n"
								 "Установка не произведена");
								 
		exit;
	}

	try
	{
		lpCommTimeouts.ReadIntervalTimeout = StrToInt(EReadIntervalTimeout->Text);
		lpCommTimeouts.ReadTotalTimeoutMultiplier = StrToInt(EReadTotalTimeoutMultiplier->Text);
		lpCommTimeouts.ReadTotalTimeoutConstant = StrToInt(EReadTotalTimeoutConstant->Text);
		lpCommTimeouts.WriteTotalTimeoutMultiplier = StrToInt(EWriteTotalTimeoutMultiplier->Text);
		lpCommTimeouts.WriteTotalTimeoutConstant = StrToInt(EWriteTotalTimeoutConstant->Text);
	}
	catch(EConvertError&)
	{
		if(Device == GPS)
			ShowMessage("Ошибочное значение временного интервала COM порта GPS/GLONASS.\n Установка не произведена");
		else if(Device == CMPS)
			ShowMessage("Ошибочное значение временного интервала COM порта компаса.\n Установка не произведена");
		exit;
	}

	if (!SetCommTimeouts(port, &lpCommTimeouts))
	{
		if(Device == GPS)
			ShowMessage("Значения временных параметров COM порта GPS/GLONASS недопустимые\n Установка не произведена");
		else if(Device == CMPS)
			ShowMessage("Значения временных параметров COM порта компаса недопустимые\n Установка не произведена");
					
		exit;
	}
}


void __fastcall TFormPorts::PortClose(void)
{
 TimerRead->Enabled = false;

 if (port != 0)
 {
	 CloseHandle(port);
	 port = 0;
 }
}

void __fastcall TFormPorts::PortRead(void)
{
	DWORD n;

	buf = "";

	FlushFileBuffers(port);
	if(ReadFile(port, buf.c_str(), 8, &n, &Overlapp) != 0);
//  	Form1->MemoAll->Lines->Add(buf);


	if(GetLastError() != ERROR_IO_PENDING)
	{
		if(Device == GPS)
			ShowMessage("Ошибка чтения данных из порта GPS/GLONASS");
		if(Device == CMPS)
			ShowMessage("Ошибка чтения данных из порта компаса");
	}
	else
		TimerRead->Enabled = true;
}

void __fastcall TFormPorts::PortWrite(AnsiString s)
{
	DWORD n;

	FlushFileBuffers(port);
	WriteFile(port, s.c_str(), strlen(s.c_str()), &n, &Overlapp);

	if(GetLastError() != ERROR_IO_PENDING)
	{
		if(Device == GPS)
			ShowMessage("Ошибка записи в порт данных GPS/GLONASS");
		if(Device == CMPS)
			ShowMessage("Ошибка записи в порт данных компаса");
	}
	else
		TimerWrite->Enabled = true;
}



void __fastcall TFormPorts::TimerWriteTimer(TObject *Sender)
{
	DWORD n;

	if(GetOverlappedResult(port, &Overlapp, &n, false))
	{
//		Form1->MemoAll->Lines->Add("Переданны новые данные - " + IntToStr(n) + " байт");
//		Form1->MemoAll->Lines->Add(buf);
		TimerWrite->Enabled = false;
	}
	else
	{
//		Form1->MemoAll->Lines->Add("Идет передача данных");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormPorts::TimerReadTimer(TObject *Sender)
{
	DWORD n;

	if(GetOverlappedResult(port, &Overlapp, &n, false))
	{
//		Form1->MemoAll->Lines->Add("Приняты новые данные - " + IntToStr(n) + " байт");
//		Form1->MemoAll->Lines->Add(buf);
		TimerRead->Enabled = false;
		PortRead();
	}
	else
	{
//		Form1->MemoAll->Lines->Add("Идет прием данных");
	}
}
//---------------------------------------------------------------------------


HANDLE __fastcall TFormPorts::SerialOpenPort(HANDLE hPort, UnicodeString port )
{
	hPort = CreateFile( port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0,
		OPEN_EXISTING, 0, 0);

	return hPort;
}

void __fastcall TFormPorts::SerialClosePort( HANDLE hPort )
{
	if (hPort != 0)
	{
		CloseHandle(hPort);
		port = 0;
 	}
}

void __fastcall TFormPorts::SerialSetBaud( HANDLE hPort, long lRate, int hwflow )
{
	DCB dcb;

	//
	// Purge any pending characters in the serial port.
	//
	PurgeComm( hPort, (PURGE_TXABORT | PURGE_RXABORT |
		PURGE_TXCLEAR | PURGE_RXCLEAR));

	//
	// Fill in the device control block.
	//
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = lRate;
	dcb.fBinary = TRUE;
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	if( hwflow ){
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
	}else{
		dcb.fDtrControl = DTR_CONTROL_DISABLE;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
	}
	dcb.fDsrSensitivity = FALSE;
	dcb.fTXContinueOnXoff = TRUE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;
	dcb.fAbortOnError = FALSE;
	dcb.XonLim = 0;
	dcb.XoffLim = 0;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.XonChar = 17;
	dcb.XoffChar = 19;
	dcb.ErrorChar = 0;
	dcb.EofChar = 0;
	dcb.EvtChar = 0;
	dcb.wReserved1 = 0;

	//
	// Set the new serial port configuration.
	//
	SetCommState( hPort, &dcb);
}

int __fastcall TFormPorts::SerialReceiveChar( HANDLE hPort,long lTimeout)
{
	COMMTIMEOUTS sTimeouts;
	int cChar;
	DWORD dwLen;

	sTimeouts.ReadIntervalTimeout = 0;
	sTimeouts.ReadTotalTimeoutMultiplier = 0;
	sTimeouts.ReadTotalTimeoutConstant = lTimeout;
	sTimeouts.WriteTotalTimeoutMultiplier = 0;
	sTimeouts.WriteTotalTimeoutConstant = 0;

	SetCommTimeouts(hPort, &sTimeouts);

	cChar = 0;
	if(!ReadFile(hPort, &cChar, 1, &dwLen, NULL))
		cChar = -1;

	if(dwLen != 1)
		cChar = -1;

	return cChar;
}

int __fastcall TFormPorts::SerialReceiveBuffer( HANDLE hPort, char *pcBuf, int len, long lTimeout)
{
	COMMTIMEOUTS sTimeouts;
	DWORD dwLen;

	sTimeouts.ReadIntervalTimeout = 0;
	sTimeouts.ReadTotalTimeoutMultiplier = 0;
	sTimeouts.ReadTotalTimeoutConstant = lTimeout;
	sTimeouts.WriteTotalTimeoutMultiplier = 0;
	sTimeouts.WriteTotalTimeoutConstant = 0;

	SetCommTimeouts(hPort, &sTimeouts);

	if(!ReadFile(hPort, pcBuf, len, &dwLen, NULL))
		return -1;

	if(dwLen == 0 )
		return 0;

/*
	if(dwLen != len )
		return -1;
*/

	return dwLen;
}

int __fastcall TFormPorts::SerialWriteChar( HANDLE hPort, char cChar )
{
	DWORD dwLen;
	if(!WriteFile(hPort, &cChar, 1, &dwLen, NULL))
		cChar = -1;

	if(dwLen != 1)
		cChar = -1;

	return cChar;
}

int __fastcall TFormPorts::SerialWriteBuffer( HANDLE hPort, char *pcBuf, int len )
{
	DWORD dwLen;
	if(!WriteFile(hPort, pcBuf, len, &dwLen, NULL))
		return -1;

	if( (int)dwLen != len )
		return -1;

	return len;
}

void __fastcall TFormPorts::ReadSeting( UnicodeString Dev)
{
	TIniFile *ini = new TIniFile (ExtractFilePath(Application->ExeName) + "setting.ini");
		ComboBox1->ItemIndex = ComboBox1->Items->IndexOf(ini->ReadString(Dev, "COM_PORT", "COM1"));
		Button1Click(NULL);
		CBBaudRate->ItemIndex = ini->ReadInteger(Dev, "CBBaudRate", 0);
		CBParity->ItemIndex = ini->ReadInteger(Dev, "CBParity", 0);
		CBByteSize->ItemIndex = ini->ReadInteger(Dev, "CBByteSize", 0);
		CBStopBits->ItemIndex = ini->ReadInteger(Dev, "CBStopBits", 0);
		EReadIntervalTimeout->Text = ini->ReadString(Dev, "EReadIntervalTimeout", "");
		EReadTotalTimeoutMultiplier->Text = ini->ReadString(Dev, "EReadTotalTimeoutMultiplier", "");
		EReadTotalTimeoutConstant->Text = ini->ReadString(Dev, "EReadTotalTimeoutConstant", "");
		EWriteTotalTimeoutMultiplier->Text = ini->ReadString(Dev, "EWriteTotalTimeoutMultiplier", "");
		EWriteTotalTimeoutConstant->Text = ini->ReadString(Dev, "EWriteTotalTimeoutConstant", "");
	delete ini;
}

void __fastcall TFormPorts::WriteSeting( UnicodeString Dev)
{
	TIniFile *ini = new TIniFile (ExtractFilePath(Application->ExeName) + "setting.ini");
		ini->WriteString(Dev, "COM_PORT", ComboBox1->Items->Strings[ComboBox1->ItemIndex]);
		ini->WriteInteger(Dev, "CBBaudRate", CBBaudRate->ItemIndex);
		ini->WriteInteger(Dev, "CBParity", CBParity->ItemIndex);
		ini->WriteInteger(Dev, "CBByteSize", CBByteSize->ItemIndex);
		ini->WriteInteger(Dev, "CBStopBits", CBStopBits->ItemIndex);
		ini->WriteString(Dev, "EReadIntervalTimeout", EReadIntervalTimeout->Text);
		ini->WriteString(Dev, "EReadTotalTimeoutMultiplier", EReadTotalTimeoutMultiplier->Text);
		ini->WriteString(Dev, "EReadTotalTimeoutConstant", EReadTotalTimeoutConstant->Text);
		ini->WriteString(Dev, "EWriteTotalTimeoutMultiplier", EWriteTotalTimeoutMultiplier->Text);
		ini->WriteString(Dev, "EWriteTotalTimeoutConstant", EWriteTotalTimeoutConstant->Text);
	delete ini;
}
