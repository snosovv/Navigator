//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mapcmp"
#pragma link "mapviewa"
#pragma link "mapwina"
#pragma link "mapdialg"
#pragma link "mapcompa"
#pragma link "mappoint"
#pragma link "mDialog"
#pragma link "mdlgsher"
#pragma link "mapscrn"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	MapWorkSetFree = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N11Click(TObject *Sender)
{
	FormPorts->Device = GPS;
	FormPorts->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenPortClick(TObject *Sender)
{
	FormPorts->Device = GPS;
	FormPorts->PortOpen();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClosePortClick(TObject *Sender)
{
	FormPorts->Device = GPS;
	FormPorts->PortClose();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
	if(MapWorkSetFree != NULL)
	{
		FreeLibrary(dllInstance);
		MapWorkSetFree = NULL;
	}

	OpenMapDialog->Preview = true;
	//Вызвать диалог
	if(OpenMapDialog->Execute())
	{
		if(MapView->MapHandle)
		{
			MapView->Rendering = false;
			MapView->MapSites->Append(OpenMapDialog->FileName);
			MapView->Rendering = true;
			MapView->Repaint();
		}
		else
		{
			MapView->Rendering = false;
			MapView->WriteLogAccess(false, false);

			dllInstance = LoadLibrary(L"MyDLL.dll");
			if(dllInstance)
			{
				MapWorkSetFree = (MType *)GetProcAddress(dllInstance, "_MapWorkSetFree");
				if(MapWorkSetFree)
				{
					MapWorkSetFree();
					MapView->MapFileName = OpenMapDialog->FileName;
				}
				else
				{
					ShowMessage("Функция 'MapWorkSetFree' недоступна");
					return;
				}
			}
			else
			{
				ShowMessage("Не удалось загрузить MYDLL.DLL");
				return;
			}

			MapView->WriteLogAccess(true, true);

			SetCurrentDir(ExtractFilePath(Application->ExeName));

			Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
			//Позиционируем вновь открываемую карту по центру
			DOUBLEPOINT XY1, XY2;
			XY1.X = Mapproc::mapGetMapX1(MapView->MapHandle);
			XY1.Y = Mapproc::mapGetMapY1(MapView->MapHandle);
			XY2.X = Mapproc::mapGetMapX2(MapView->MapHandle);
			XY2.Y = Mapproc::mapGetMapY2(MapView->MapHandle);
			Move_To_Point(XY2.X-(XY2.X-XY1.X)/2, XY2.Y-(XY2.Y-XY1.Y)/2);
			MapView->Rendering = true;
			MapView->Repaint();
		}
	}
}
//---------------------------------------------------------------------------


/******************************************************************************/
/*Функция позиционирования карты с центром в координатах X Y										*/
/******************************************************************************/
void __fastcall TForm1::Move_To_Point(float X, float Y)
{
	int aLeft=MapView->Width/2;
	int aTop=MapView->Height/2;
  //Отобразить карту с центром  в точке с координатами X Y
	MapView->GoPointInWindow(X, Y, Maptype::PP_PLANE, aLeft, aTop);
  //Перерисовать карту
	if(!MapView->Rendering)
		MapView->Rendering = true;
	else
		MapView->Repaint();

}

void __fastcall TForm1::MapViewAppendSite(TObject *Sender, TMapSite *MapSite)
{
	MapView->ViewScale = MapView->ViewScale;
	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == 10)
		MapView->ViewScale = MapView->ViewScale/1.5;
	else if(Key == 20)
		MapView->ViewScale = MapView->ViewScale*1.5;

	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == 10)
		MapView->ViewScale = MapView->ViewScale/1.5;
	else if(Key == 20)
		MapView->ViewScale = MapView->ViewScale*1.5;

	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == 10)
		MapView->ViewScale = MapView->ViewScale/1.5;
	else if(Key == 20)
		MapView->ViewScale = MapView->ViewScale*1.5;

	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::MapViewBuildMtrProcess(TObject *Sender, UnicodeString MtrName,
          int Persent, bool &StopProcess)
{
	MapView->ViewScale = MapView->ViewScale;
	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
 	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewMapPaintObject(TObject *Sender, TCanvas *aCanvas, TRect &aMapPaintRect,
          int aLeftPosition, int aTopPosition, TMapPaintEventType aMapPaintEventType)

{
		//Если карта не открыта или запрещена ее перерисовка выходим из функции
	if(MapView->MapHandle == 0 || MapView->Rendering == false) return;
	//Если запрощенна печать карты, то оставляем масштабный кооэффициент посчитанный
	//для текущего принтера
	if (aMapPaintEventType != 2/*PaintInPrinter*/)
		kk = 1.0;

	deltax=MapView->MapLeft+aLeftPosition;
	deltay=MapView->MapTop+aTopPosition;

	double xp1, yp1;
	double xp2, yp2;

	DOUBLEPOINT Point1;
	DOUBLEPOINT Point2;

	xp1 = X_GNSS_POS*DegToRad;
	yp1 = Y_GNSS_POS*DegToRad;

//	mapGeoWGS84ToGeo42(MapView->MapHandle, &xp1, &yp1);

	Point1.x = xp1;
	Point1.y = yp1;
	mapGeoAzimDistToGeo(&Point1, 0, 10000, &Point2);
	xp2 = Point2.x;
	yp2 = Point2.y;

	mapGeoToPicture(&xp1, &yp1);
	mapGeoToPicture(&xp2, &yp2);

	double da = 0;

	if(xp2 - xp1 > 0)
		da = 90.0 + atan2((yp2 - yp1),(xp2 - xp1))/DegToRad;

//	aCanvas->Ellipse((x-5-deltax)*kk, (y-5-deltay)*kk, (x+5-deltax)*kk, (y+5-deltay)*kk);
	Alfa_Sat = StrToFloat(Az->Caption)+da;

	radians1 = (90-270.0-Alfa_Sat)*DegToRad;
	radians2 = (90-350.4059317731395385555614721593-Alfa_Sat)*DegToRad;
	radians3 = (90-330.0-Alfa_Sat)*DegToRad;
	radians4 = (90-0.0-Alfa_Sat)*DegToRad;
	radians5 = (90-30.0-Alfa_Sat)*DegToRad;
	radians6 = (90-9.5940682268604614444385278406991-Alfa_Sat)*DegToRad;
	radians7 = (90-90.0-Alfa_Sat)*DegToRad;

	radius1 = sqrt(15*15+0*0);
	radius2 = sqrt(15*15+90*90);
	radius3 = sqrt(45*45+90*90);
	radius4 = sqrt(0*0+150*150);
	radius5 = sqrt(45*45+90*90);
	radius6 = sqrt(15*15+90*90);
	radius7 = sqrt(15*15+0*0);

	x1 = radius1*cos(radians1);
	y1 = -radius1*sin(radians1);

	x2 = radius2*cos(radians2);
	y2 = -radius2*sin(radians2);

	x3 = radius3*cos(radians3);
	y3 = -radius3*sin(radians3);

	x4 = radius4*cos(radians4);
	y4 = -radius4*sin(radians4);

	x5 = radius5*cos(radians5);
	y5 = -radius5*sin(radians5);

	x6 = radius6*cos(radians6);
	y6 = -radius6*sin(radians6);

	x7 = radius7*cos(radians7);
	y7 = -radius7*sin(radians7);

	aCanvas->Pen->Width = 1;
	aCanvas->Pen->Color = clBlack;
	aCanvas->Brush->Color = clGreen;

	TPoint* points_sat = new TPoint[8];
	points_sat[0]=Classes::Point((xp1-deltax)*kk,(yp1-deltay)*kk);
	points_sat[1]=Classes::Point((xp1-deltax+x1)*kk,(yp1-deltay+y1)*kk);
	points_sat[2]=Classes::Point((xp1-deltax+x2)*kk,(yp1-deltay+y2)*kk);
	points_sat[3]=Classes::Point((xp1-deltax+x3)*kk,(yp1-deltay+y3)*kk);
	points_sat[4]=Classes::Point((xp1-deltax+x4)*kk,(yp1-deltay+y4)*kk);
	points_sat[5]=Classes::Point((xp1-deltax+x5)*kk,(yp1-deltay+y5)*kk);
	points_sat[6]=Classes::Point((xp1-deltax+x6)*kk,(yp1-deltay+y6)*kk);
	points_sat[7]=Classes::Point((xp1-deltax+x7)*kk,(yp1-deltay+y7)*kk);
	aCanvas->Polygon(points_sat, 7);
	if(points_sat) delete [] points_sat;

//	Alfa_Sat_Course = Alfa_Sat-Alfa;
	Alfa_Sat_Course = AlfaCMPS;

	radians1 = (90-270.0-Alfa_Sat_Course)*DegToRad;
	radians2 = (90-350.4059317731395385555614721593-Alfa_Sat_Course)*DegToRad;
	radians3 = (90-330.0-Alfa_Sat_Course)*DegToRad;
	radians4 = (90-0.0-Alfa_Sat_Course)*DegToRad;
	radians5 = (90-30.0-Alfa_Sat_Course)*DegToRad;
	radians6 = (90-9.5940682268604614444385278406991-Alfa_Sat_Course)*DegToRad;
	radians7 = (90-90.0-Alfa_Sat_Course)*DegToRad;

	radius1 = sqrt(15*15+0*0);
	radius2 = sqrt(15*15+90*90);
	radius3 = sqrt(45*45+90*90);
	radius4 = sqrt(0*0+150*150);
	radius5 = sqrt(45*45+90*90);
	radius6 = sqrt(15*15+90*90);
	radius7 = sqrt(15*15+0*0);

	x1 = radius1*cos(radians1);
	y1 = -radius1*sin(radians1);

	x2 = radius2*cos(radians2);
	y2 = -radius2*sin(radians2);

	x3 = radius3*cos(radians3);
	y3 = -radius3*sin(radians3);

	x4 = radius4*cos(radians4);
	y4 = -radius4*sin(radians4);

	x5 = radius5*cos(radians5);
	y5 = -radius5*sin(radians5);

	x6 = radius6*cos(radians6);
	y6 = -radius6*sin(radians6);

	x7 = radius7*cos(radians7);
	y7 = -radius7*sin(radians7);

	aCanvas->Pen->Width = 1;
	aCanvas->Pen->Color = clBlack;
	aCanvas->Brush->Color = clWhite;

	TPoint* points_sat_course = new TPoint[8];
	points_sat_course[0]=Classes::Point((xp1-deltax)*kk,(yp1-deltay)*kk);
	points_sat_course[1]=Classes::Point((xp1-deltax+x1)*kk,(yp1-deltay+y1)*kk);
	points_sat_course[2]=Classes::Point((xp1-deltax+x2)*kk,(yp1-deltay+y2)*kk);
	points_sat_course[3]=Classes::Point((xp1-deltax+x3)*kk,(yp1-deltay+y3)*kk);
	points_sat_course[4]=Classes::Point((xp1-deltax+x4)*kk,(yp1-deltay+y4)*kk);
	points_sat_course[5]=Classes::Point((xp1-deltax+x5)*kk,(yp1-deltay+y5)*kk);
	points_sat_course[6]=Classes::Point((xp1-deltax+x6)*kk,(yp1-deltay+y6)*kk);
	points_sat_course[7]=Classes::Point((xp1-deltax+x7)*kk,(yp1-deltay+y7)*kk);
	aCanvas->Polygon(points_sat_course, 7);
	if(points_sat_course) delete [] points_sat_course;



	radians1 = (-66.421821521798168895977500580173-((double)Alfa+da))*DegToRad;
	radians2 = (-90.0-(Alfa+da))*DegToRad;
	radians3 = (-113.57817847820183110402249941983-(Alfa+da))*DegToRad;

	radius1 = sqrt(25*25+10*10);
	radius2 = sqrt(20*20+0*0);
	radius3 = sqrt(25*25+10*10);

	x1 = radius1*cos(radians1);
	y1 = -radius1*sin(radians1);

	x2 = radius2*cos(radians2);
	y2 = -radius2*sin(radians2);

	x3 = radius3*cos(radians3);
	y3 = -radius3*sin(radians3);

	aCanvas->Pen->Width = 1;
	aCanvas->Pen->Color = clBlack;
	aCanvas->Brush->Color = clRed;

	TPoint* points = new TPoint[4];
	points[0]=Classes::Point((xp1-deltax)*kk,(yp1-deltay)*kk);
	points[1]=Classes::Point((xp1-deltax+x1)*kk,(yp1-deltay+y1)*kk);
	points[2]=Classes::Point((xp1-deltax+x2)*kk,(yp1-deltay+y2)*kk);
	points[3]=Classes::Point((xp1-deltax+x3)*kk,(yp1-deltay+y3)*kk);
	aCanvas->Polygon(points, 3);
	if(points) delete [] points;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewMapSortProcess(TObject *Sender, int Persent, bool &StopProcess)

{
	MapView->ViewScale = MapView->ViewScale;
	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	//Если не открыта карта производим выход из функции
	if(MapView->MapHandle == 0) return;
	else
	{
		//Координаты точки где кликнули мышкой
		MouseClicX = MapView->MapLeft+X;
		MouseClicY = MapView->MapTop+Y;
	}
	//Нажата левая клавиша мыши
	if(Button==mbLeft)
	{
		MouseX=X;
		MouseY=Y;
		MapView->Cursor=crHandPoint;
	}
	//Нажата правая клавиша мыши
	else if(Button==mbRight)
	{
		MouseX=X;
		MouseY=Y;
		MapView->Cursor=crHandPoint;
	}
	//Нажато колесо прoкрутки
	else if(Button==mbMiddle)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	//Если карта не открыта выходим из функции
	if(MapView->MapHandle == 0) return;
	AnsiString nd;
	//Координаты положения курсора над картой
	double tempx=MapView->MapLeft+X;
	double tempy=MapView->MapTop+Y;
	mapPictureToGeo(&tempx, &tempy);
//	LBLL->Caption="Широта: "+ FloatToStr(tempx/DegToRad).SubString(1,10) + " Долгота: " +FloatToStr(tempy/DegToRad).SubString(1,10);

 //Если необходимо координаты в формате Градусы минуты секунды
	LBLL->Caption="Широта: "+DegToCharDeg(tempx/DegToRad) + " Долгота: " +DegToCharDeg(tempy/DegToRad);
//	LBLL->Caption="Широта: "+FloatToStr(tempx) + " Долгота: " +FloatToStr(tempy);

	//Если нажата левая клавиша, сдвигать карту
	if(MapView->Cursor==crHandPoint)
	{
		MapView->MapLeft+=(MouseX-X);
		MapView->MapTop+=(MouseY-Y);
		MouseX=X;
		MouseY=Y;

		MapLeft = MapView->MapLeft;
		MapTop = MapView->MapTop;
		mapPictureToPlane(&MapLeft, &MapTop);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MapViewMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	MapView->Cursor=crDefault;
}
//---------------------------------------------------------------------------


/******************************************************************************/
//Функция определения географических координат точки PointEnd (в радианах),   */
//по географическим координатам начальной точки PointStart (в радианах),      */
//азимуту azimut (в радианах) и растоянию между ними точками distanse (в метрах)
/******************************************************************************/
void TForm1::mapGeoAzimDistToGeo(DOUBLEPOINT *PointStart, double azimut, double distanse, DOUBLEPOINT *PointEnd)
{
	if(distanse!=0.0)
	{
		int a = 6378245;
		double e2 = 0.0066934;
		double Roo=a*(1-0.5*e2*sin(PointStart->x)*sin(PointStart->x));
		double delta_fi = e2*sin(PointStart->x)*cos(PointStart->x);
		double fi = PointStart->x - delta_fi;
		double  D = distanse/Roo;
    	azimut = 0-azimut;
		double P11 = Roo*(cos(PointStart->y)*cos(fi)*cos(D)+sin(PointStart->y)*sin(azimut)*sin(D)-cos(PointStart->y)*sin(fi)*cos(azimut)*sin(D));
		double P21 = Roo*(sin(PointStart->y)*cos(fi)*cos(D)-cos(PointStart->y)*sin(azimut)*sin(D)-sin(PointStart->y)*sin(fi)*cos(azimut)*sin(D));
		double P31 = sin(fi)*cos(D)+cos(fi)*cos(azimut)*sin(D);
		PointEnd->y = atan2(P21,P11);
		double fi_0 = asin(P31);
		delta_fi = e2*sin(fi_0)*cos(fi_0);
		long double fi_1;
		for(int i=0; i<15; i++)
		{
			fi_1 = fi_0 + delta_fi;
			delta_fi = e2*sin(fi_1)*cos(fi_1);
		}
		PointEnd->x = fi_0 + delta_fi;
	}
	else
	{
		PointEnd->x = PointStart->x;
		PointEnd->y = PointStart->y;
	}
}


void __fastcall TForm1::mapPlaneToPicture(double *X, double *Y)
{
	axMapPointPlaneToPicture->MapView = MapView;
	axMapPointPlaneToPicture->PlaceInp = Maptype::PP_PLANE;
	axMapPointPlaneToPicture->PlaceOut = Maptype::PP_PICTURE;
	axMapPointPlaneToPicture->SetPoint(*X, *Y);
	axMapPointPlaneToPicture->GetPoint(*X, *Y);
}

void __fastcall TForm1::mapPictureToPlane(double *X, double *Y)
{
	axMapPointPictureToPlane->MapView = MapView;
	axMapPointPictureToPlane->PlaceInp = Maptype::PP_PICTURE;
	axMapPointPictureToPlane->PlaceOut = Maptype::PP_PLANE;
	axMapPointPictureToPlane->SetPoint(*X, *Y);
	axMapPointPictureToPlane->GetPoint(*X, *Y);
}

void __fastcall TForm1::mapPlaneToGeo(double *X, double *Y)
{
	axMapPointPlaneToGeo->MapView = MapView;
	axMapPointPlaneToGeo->PlaceInp = Maptype::PP_PLANE;
	axMapPointPlaneToGeo->PlaceOut = Maptype::PP_GEO;
	axMapPointPlaneToGeo->SetPoint(*X, *Y);
	axMapPointPlaneToGeo->GetPoint(*X, *Y);
}

void __fastcall TForm1::mapGeoToPlane(double *X, double *Y)
{
	axMapPointGeoToPlane->MapView = MapView;
	axMapPointGeoToPlane->PlaceInp = Maptype::PP_GEO;
	axMapPointGeoToPlane->PlaceOut = Maptype::PP_PLANE;
	axMapPointGeoToPlane->SetPoint(*X, *Y);
	axMapPointGeoToPlane->GetPoint(*X, *Y);
}

void __fastcall TForm1::mapGeoToPicture(double *X, double *Y)
{
	axMapPointGeoToPicture->MapView = MapView;
	axMapPointGeoToPicture->PlaceInp = Maptype::PP_GEO;
	axMapPointGeoToPicture->PlaceOut = Maptype::PP_PICTURE;
	axMapPointGeoToPicture->SetPoint(*X, *Y);
	axMapPointGeoToPicture->GetPoint(*X, *Y);
}

void __fastcall TForm1::mapPictureToGeo(double *X, double *Y)
{
	axMapPointPictureToGeo->MapView = MapView;
	axMapPointPictureToGeo->PlaceInp = Maptype::PP_PICTURE;
	axMapPointPictureToGeo->PlaceOut = Maptype::PP_GEO;
	axMapPointPictureToGeo->SetPoint(*X, *Y);
	axMapPointPictureToGeo->GetPoint(*X, *Y);
}


AnsiString __fastcall TForm1::DegToCharDeg(float deg)
{
		char gms[14];
		double tmp = deg*DegToRad;
		NRNRadCoord2Deg(tmp, gms);
		return (AnsiString)gms;
}

/*****************************************************************************/
// Функция перевода радиан в градусы для координат
/******************************************************************************/
void __fastcall TForm1::NRNRadCoord2Deg(double& rad, char* ret)
{
 ret[0]='\0';
 char degString[5];
 char minString[4];
 char secStringD[4];
 char secStringF[4];
 double tmp;

 int deg;
 int min;
 double sec;

 if(rad > 2*M_PI) rad -=2*M_PI;
 tmp = fabs((rad*180.0)/M_PI);
 deg=(int)tmp;
 tmp=(tmp-(int)tmp)*60.0;
 min=(int)tmp;
 tmp=(tmp-(int)tmp)*60.0;
 sec=tmp;

 sec*=100.0;
 sec=floor(sec+0.5);
 sec/=100.0;

 if(sec > 59.99)
 {
		 sec = 0.0;
		 min++;
 }

 if(min > 59)
 {
		min = 0;
		deg++;
 }

 if(rad < 0)
 {
	strcpy(ret,"-");
	sprintf(degString,"%02d°",deg);
 }
 else
 {
	sprintf(degString,"%03d°",deg);
 }

 sprintf(minString,"%02d'",min);
 sprintf(secStringD,"%02i,",(int)fabs(sec));
 sprintf(secStringF,"%02i\"",(int)((fabs(sec)-(int)fabs(sec))*100));

 strcat(ret,degString);
 strcat(ret,minString);
 strcat(ret,secStringD);
 strcat(ret,secStringF);
 if(strcmp(ret, "359°59'60,00\"") == 0)
 strcpy(ret,"000°00'00,00\"");
}
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	Button2Click(NULL);

	TIniFile *ini = new TIniFile(ExtractFilePath(Application->ExeName) + "setting.ini");
	{
		//Запомнить карту и параметры при выходе
		if(MapView->MapHandle)
		{
			//Запомнить имя файла карты
			ini->WriteString("SetingSledopyt", "MapFileName", MapView->MapFileName);
			ini->WriteFloat("SetingSledopyt", "MapTurn", MapView->TurnAngle());
			//Координаты верхнего левого угла
			MapLeft = MapView->MapLeft;
			MapTop = MapView->MapTop;
			ini->WriteInteger("SetingSledopyt", "MapLeft", MapLeft);
			ini->WriteInteger("SetingSledopyt", "MapTop", MapTop);
			//Масштаб отображения
			ini->WriteInteger("SetingSledopyt", "MapScale", MapView->ViewScale);

			//Закрыть карту
			MapView->MapFileName = "";
		}
		else
		{
			//Запомнить имя файла карты
			ini->WriteString("SetingSledopyt", "MapFileName", "");
			ini->WriteFloat("SetingSledopyt", "MapTurn", 0);
			//Координаты верхнего левого угла
			MapLeft = MapView->MapLeft;
			MapTop = MapView->MapTop;
			ini->WriteInteger("SetingSledopyt", "MapLeft", 0);
			ini->WriteInteger("SetingSledopyt", "MapTop", 0);
			//Масштаб отображения
			ini->WriteInteger("SetingSledopyt", "MapScale", 1);
		}
	}
	delete ini;

	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == 10)
		MapView->ViewScale = MapView->ViewScale/1.5;
	else if(Key == 20)
		MapView->ViewScale = MapView->ViewScale*1.5;

	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == 10)
		MapView->ViewScale = MapView->ViewScale/1.5;
	else if(Key == 20)
		MapView->ViewScale = MapView->ViewScale*1.5;

	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 10)
		MapView->ViewScale = MapView->ViewScale/1.5;
	else if(Key == 20)
		MapView->ViewScale = MapView->ViewScale*1.5;

	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled)
{
	if(MapView->MapHandle == 0) return;

	static TTimeStamp Time1Stamp = DateTimeToTimeStamp (Now());
	if((DateTimeToTimeStamp (Now()).Time- Time1Stamp.Time) < 500)
		return;

	Time1Stamp = DateTimeToTimeStamp (Now());

	//Спозиционировать карту в позицию где кликнули мышкой
	//Координаты точки где кликнули мышкой
	double x = MapView->MapLeft+MousePos.x-0;
	double y = MapView->MapTop+MousePos.y-0;

	int aLeft = MousePos.x-0;
	int aTop = MousePos.y-0;

	//В метрах на местности
	mapPictureToPlane(&x,&y);
	MapView->Rendering = false;
	if(WheelDelta<0)
	{
		//Уменьшать масштаб пока карта выходит за пределы области видимости
		DOUBLEPOINT XY1, XY2;
		XY1.X = Mapproc::mapGetMapX1(MapView->MapHandle);
		XY1.Y = Mapproc::mapGetMapY1(MapView->MapHandle);
		XY2.X = Mapproc::mapGetMapX2(MapView->MapHandle);
		XY2.Y = Mapproc::mapGetMapY2(MapView->MapHandle);
		mapPlaneToPicture(&XY1.X,&XY1.Y);
			mapPlaneToPicture(&XY2.X,&XY2.Y);
			if(	(abs(XY2.X-XY1.X) > MapView->Width)		||
				(abs(XY2.Y-XY1.Y) > MapView->Height)    ||
				//Для интернет карт нет габаритов района
				(abs(XY2.X-XY1.X) < 1)					||
				(abs(XY2.Y-XY1.Y) < 1)

			)
			{
				double k=1.0;
				int scale = MapView->ViewScale;
				do
				{
					//У каждой карты свой минимально возможный коэффициент изменения масштаба
					k += 0.2;
					MapView->ViewScale = (int)(((double)MapView->ViewScale)*k);
				}while (MapView->ViewScale == scale && k < 10.0);

				Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
            }
			else
			{
				MapView->Rendering = true;
				return;
			}
		}
		else
		{
			//Увеличить масштаб отображения карты
			//Максимальный масштаб 1:200
			if(MapView->ViewScale >= 400)
			{
				double k=1.0;
				int scale = MapView->ViewScale;
				do
				{
					//У каждой карты свой минимально возможный коэффициент изменения масштаба
					k += 0.2;
					MapView->ViewScale = (int)(((double)MapView->ViewScale)/k);
				}while (MapView->ViewScale == scale && k < 10.0);

				Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
			}
			else
			{
				MapView->Rendering = true;
				return;
			}
		}

		//Переместить карту относительно позици где кликнули
		MapView->GoPointInWindow(x, y, Maptype::PP_PLANE, aLeft, aTop);

		//В пиксели экрана
		mapPlaneToPicture(&x,&y);

		x = x - MapView->MapLeft + 0;
		y = y - MapView->MapTop + 0;
		SetCursorPos(x, y);

	 MapView->Rendering = true;
	 MapView->Refresh();

	 Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
	SetCurrentDir(ExtractFilePath(Application->ExeName));

	ReadIni(ExtractFilePath(Application->ExeName) + "setting.ini");

	Elevation->Text = IntToStr(Draw3D1->View3DOptions->Elevation);
	FontZoom->Text = IntToStr(Draw3D1->View3DOptions->FontZoom);
	HorizOffset->Text = IntToStr(Draw3D1->View3DOptions->HorizOffset);
	OrthoAngle->Text = IntToStr(Draw3D1->View3DOptions->OrthoAngle);
	Orthogonal->Checked = Draw3D1->View3DOptions->Orthogonal;
	Perspective->Text = IntToStr(Draw3D1->View3DOptions->Perspective);
	Rotation->Text = IntToStr(Draw3D1->View3DOptions->Rotation);
	Tilt->Text = IntToStr(Draw3D1->View3DOptions->Tilt);
	VertOffset->Text = IntToStr(Draw3D1->View3DOptions->VertOffset);
	Zoom->Text = IntToStr(Draw3D1->View3DOptions->Zoom);


	TrackBarElevation->Position = Draw3D1->View3DOptions->Elevation;
	TrackBarFontZoom->Position = Draw3D1->View3DOptions->FontZoom;
	TrackBarHorizOffset->Position = Draw3D1->View3DOptions->HorizOffset;
	TrackBarOrthoAngle->Position = Draw3D1->View3DOptions->OrthoAngle;
	TrackBarPerspective->Position = Draw3D1->View3DOptions->Perspective;
	TrackBarRotation->Position = Draw3D1->View3DOptions->Rotation;
	TrackBarTilt->Position = Draw3D1->View3DOptions->Tilt;
	TrackBarVertOffset->Position = Draw3D1->View3DOptions->VertOffset;
	TrackBarVertOffset->Position = Draw3D1->View3DOptions->VertOffset;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	flg = false;
}
//---------------------------------------------------------------------------


/* parse value from string with ',' delimeter */
char* __fastcall TForm1::GPSParseValue( char *s, char *out, int skip ){
	while(*s && skip){
		if( *s++ == ',' )
			--skip;
	}
	if( *s == 0 )
		return 0;
	while( *s && *s!=',' )
		*out++=*s++;
	*out=0;

	if( *s != ',' )
		return 0;

	return s;
}


bool __fastcall TForm1::checksum(char *s) {
		int c = 0;

		while(*s)
		{
				if(*s == '*')
					break;
				c ^= *s++;
		}

		AnsiString chsum = "";
		*s++;
		chsum = chsum + *s;
		*s++;
		chsum = chsum + *s;

		AnsiString calc_chsum = IntToHex(c,2);


		if(calc_chsum == chsum)
			return true;

		return false;
}


void __fastcall TForm1::ReadIni(AnsiString file_seting)
{
	//Проверить подключение ГЛОНАСС приемника
	FormPorts->Device = GPS;
	FormPorts->ReadSeting("GPS");
	FormPorts->Button2Click(NULL);
	FormPorts->PortClose();

	//Проверить подключение компаса
	FormPorts->Device = CMPS;
	FormPorts->ReadSeting("CMPS");
	FormPorts->Button2Click(NULL);
	FormPorts->PortClose();

    TIniFile *ini = new TIniFile (ExtractFilePath(Application->ExeName) + "setting.ini");
		AnsiString MapFileName = ini->ReadString("SetingSledopyt", "MapFileName", ExtractFilePath(Application->ExeName) + "MAPS\\Russia.sit");
		MapView->WriteLogAccess(false, false);

		dllInstance = LoadLibrary(L"MyDLL.dll");
		if(dllInstance)
		{
			MapWorkSetFree = (MType *)GetProcAddress(dllInstance, "_MapWorkSetFree");
			if(MapWorkSetFree)
			{
				MapWorkSetFree();
				MapView->MapFileName = MapFileName;
			}
			else
			{
				ShowMessage("Функция 'MapWorkSetFree' недоступна");
			}
		}
		else
		{
			ShowMessage("Не удалось загрузить MYDLL.DLL");
		}

		MapView->WriteLogAccess(false, false);
		MapView->TurnSetup(ini->ReadFloat("SetingSledopyt", "MapTurn", 0.0) ,0);
		MapView->Repaint();
		MapLeft = ini->ReadInteger("SetingSledopyt", "MapLeft", 43106);
		MapTop = ini->ReadInteger("SetingSledopyt", "MapTop", 97318);
		MapView->ViewScale = ini->ReadInteger("SetingSledopyt", "MapScale", 424089);
		Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
		if (MapLeft == -1 && MapTop == -1)
		{
			MapView->MapLeft = MapView->MapWidth/2;
			MapView->MapTop = MapView->Height/2;
		}
		else
		{
			MapView->MapLeft = MapLeft;
			MapView->MapTop = MapTop;
		}

		SetCurrentDir(ExtractFilePath(Application->ExeName));


}
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	double x,y;

	x = X_GNSS_POS*DegToRad;
	y = Y_GNSS_POS*DegToRad;

	mapGeoToPlane(&x, &y);
	Move_To_Point(x,y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	//Проверить подключение компаса
	FormPorts->Device = CMPS;
	FormPorts->ReadSeting("CMPS");
	FormPorts->Button2Click(NULL);
	FormPorts->PortClose();

	HANDLE hComCMPS = FormPorts->SerialOpenPort( hComCMPS, FormPorts->ComboBox1->Items->Strings[FormPorts->ComboBox1->ItemIndex] );

	//Проверить подключение спутникового приемника
	FormPorts->Device = GPS;
	FormPorts->ReadSeting("GPS");
	FormPorts->Button2Click(NULL);
	FormPorts->PortClose();

	int sym;
	char *p;
	double speed;
	char fix;

	HANDLE hCom = FormPorts->SerialOpenPort( hCom, FormPorts->ComboBox1->Items->Strings[FormPorts->ComboBox1->ItemIndex] );
	if( hCom == INVALID_HANDLE_VALUE )
		 return;

	flg = true;

	loc_current.hdop = 255;
	while( flg )
	{
		MSG message; while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

		Sleep( 1 );
		sym = FormPorts->SerialReceiveChar(hCom,  50 );

		if(sym == -1)
			continue;

        nmea_processor(sym);

		if( loc_current.hdop == 255 )
			continue;

		if(loc_current.loc_valid == 0)
		{
			g_GpsInfoTrusted->Checked = false;
			continue;
		}
		else
			g_GpsInfoTrusted->Checked = true;

		g_TotalSat->Caption = (int)loc_current.sats;
		g_View->Caption = "(" + IntToStr(loc_current.sats_track) + ")";

		char buf[9];

		sprintf(buf, "%.2d.%.2d.%.2d", loc_current.date[0], loc_current.date[1], loc_current.date[2]);
		g_Date->Caption = buf;

		sprintf(buf, "%.2d:%.2d:%.2d", loc_current.time[0], loc_current.time[1], loc_current.time[2]);
		g_Time->Caption = buf;

		char xgms[14];
		char ygms[14];

		X_GNSS_POS = ((double(loc_current.lat))/10000000.0);
		double tempx=X_GNSS_POS*DegToRad;
		NRNRadCoord2Deg(tempx, xgms);
		g_Latitude->Caption = (AnsiString)xgms;

		Y_GNSS_POS = ((double(loc_current.lon))/10000000.0);
		double tempy=Y_GNSS_POS*DegToRad;
		NRNRadCoord2Deg(tempy, ygms);
		g_Longitude->Caption = (AnsiString)ygms;

		g_Speed->Caption = loc_current.speed;

		g_Bearing->Caption = loc_current.course;
		Alfa = loc_current.course;

		g_Height->Caption = loc_current.alt;

		double k = PI/180;
		double a = ((double(loc_current.lat))/10000000.0) * k;
		double b = ((double(loc_current.lon))/10000000.0) * k;
		double c = StrToFloat(LatSat->Text) * k;

		if(a == 0 || b == 0 || c == 0)
			continue;

		Az->Caption = FloatToStr((PI+atan(tan(b-c)/sin(a)))/k);
		Azimut->Position = StrToFloat(Az->Caption);


		UM->Caption = FloatToStr(atan((cos(b-c)*cos(a)-0.15126)/sqrt(1-cos(b-c)*cos(b-c)*cos(a)*cos(a)))/k);
		Ugolmesta->Position = StrToFloat(UM->Caption);

		UPK->Caption = FloatToStr(atan(sin(b-c)/tan(a))/k);
		UgolPovorotaConvertera->Position = StrToFloat(UPK->Caption);


		loc_current.hdop  = 255;

/*
		if( sym != '$')
			continue;


		p = buff;
		*p++=sym;
		while( sym != '\n' ){
			sym = FormPorts->SerialReceiveChar( hCom, 5000 );
			if( sym == -1 )
				break;
			*p++ = sym;
		}
		/* bad string */
/*
		if( sym == -1 )
			continue;
		*p = 0;
//		 MemoAll->Lines->Add(buff);

		if(!checksum(&buff[1]))
			continue;
//		else
//			MemoGood->Lines->Add(buff);

		validMessage->Caption = IntToStr(validMessage->Caption.ToInt()+1);



		if( strncmp( buff, "$GPGGA", 6) == 0){
						p = GPSParseValue( buff, sval, 7);
						if( p == 0 )
								continue;
						g_TotalSat->Caption = atoi( sval );

			p = GPSParseValue( buff, sval, 9);
						if( p == 0 )
								continue;
						g_Height->Caption = (int)fabs(atof( sval ));
						continue;
				}

		//Количество видимых спутников
		if(strncmp( buff, "$GPGSV", 6) == 0)
		{
			p = GPSParseValue( buff, sval, 2);
						if( p == 0 )
				continue;

			if(atoi( sval ) == 1)
			{

				p = GPSParseValue( buff, sval, 3);
				if( p == 0 )
					continue;

				g_View->Caption = "(" + IntToStr(atoi( sval )) + ")";
			}
			continue;
		}


		if( strncmp( buff, "$GPRMC", 6) != 0)
			continue;

		MemoGood->Lines->Add(buff);

//		validMessage->Caption = IntToStr(validMessage->Caption.ToInt()+1);

				//UTC Time hhmmss.sss
				p = GPSParseValue( buff, sval, 1 );
				if( p == 0 )
						continue;
				g_Time->Caption = (int)atof( sval );
				if(g_Time->Caption.Length() == 5)
					g_Time->Caption = "0"+g_Time->Caption;

		p = GPSParseValue( buff, sval, 7 );
		if( p == 0 )
			continue;

		speed = atof( sval );
		g_Speed->Caption = (long)(speed*1.85200);

		p = GPSParseValue( buff, sval, 8 );
		if( p == 0 )
			continue;

		g_Bearing->Caption = atof( sval );
		Alfa = g_Bearing->Caption.ToDouble();

				//Date
				p = GPSParseValue( buff, sval, 9 );
				if( p == 0 )
						continue;
				g_Date->Caption = atol( sval );
				if(g_Date->Caption.Length() == 5)
					g_Date->Caption = "0"+g_Date->Caption;

		//Status A=data valid or V=data not valid
		g_GpsInfoTrusted->Checked = FALSE;
		p = GPSParseValue( buff, sval, 2 );

		if( p == 0 )
			continue;
		fix = sval[0];

		if(fix == 'A')
		{
			char xgms[14];
			char ygms[14];

			//Latitude
					p = GPSParseValue( buff, sval, 3 );
					if( p == 0 )
						 continue;
					double latdeg = atof( sval );
					latdeg = (double)((int)(latdeg/100))+(latdeg/100-(int)(latdeg/100))/60.0*100.0;


					//N/S Indicator
					p = GPSParseValue( buff, sval, 4 );
						if( p == 0 )
							continue;

			char latdir;
					latdir = sval[0];
			if (latdir == 'S')
				latdeg = -latdeg;

				X_GNSS_POS = latdeg;
				double tempx=X_GNSS_POS*DegToRad;
				NRNRadCoord2Deg(tempx, xgms);
				g_Latitude->Caption = (AnsiString)xgms;


					//Longitude
					p = GPSParseValue( buff, sval, 5 );
					if( p == 0 )
							continue;
					double lngdeg = atof( sval );
					lngdeg = (double)((int)(lngdeg/100))+(lngdeg/100-(int)(lngdeg/100))/60.0*100.0;
					//E/W Indicator
					p = GPSParseValue( buff, sval, 6 );
					if( p == 0 )
							continue;
			char lngdir;
					lngdir = sval[0];
			if (lngdir == 'W')
				lngdeg = -lngdeg;
				Y_GNSS_POS = lngdeg;
				double tempy=Y_GNSS_POS*DegToRad;
				NRNRadCoord2Deg(tempy, ygms);
					g_Longitude->Caption = (AnsiString)ygms;

					MapView->Repaint();

			if(g_TotalSat->Caption.ToInt() > 3 && g_Speed->Caption.ToInt() < 180)
				g_GpsInfoTrusted->Checked = TRUE;
		}
*/
		if( hComCMPS != INVALID_HANDLE_VALUE )
			ReadCMPS(hComCMPS);

		MapView->Repaint();
	}

	FormPorts->SerialClosePort( hCom );
	if( hComCMPS != INVALID_HANDLE_VALUE )
		FormPorts->SerialClosePort( hComCMPS);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
	TIniFile *ini = new TIniFile (ExtractFilePath(Application->ExeName) + "setting.ini");
		//Проверить подключение компаса
		FormPorts->Device = CMPS;
		FormPorts->ReadSeting("CMPS");
		FormPorts->Button2Click(NULL);
		FormPorts->PortClose();
    delete ini;

	HANDLE hCom = FormPorts->SerialOpenPort( hCom, FormPorts->ComboBox1->Items->Strings[FormPorts->ComboBox1->ItemIndex] );
	if( hCom == INVALID_HANDLE_VALUE )
		 return;

	flg = true;

	while( flg )
	{
		ReadCMPS(hCom);
	}

	FormPorts->SerialClosePort( hCom );
}

//---------------------------------------------------------------------------

void __fastcall TForm1::ReadCMPS(HANDLE hCom)
{
    int sym;
	int ANGLE_16;
	double bearing;

	MSG message; while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	FormPorts->SerialWriteChar (hCom, 0x11);
	sym = GetChar(hCom);
	if(sym != 15)
	{
		while(sym != -1)
			sym = GetChar(hCom);
		validMessage->Caption = IntToStr(validMessage->Caption.ToInt()+1);
		return;
	}

	LabelVersion->Caption = "V. 0x" + IntToHex(sym, 2);
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	FormPorts->SerialWriteChar (hCom, 0x12);
	sym = GetChar(hCom);
	bearing = ((double)sym)*360.0/256.0-10.64;
	if(bearing < 0)
		bearing += 360.0;
	Label_Angle_8_Bit->Caption = "Ang( 8) = " + FloatToStr(bearing) + "°";
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	FormPorts->SerialWriteChar (hCom, 0x23);
	sym = GetChar(hCom);
	ANGLE_16 = sym;
	sym = GetChar(hCom);
	ANGLE_16 = (ANGLE_16<<8)+sym;
	bearing = ((double)ANGLE_16)/10.0-10.64;
	if(bearing < 0)
		bearing += 360.0;
	Label_Angle_16_Bit->Caption = "Ang(16) = " + FloatToStr(bearing) + "°";

//	g_Bearing->Caption = IntToStr((int)bearing);
	AlfaCMPS = (int)bearing;

	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

//	FormPorts->SerialWriteChar (hCom, 0x14);
	sym = GetChar(hCom);
	if(sym > 127)
		sym -= 256;
	LabelPitch->Caption = "Pitch = " + IntToStr(sym) + "°";
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

//	FormPorts->SerialWriteChar (hCom, 0x15);
	sym = GetChar(hCom);
	if(sym > 127)
	sym -= 256;
	LabelRoll->Caption = "Roll = " + IntToStr(sym) + "°";
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	FormPorts->SerialWriteChar (hCom, 0x21);
	//X
	sym = GetChar(hCom);
	ANGLE_16 = sym;
	sym = GetChar(hCom);
	ANGLE_16 = (ANGLE_16<<8)+sym;
	if(ANGLE_16 > 32767)
		ANGLE_16 -= 65536;
	LabelMagRawX->Caption = "MagRaw Х="+FloatToStr(((double)ANGLE_16)/10.0);
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	//Y
	sym = GetChar(hCom);
	ANGLE_16 = sym;
	sym = GetChar(hCom);
	ANGLE_16 = (ANGLE_16<<8)+sym;
	if(ANGLE_16 > 32767)
		ANGLE_16 -= 65536;
	LabelMagRawY->Caption = "MagRaw Y="+FloatToStr(((double)ANGLE_16)/10.0);
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	//Z
	sym = GetChar(hCom);
	ANGLE_16 = sym;
	sym = GetChar(hCom);
	ANGLE_16 = (ANGLE_16<<8)+sym;
	if(ANGLE_16 > 32767)
		ANGLE_16 -= 65536;
	LabelMagRawZ->Caption = "MagRaw Z="+FloatToStr(((double)ANGLE_16)/10.0);
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	FormPorts->SerialWriteChar (hCom, 0x22);
	//X
	sym = GetChar(hCom);
	ANGLE_16 = sym;
	sym = GetChar(hCom);
	ANGLE_16 = (ANGLE_16<<8)+sym;
	if(ANGLE_16 > 32767)
	ANGLE_16 -= 65536;
	LabelAccelRawX->Caption = "AccelRaw Х="+FloatToStr(((double)ANGLE_16)/10.0);
	int x = ANGLE_16;
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	//Y
	sym = GetChar(hCom);
	ANGLE_16 = sym;
	sym = GetChar(hCom);
	ANGLE_16 = (ANGLE_16<<8)+sym;
	if(ANGLE_16 > 32767)
		ANGLE_16 -= 65536;
	LabelAccelRawY->Caption = "AccelRaw Y="+FloatToStr(((double)ANGLE_16)/10.0);
	int y = ANGLE_16;
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	//Z
	sym = GetChar(hCom);
	ANGLE_16 = sym;
	sym = GetChar(hCom);
	ANGLE_16 = (ANGLE_16<<8)+sym;
	if(ANGLE_16 > 32767)
		ANGLE_16 -= 65536;
	LabelAccelRawZ->Caption = "AccelRaw Z="+FloatToStr(((double)ANGLE_16)/10.0);
	int z = ANGLE_16;
	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}

	Draw3D1->Repaint();

	Draw3D1->Canvas->Pen->Color=clRed;
	Draw3D1->Canvas->HorizLine3D(-30,300,0,0);
	Draw3D1->Canvas->Pen->Color=clYellow;
	Draw3D1->Canvas->VertLine3D(0,300,-30,0);
	Draw3D1->Canvas->Pen->Color=clGreen;
	Draw3D1->Canvas->ZLine3D(0,0,-30,300);

	Draw3D1->Canvas->MoveTo3D(0, 0, 0);
	Draw3D1->Canvas->LineTo3D(x, y, z);

	while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}
}


int __fastcall TForm1::GetChar(HANDLE hCom)
{
	int sym;

//	while(flg)
//	{
		MSG message; while(::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {::TranslateMessage(&message); ::DispatchMessage(&message);}
		Sleep( 1 );
		sym = FormPorts->SerialReceiveChar(hCom,  50 );
/*
		if(sym != -1)
			break;
	}
*/
	Sleep(25);
	return sym;
}


void __fastcall TForm1::Draw3D1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
//	Draw3D1->Canvas->MoveTo3D(-100, -100, -100);
	Draw3D1->Canvas->TextOut3D(0, 0, 0, "X="+IntToStr(X)+" Y="+IntToStr(Y));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Draw3D1->View3DOptions->Elevation = StrToInt(Elevation->Text);
	Draw3D1->View3DOptions->FontZoom = StrToInt(FontZoom->Text);
	Draw3D1->View3DOptions->HorizOffset = StrToInt(HorizOffset->Text);
	Draw3D1->View3DOptions->OrthoAngle = StrToInt(OrthoAngle->Text);
	Draw3D1->View3DOptions->Orthogonal = Orthogonal->Checked;
	Draw3D1->View3DOptions->Perspective = StrToInt(Perspective->Text);
	Draw3D1->View3DOptions->Rotation = StrToInt(Rotation->Text);
	Draw3D1->View3DOptions->Tilt = StrToInt(Tilt->Text);
	Draw3D1->View3DOptions->VertOffset = StrToInt(VertOffset->Text);
	Draw3D1->View3DOptions->Zoom = StrToInt(Zoom->Text);

	Draw3D1->Repaint();
}
//---------------------------------------------------------------------------


TColor RandomColor(void)
{
  TColor Res;
  // This small function returns a random color
  switch (random(8))
  {
    case 0: Res = clRed; break;
    case 1: Res = clYellow; break;
    case 2: Res = clGreen; break;
    case 3: Res = clBlue; break;
    case 4: Res = clNavy; break;
    case 5: Res = clAqua; break;
    case 6: Res = clLime; break;
    default : Res = clWhite;
  }
  return Res;
}


void __fastcall TForm1::Draw3D1Paint(TObject *Sender, const TRect &ARect)
{
  int tmpX, tmpY;
  TPoint FourPoints[4];
  // We should use this event to "Paint" shapes onto a Draw3D
  //  component Canvas.

  // We can for example, use the "Center" position in the 3D space

  int CenterX = Draw3D1->ChartXCenter;
  int CenterY = Draw3D1->ChartYCenter;
  int CenterZ = 0;

  // Determine if draw dark shape shadows or not
  bool WithShadows = CheckBox1->Checked;

  // Using the Canvas, let's draw some shapes...
  TCanvas3D *c = Draw3D1->Canvas;
    // Draw a "room". Notice only 2D drawing methods are used here
    if (CheckBoxDrawRoom->Checked)
    {
      // use a gradient to simulate a "room" ...
      if (CheckBoxGradient->Checked) c->GradientFill(Draw3D1->ChartBounds,clWhite,clGray,gdFromCenter);
      else
      // or use polygons...
      {
        c->Pen->Style = psSolid;
        c->Pen->Color = clBlack;
        c->Brush->Color = clWhite;
        TRect R = Draw3D1->ChartBounds;
        tmpX = (R.Right-R.Left)/4;
        tmpY = (R.Bottom-R.Top)/4;
        FourPoints[0] = Point(R.Left,R.Bottom);
        FourPoints[1] = Point(R.Left,R.Top);
        FourPoints[2] = Point(R.Left+tmpX,R.Top+tmpY);
        FourPoints[3] = Point(R.Left+tmpX,R.Bottom-tmpY);
        c->Polygon(FourPoints,3);
        FourPoints[0] = Point(R.Right,R.Bottom);
        FourPoints[1] = Point(R.Right,R.Top);
        FourPoints[2] = Point(R.Right-tmpX,R.Top+tmpY);
        FourPoints[3] = Point(R.Right-tmpX,R.Bottom-tmpY);

        c->Polygon(FourPoints,3);
        c->Brush->Color = clGray;
        c->Rectangle(R.Left+tmpX,R.Top+tmpY,R.Right-tmpX,R.Bottom-tmpY);
      }
    }

    if (CheckBoxDrawAxes->Checked)
    {
      // Draw the "axis"
      c->Pen->Color = clNavy;
      c->Pen->Style = psDot;
      c->BackMode = cbmTransparent;
	  c->VertLine3D(CenterX,CenterY-30,CenterY+300,CenterZ);
	  c->HorizLine3D(CenterX-30,CenterX+300,CenterY,CenterZ);
      c->ZLine3D(CenterX,CenterY,CenterZ-30,CenterZ+300);
    }

    // Draw 100 small random dots, to simulate "dust"
    for (int t=0; t<101; t++)
        c->Pixels3D[200+random(50)][120+random(100)][20+random(100)] = RandomColor();

    // Draw several shapes, planes, pyramids, cubes, etc
    c->Pen->Color = clBlack;
    c->Pen->Style = psSolid;

    c->Brush->Color = clAqua;
    c->Plane3D(Point(5,200),Point(90,240), -10,30);

    c->Brush->Color = clYellow;
    c->Pyramid(false,5,150,130,200,5,30,WithShadows);

    c->Brush->Color = clWhite;
    c->Cube(5,80,80,120,5,30,WithShadows);

    c->Brush->Color = clLime;
    c->Cylinder(false,150,50,190,200,5,50,WithShadows);

    // Draw a 3D cone
    c->Pen->Width = 1;
    c->Pen->Color = clBlue;
    c->Brush->Color = clWhite;
    c->Cone(true,CenterX-50,20,CenterX,50,20,80,WithShadows,0);

    c->Brush->Color = clRed;
    c->EllipseWithZ(40,100,80,140,-20);

    c->Brush->Color = clBlue;
    c->Pen->Color = clYellow;
    c->Cube(CenterX+130,CenterX+170,120,190,70,100,WithShadows);

    c->Brush->Color = clRed;
    c->Pen->Color = clWhite;
    c->Cube(CenterX+30,CenterX+70,120,190,70,100,WithShadows);

    c->Brush->Color = clRed;
    c->Pen->Color = clYellow;
    c->Cube(CenterX+130,CenterX+170,120,190,10,30,WithShadows);

    c->Brush->Color = clBlue;
    c->Pen->Color = clWhite;
    c->Cube(CenterX+30,CenterX+70,120,190,10,30,WithShadows);

    c->Pen->Style = psClear;
    c->Brush->Color = clRed;
    c->Cylinder(false,CenterX+30,70,CenterX+170,100,70,100,WithShadows);
    c->Cylinder(false,CenterX+30,70,CenterX+170,100,10,40,WithShadows);
    c->Pen->Style = psSolid;

    // Draw a pyramid on top of the cylinder
    c->Brush->Color = clWhite;
    c->Pen->Color = clSilver;
    c->Pyramid(true,CenterX+30,40,CenterX+170,60,10,100,WithShadows);

    // Draw a black line on top of the pyramid
    c->Pen->Color = clBlack;
    c->Pen->Width = 2;
    c->MoveTo3D( CenterX+100, 40, 45 );
    c->LineTo3D( CenterX+100, 20, 45 );

    // Draw text at 3D xyz position, on top of the previous line
    c->Font->Color = clBlack;
    c->TextAlign = TA_CENTER;
    c->BackMode = cbmTransparent;
	c->TextOut3D(CenterX+100,0,45,"Hello!");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrackBarChange(TObject *Sender)
{
	if((TTrackBar *)Sender == TrackBarElevation)
		Elevation->Text = IntToStr(TrackBarElevation->Position);

	if((TTrackBar *)Sender == TrackBarFontZoom)
		FontZoom->Text = IntToStr(TrackBarFontZoom->Position);

	if((TTrackBar *)Sender == TrackBarHorizOffset)
		HorizOffset->Text = IntToStr(TrackBarHorizOffset->Position);

	if((TTrackBar *)Sender == TrackBarOrthoAngle)
		OrthoAngle->Text = IntToStr(TrackBarOrthoAngle->Position);

	if((TTrackBar *)Sender == TrackBarPerspective)
		Perspective->Text = IntToStr(TrackBarPerspective->Position);

	if((TTrackBar *)Sender == TrackBarRotation)
		Rotation->Text = IntToStr(TrackBarRotation->Position);

	if((TTrackBar *)Sender == TrackBarTilt)
		Tilt->Text = IntToStr(TrackBarTilt->Position);

	if((TTrackBar *)Sender == TrackBarVertOffset)
		VertOffset->Text = IntToStr(TrackBarVertOffset->Position);

	if((TTrackBar *)Sender == TrackBarZoom)
		Zoom->Text = IntToStr(TrackBarZoom->Position);

    Button4Click(NULL);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
	if(MessageDlg(	"Вернуть к заводским установкам?", mtConfirmation,	TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
	{
		HANDLE hCom = FormPorts->SerialOpenPort( hCom, FormPorts->ComboBox1->Items->Strings[FormPorts->ComboBox1->ItemIndex] );
		if( hCom == INVALID_HANDLE_VALUE )
		{
			MessageDlg(	"Не удалось открыть порт!", mtError,	TMsgDlgButtons() << mbOK, 0);
			return;
		}

		MessageDlg(	"Направте компа на север", mtError,	TMsgDlgButtons() << mbOK, 0);
		FormPorts->SerialWriteChar (hCom, 0x6A);
		Sleep(100);
		FormPorts->SerialWriteChar (hCom, 0x7C);
		Sleep(100);
		FormPorts->SerialWriteChar (hCom, 0x81);

		FormPorts->SerialClosePort( hCom );
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	if(MessageDlg(	"Отколибровать компас?", mtConfirmation,	TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
	{
		HANDLE hCom = FormPorts->SerialOpenPort( hCom, FormPorts->ComboBox1->Items->Strings[FormPorts->ComboBox1->ItemIndex] );
		if( hCom == INVALID_HANDLE_VALUE )
		{
			MessageDlg(	"Не удалось открыть порт!", mtError,	TMsgDlgButtons() << mbOK, 0);
			return;
		}

		MessageDlg(	"Направте компа на север", mtError,	TMsgDlgButtons() << mbOK, 0);
		FormPorts->SerialWriteChar (hCom, 0x31);
		Sleep(100);
		FormPorts->SerialWriteChar (hCom, 0x45);
		Sleep(100);
		FormPorts->SerialWriteChar (hCom, 0x5A);
		Sleep(1000);

		//Направление на север
		FormPorts->SerialWriteChar (hCom, 0x5E);
		//Направление на восток
		MessageDlg(	"Направте компа на восток", mtError,	TMsgDlgButtons() << mbOK, 0);
		FormPorts->SerialWriteChar (hCom, 0x5E);
		//Направление на юг
		MessageDlg(	"Направте компа на юг", mtError,	TMsgDlgButtons() << mbOK, 0);
		FormPorts->SerialWriteChar (hCom, 0x5E);
		//Направление на запад
		MessageDlg(	"Направте компа на запад", mtError,	TMsgDlgButtons() << mbOK, 0);
		FormPorts->SerialWriteChar (hCom, 0x5E);

		MessageDlg(	"Колибровка закончина", mtError,	TMsgDlgButtons() << mbOK, 0);

		FormPorts->SerialClosePort( hCom );
	}

}
//---------------------------------------------------------------------------






void __fastcall TForm1::ToolButton1Click(TObject *Sender)
{
	MapView->ViewScale = MapView->ViewScale*2;
	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
	MapView->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton2Click(TObject *Sender)
{
		MapView->ViewScale = MapView->ViewScale/2;
		Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
		MapView->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton3Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton4Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton5Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton6Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ToolButton7Click(TObject *Sender)
{
	if(MapWorkSetFree != NULL)
	{
		FreeLibrary(dllInstance);
		MapWorkSetFree = NULL;
	}

	dllInstance = LoadLibrary(L"MyDLL.dll");
	if(dllInstance)
	{
		MapWorkSetFree = (MType *)GetProcAddress(dllInstance, "_MapWorkSetFree");
		if(MapWorkSetFree)
		{
			MapWorkSetFree();

//			mapSetPathShell("C:\\Program Files (x86)\\Panorama\\Panorama11");
			mapSetPathShell("C:\\Program Files (x86)\\Panorama\\MapView11");
			TDOUBLEPOINT Centerpoint;
//			MapView->MapOpen("C:\\Users\\serg\\Desktop\\OSM_moscow\\RU-MOW.sit",1);
			MapView->GetCenter(Centerpoint, PP_GEO);

			MapWMSPopupDialog1->Execute();
//			MapView->MapOpen(wmsstring,1);
			MapView->Rendering = false;
			MapView->UpdatePictureBorder();

			MapView->SetCenter(Centerpoint,PP_GEO);
			MapView->ViewScale = 1000000;
			Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
			MapView->Rendering = true;

			MapView->Repaint();
/*
			char wmsstring[2048] = "WMTS#Type=UTMS&IP=http://ecn.t0.tiles.virtualearth.net/tiles/a&ID1=VirtualEarthSat&Name1=VirtualEarthSat&Matrix=urn:ogc:def:wkss:OGC:1.0:GoogleMapsCompatible";
			mapSetPathShell("C:\\Program Files (x86)\\Panorama\\Panorama11");
			mapSetPathShell("C:\\Program Files (x86)\\Panorama\\MapView11");
			TDOUBLEPOINT Centerpoint;
			MapView->MapOpen("C:\\Users\\serg\\Desktop\\OSM_moscow\\RU-MOW.sit",1);
			MapView->GetCenter(Centerpoint, PP_GEO);

			MapView->MapOpen(wmsstring,1);
			MapView->Rendering = false;
			MapView->UpdatePictureBorder();

			MapView->SetCenter(Centerpoint,PP_GEO);
			MapView->ViewScale = 100000;
			Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
			MapView->Rendering = true;

			MapView->Repaint();
*/
		}
		else
		{
			ShowMessage("Функция 'MapWorkSetFree' недоступна");
			return;
		}
	}
	else
	{
		ShowMessage("Не удалось загрузить MYDLL.DLL");
		return;
	}
/*
	MapView->WriteLogAccess(false, false);

	SetCurrentDir(ExtractFilePath(Application->ExeName));

	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
	//Позиционируем вновь открываемую карту по центру
	DOUBLEPOINT XY1, XY2;
	XY1.X = Mapproc::mapGetMapX1(MapView->MapHandle);
	XY1.Y = Mapproc::mapGetMapY1(MapView->MapHandle);
	XY2.X = Mapproc::mapGetMapX2(MapView->MapHandle);
	XY2.Y = Mapproc::mapGetMapY2(MapView->MapHandle);
	Move_To_Point(XY2.X-(XY2.X-XY1.X)/2, XY2.Y-(XY2.Y-XY1.Y)/2);
	MapView->Rendering = true;
*/
	MapView->Repaint();
/*
	MapWMSBuildURLDialog1->Execute();
*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton8Click(TObject *Sender)
{
	if(MapWorkSetFree != NULL)
	{
		FreeLibrary(dllInstance);
		MapWorkSetFree = NULL;
	}

	dllInstance = LoadLibrary(L"MyDLL.dll");
	if(dllInstance)
	{
		MapWorkSetFree = (MType *)GetProcAddress(dllInstance, "_MapWorkSetFree");
		if(MapWorkSetFree)
		{
			MapWorkSetFree();

//			mapSetPathShell("C:\\Program Files (x86)\\Panorama\\Panorama11");
			mapSetPathShell("C:\\Program Files (x86)\\Panorama\\MapView11");

			TDOUBLEPOINT Centerpoint;
			MapView->GetCenter(Centerpoint, PP_GEO);

			MapWMSBuildURLDialog1->Execute();
			MapView->MapOpen(MapWMSBuildURLDialog1->WMSConnectionString, true);
			MapView->Rendering = false;
			MapView->UpdatePictureBorder();

			MapView->SetCenter(Centerpoint,PP_GEO);
			MapView->ViewScale = 1000000;
			Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
			MapView->Rendering = true;

			MapView->Repaint();
		}
		else
		{
			ShowMessage("Функция 'MapWorkSetFree' недоступна");
			return;
		}
	}
	else
	{
		ShowMessage("Не удалось загрузить MYDLL.DLL");
		return;
	}

	MapView->Repaint();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	MapView->ViewScale = pow(10, (ComboBox1->ItemIndex));
	Scalle->Caption = "Масштаб: 1:" + IntToStr(MapView->ViewScale);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SettingCOMCMPSClick(TObject *Sender)
{
	FormPorts->Device = CMPS;
	FormPorts->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenCOMCMPSClick(TObject *Sender)
{
	FormPorts->Device = CMPS;
	FormPorts->PortOpen();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CloseCOMCMPSClick(TObject *Sender)
{
	FormPorts->Device = CMPS;
	FormPorts->PortClose();
}
//---------------------------------------------------------------------------




