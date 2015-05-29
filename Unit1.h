//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "mapcmp.hpp"
#include "mapviewa.hpp"
#include "mapwina.hpp"
#include "mapdialg.hpp"
#include <Vcl.Dialogs.hpp>
#include "mapcompa.hpp"
#include "mappoint.hpp"
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <math.h>
#include <stdio.h>
#include <IniFiles.hpp>

#include "UPort.h"

#include "NMEA_PARSER/nmea_parser.h"
#include <VCLTee.TeeDraw3D.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "mDialog.hpp"
#include "mdlgsher.hpp"
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
#include "mapscrn.hpp"

typedef struct DOUBLEPOINT   // КООРДИНАТЫ ТОЧКИ (ПЛАВАЮЩАЯ МЕТРИКА)
{
#ifdef __cplusplus           // 11/04/01
	union { double x; double X; };
	union { double y; double Y; };

	void operator  = (double value)  {         x  = value;   y  = value;  }
	 int operator != (double value)  { return (x != value || y != value); }
	 int operator == (double value)  { return (x == value && y == value); }
#else
	double X;
	double Y;
#endif
}
	DOUBLEPOINT;


#define DegToRad 0.017453292519943295769236907684886
#define PI 3.1415926535897932384626433832795

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TOpenMapDialog *OpenMapDialog;
	TMainMenu *MainMenu1;
	TMenuItem *Seting;
	TMenuItem *COMPort1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMapPoint *axMapPointPictureToGeo;
	TMapPoint *axMapPointGeoToPicture;
	TMapPoint *axMapPointGeoToPlane;
	TMapPoint *axMapPointPlaneToGeo;
	TMapPoint *axMapPointPictureToPlane;
	TMapPoint *axMapPointPlaneToPicture;
	TPanel *Panel1;
	TPanel *Scalle;
	TLabel *LBLL;
	TMenuItem *COMCMPS1;
	TMenuItem *COMGPS1;
	TMenuItem *SettingCOMGPS;
	TMenuItem *OpenCOMGPS;
	TMenuItem *CloseCOMGPS;
	TMenuItem *SettingCOMCMPS;
	TMenuItem *OpenCOMCMPS;
	TMenuItem *CloseCOMCMPS;
	TLabel *validMessage;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TMapView *MapView;
	TDraw3D *Draw3D1;
	TLabel *Label13;
	TLabel *Label15;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TCheckBox *CheckBox1;
	TEdit *Elevation;
	TEdit *FontZoom;
	TEdit *HorizOffset;
	TEdit *OrthoAngle;
	TCheckBox *Orthogonal;
	TEdit *Perspective;
	TEdit *Rotation;
	TEdit *Tilt;
	TEdit *VertOffset;
	TEdit *Zoom;
	TButton *Button4;
	TCheckBox *CheckBoxDrawRoom;
	TCheckBox *CheckBoxGradient;
	TCheckBox *CheckBoxDrawAxes;
	TTrackBar *TrackBarZoom;
	TTrackBar *TrackBarVertOffset;
	TTrackBar *TrackBarTilt;
	TTrackBar *TrackBarRotation;
	TTrackBar *TrackBarPerspective;
	TTrackBar *TrackBarOrthoAngle;
	TTrackBar *TrackBarHorizOffset;
	TTrackBar *TrackBarFontZoom;
	TTrackBar *TrackBarElevation;
	TMapWMSPopupDialog *MapWMSPopupDialog1;
	TImage *Image1;
	TImageList *ImageList1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TMapWMSBuildURLDialog *MapWMSBuildURLDialog1;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TComboBox *ComboBox1;
	TMemo *MemoGood;
	TGroupBox *GroupBoxGPS;
	TBitBtn *BitBtn1;
	TLabel *g_Height;
	TLabel *g_Bearing;
	TLabel *g_Speed;
	TLabel *g_Longitude;
	TLabel *g_Latitude;
	TLabel *g_Time;
	TLabel *g_Date;
	TCheckBox *g_GpsInfoTrusted;
	TLabel *g_View;
	TLabel *g_TotalSat;
	TLabel *Label3;
	TLabel *Label12;
	TLabel *Label10;
	TLabel *Label223;
	TLabel *Label14;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label8;
	TLabel *Label2;
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBoxSatelit;
	TLabel *Label9;
	TLabel *UPK;
	TLabel *Label11;
	TLabel *UM;
	TLabel *Label7;
	TLabel *Label5;
	TEdit *LatSat;
	TTrackBar *UgolPovorotaConvertera;
	TTrackBar *Ugolmesta;
	TTrackBar *Azimut;
	TGroupBox *GroupBoxCMPS;
	TLabel *LabelMagRawY;
	TLabel *LabelAccelRawZ;
	TLabel *LabelAccelRawY;
	TLabel *LabelMagRawZ;
	TLabel *LabelMagRawX;
	TLabel *LabelRoll;
	TLabel *LabelPitch;
	TLabel *Label_Angle_16_Bit;
	TLabel *LabelVersion;
	TLabel *Label_Angle_8_Bit;
	TLabel *LabelAccelRawX;
	TButton *Button3;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TLabel *Az;
	void __fastcall N11Click(TObject *Sender);
	void __fastcall OpenPortClick(TObject *Sender);
	void __fastcall ClosePortClick(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall MapViewAppendSite(TObject *Sender, TMapSite *MapSite);
	void __fastcall MapViewKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MapViewKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MapViewKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MapViewBuildMtrProcess(TObject *Sender, UnicodeString MtrName, int Persent,
          bool &StopProcess);
	void __fastcall MapViewMapPaintObject(TObject *Sender, TCanvas *aCanvas, TRect &aMapPaintRect,
          int aLeftPosition, int aTopPosition, TMapPaintEventType aMapPaintEventType);
	void __fastcall MapViewMapSortProcess(TObject *Sender, int Persent, bool &StopProcess);
	void __fastcall MapViewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall MapViewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MapViewMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Draw3D1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Draw3D1Paint(TObject *Sender, const TRect &ARect);
	void __fastcall TrackBarChange(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton3Click(TObject *Sender);
	void __fastcall ToolButton4Click(TObject *Sender);
	void __fastcall ToolButton5Click(TObject *Sender);
	void __fastcall ToolButton6Click(TObject *Sender);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall ToolButton8Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall SettingCOMCMPSClick(TObject *Sender);
	void __fastcall OpenCOMCMPSClick(TObject *Sender);
	void __fastcall CloseCOMCMPSClick(TObject *Sender);






private:	// User declarations

	void __fastcall Move_To_Point(float X, float Y);			//Переместить карту в указанную точку
	void mapGeoAzimDistToGeo(DOUBLEPOINT *, double, double, DOUBLEPOINT *);

	void __fastcall mapPlaneToPicture(double *X, double *Y);
	void __fastcall mapPictureToPlane(double *X, double *Y);
	void __fastcall mapPlaneToGeo(double *X, double *Y);
	void __fastcall mapGeoToPlane(double *X, double *Y);
	void __fastcall mapGeoToPicture(double *X, double *Y);
	void __fastcall mapPictureToGeo(double *X, double *Y);

	AnsiString __fastcall DegToCharDeg(float deg);
	void __fastcall NRNRadCoord2Deg(double& rad, char* ret);

	char* __fastcall GPSParseValue( char *s, char *out, int skip );
	bool __fastcall checksum(char *s);
	void __fastcall ReadIni(AnsiString file_seting);

	int __fastcall GetChar(HANDLE hCom);
	void __fastcall ReadCMPS(HANDLE hCom);

	int MouseX;
	int MouseY;
	double MapLeft;
	double MapTop;
	double MouseClicX;
	double MouseClicY;
	float deltax;      // Абсцисса левого верхнего угла окна просмотра карты в пикселях в текущем масштабе отображения минус смещение относительно начала окна
	float deltay;      // Ордината левого верхнего угла окна просмотра карты в пикселях в текущем масштабе отображения минус смещение относительно начала окна
	float kkPrinter;   // КОЛ-ВО ТОЧЕК НА ДЮЙМ
	float kkScreen;    // КОЛ-ВО ПИКСЕЛОВ НА 100 СМ
	float kk;          // их соотношение

	double radians1;
	double radians2;
	double radians3;
	double radians4;
	double radians5;
	double radians6;
	double radians7;

	double radius1;
	double radius2;
	double radius3;
	double radius4;
	double radius5;
	double radius6;
	double radius7;

	double x1;
	double x2;
	double x3;
	double x4;
	double x5;
	double x6;
	double x7;

	double y1;
	double y2;
	double y3;
	double y4;
	double y5;
	double y6;
	double y7;

	double Alfa_Sat;
	double Alfa_Sat_Course;

	char buff[1024];
	char sval[1024];

	bool flg;

	double X_GNSS_POS;
	double Y_GNSS_POS;
	int Alfa;
	int AlfaCMPS;



public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	HINSTANCE dllInstance;

	typedef void (__import * MType());
    MType * MapWorkSetFree;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
