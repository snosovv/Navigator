object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 842
  ClientWidth = 986
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnKeyUp = FormKeyUp
  OnMouseWheel = FormMouseWheel
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object validMessage: TLabel
    Left = 0
    Top = 809
    Width = 986
    Height = 13
    Align = alBottom
    Caption = '0'
    ExplicitWidth = 6
  end
  object Image1: TImage
    Left = 448
    Top = 376
    Width = 105
    Height = 105
  end
  object Panel1: TPanel
    Left = 808
    Top = 0
    Width = 178
    Height = 809
    Align = alRight
    BorderStyle = bsSingle
    TabOrder = 0
    object GroupBoxGPS: TGroupBox
      Left = 1
      Top = 1
      Width = 172
      Height = 248
      Align = alTop
      Caption = 'GPS/GLONASS'
      TabOrder = 0
      object g_Height: TLabel
        Left = 80
        Top = 170
        Width = 6
        Height = 13
        Caption = '0'
      end
      object g_Bearing: TLabel
        Left = 80
        Top = 150
        Width = 6
        Height = 13
        Caption = '0'
      end
      object g_Speed: TLabel
        Left = 80
        Top = 130
        Width = 6
        Height = 13
        Caption = '0'
      end
      object g_Longitude: TLabel
        Left = 80
        Top = 110
        Width = 16
        Height = 13
        Caption = '0.0'
      end
      object g_Latitude: TLabel
        Left = 80
        Top = 90
        Width = 16
        Height = 13
        Caption = '0.0'
      end
      object g_Time: TLabel
        Left = 80
        Top = 70
        Width = 6
        Height = 13
        Caption = '0'
      end
      object g_Date: TLabel
        Left = 80
        Top = 50
        Width = 6
        Height = 13
        Caption = '0'
      end
      object g_View: TLabel
        Left = 110
        Top = 10
        Width = 6
        Height = 13
        BiDiMode = bdLeftToRight
        Caption = '0'
        ParentBiDiMode = False
      end
      object g_TotalSat: TLabel
        Left = 80
        Top = 10
        Width = 6
        Height = 13
        BiDiMode = bdRightToLeft
        Caption = '0'
        ParentBiDiMode = False
      end
      object Label3: TLabel
        Left = 8
        Top = 10
        Width = 60
        Height = 13
        Caption = 'Sat (visible):'
      end
      object Label12: TLabel
        Left = 8
        Top = 30
        Width = 26
        Height = 13
        Caption = 'Valid:'
      end
      object Label10: TLabel
        Left = 8
        Top = 50
        Width = 30
        Height = 13
        Caption = #1044#1072#1090#1072':'
      end
      object Label223: TLabel
        Left = 8
        Top = 70
        Width = 34
        Height = 13
        Caption = #1042#1088#1077#1084#1103':'
      end
      object Label14: TLabel
        Left = 8
        Top = 90
        Width = 44
        Height = 13
        Caption = #1064#1080#1088#1086#1090#1072':'
      end
      object Label4: TLabel
        Left = 8
        Top = 110
        Width = 47
        Height = 13
        Caption = #1044#1086#1083#1075#1086#1090#1072':'
      end
      object Label6: TLabel
        Left = 8
        Top = 130
        Width = 52
        Height = 13
        Caption = #1057#1082#1086#1088#1086#1089#1090#1100':'
      end
      object Label8: TLabel
        Left = 8
        Top = 150
        Width = 28
        Height = 13
        Caption = #1050#1091#1088#1089':'
      end
      object Label2: TLabel
        Left = 8
        Top = 170
        Width = 41
        Height = 13
        Caption = #1042#1099#1089#1086#1090#1072':'
      end
      object BitBtn1: TBitBtn
        Left = 110
        Top = 30
        Width = 55
        Height = 17
        Caption = '->'
        TabOrder = 0
        OnClick = BitBtn1Click
      end
      object g_GpsInfoTrusted: TCheckBox
        Left = 80
        Top = 30
        Width = 17
        Height = 17
        TabOrder = 1
      end
      object Button1: TButton
        Left = 2
        Top = 196
        Width = 168
        Height = 25
        Align = alBottom
        Caption = #1057#1090#1072#1088#1090
        TabOrder = 2
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 2
        Top = 221
        Width = 168
        Height = 25
        Align = alBottom
        Caption = #1057#1090#1086#1087
        TabOrder = 3
        OnClick = Button2Click
      end
    end
    object GroupBoxSatelit: TGroupBox
      Left = 1
      Top = 592
      Width = 172
      Height = 212
      Align = alBottom
      Caption = #1057#1087#1091#1090#1085#1080#1082
      TabOrder = 1
      object Label9: TLabel
        Left = 8
        Top = 10
        Width = 47
        Height = 13
        Caption = #1044#1086#1083#1075#1086#1090#1072':'
      end
      object UPK: TLabel
        Left = 75
        Top = 150
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label11: TLabel
        Left = 8
        Top = 150
        Width = 66
        Height = 13
        Caption = #1059#1075'. '#1087#1086#1074'. '#1082#1086#1085':'
      end
      object UM: TLabel
        Left = 75
        Top = 90
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label7: TLabel
        Left = 8
        Top = 90
        Width = 60
        Height = 13
        Caption = #1059#1075#1086#1083' '#1084#1077#1089#1090#1072':'
      end
      object Label5: TLabel
        Left = 8
        Top = 30
        Width = 40
        Height = 13
        Caption = #1040#1079#1080#1084#1091#1090':'
      end
      object Az: TLabel
        Left = 75
        Top = 31
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LatSat: TEdit
        Left = 90
        Top = 10
        Width = 75
        Height = 24
        Color = clHighlight
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clYellow
        Font.Height = -13
        Font.Name = 'Fixedsys'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Text = '36,0'
      end
      object UgolPovorotaConvertera: TTrackBar
        Left = 8
        Top = 169
        Width = 165
        Height = 36
        LineSize = 10
        Max = 360
        Min = -360
        PageSize = 0
        Frequency = 10
        TabOrder = 1
      end
      object Ugolmesta: TTrackBar
        Left = 3
        Top = 109
        Width = 165
        Height = 32
        LineSize = 10
        Max = 360
        Min = -360
        PageSize = 0
        Frequency = 10
        TabOrder = 2
      end
      object Azimut: TTrackBar
        Left = 8
        Top = 50
        Width = 165
        Height = 36
        LineSize = 10
        Max = 360
        Min = -360
        PageSize = 0
        Frequency = 10
        TabOrder = 3
      end
    end
    object GroupBoxCMPS: TGroupBox
      Left = 1
      Top = 249
      Width = 172
      Height = 327
      Align = alTop
      Caption = #1050#1086#1084#1087#1072#1089
      TabOrder = 2
      object LabelMagRawY: TLabel
        Left = 2
        Top = 130
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelAccelRawZ: TLabel
        Left = 2
        Top = 210
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelAccelRawY: TLabel
        Left = 2
        Top = 190
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelMagRawZ: TLabel
        Left = 2
        Top = 150
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelMagRawX: TLabel
        Left = 2
        Top = 110
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelRoll: TLabel
        Left = 2
        Top = 70
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelPitch: TLabel
        Left = 2
        Top = 90
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label_Angle_16_Bit: TLabel
        Left = 2
        Top = 50
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelVersion: TLabel
        Left = 2
        Top = 10
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label_Angle_8_Bit: TLabel
        Left = 2
        Top = 30
        Width = 6
        Height = 13
        Caption = '0'
      end
      object LabelAccelRawX: TLabel
        Left = 2
        Top = 170
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Button3: TButton
        Left = 2
        Top = 225
        Width = 168
        Height = 25
        Align = alBottom
        Caption = #1057#1090#1072#1088#1090' CMPS'
        TabOrder = 0
        OnClick = Button3Click
      end
      object Button5: TButton
        Left = 2
        Top = 250
        Width = 168
        Height = 25
        Align = alBottom
        Caption = #1050#1086#1083#1080#1073#1088#1086#1074#1082#1072' CMPS'
        TabOrder = 1
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 2
        Top = 275
        Width = 168
        Height = 25
        Align = alBottom
        Caption = #1042#1077#1088#1085#1091#1090#1100' '#1082' '#1079#1072#1074#1086#1076#1089#1082#1080#1084' '#1091#1089#1090#1072#1085#1086#1074#1082#1072#1084
        TabOrder = 2
        OnClick = Button6Click
      end
      object Button7: TButton
        Left = 2
        Top = 300
        Width = 168
        Height = 25
        Align = alBottom
        Caption = #1057#1090#1086#1087
        TabOrder = 3
        OnClick = Button2Click
      end
    end
  end
  object Scalle: TPanel
    Left = 0
    Top = 822
    Width = 986
    Height = 20
    Align = alBottom
    Alignment = taLeftJustify
    Caption = #1052#1072#1089#1096#1090#1072#1073': 1:1000000'
    Color = clWhite
    TabOrder = 1
    ExplicitTop = 815
    object LBLL: TLabel
      Left = 176
      Top = 3
      Width = 250
      Height = 13
      Caption = #1064#1080#1088#1086#1090#1072': 000'#176'00'#39'00,00"     '#1044#1086#1083#1075#1086#1090#1072': 000'#176'00'#39'00,00"'
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 808
    Height = 809
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = #1050#1072#1088#1090#1072
      object MapView: TMapView
        Left = 0
        Top = 29
        Width = 800
        Height = 615
        Hint = #1050#1072#1088#1090#1072
        Margins.Left = 0
        Margins.Top = 0
        Margins.Right = 0
        Margins.Bottom = 0
        HorzScrollBar.Increment = 16
        VertScrollBar.Increment = 16
        Rendering = True
        BackStretch = True
        BackTile = True
        BackColor = clSilver
        PrintScale = 100000
        PlaceOut = PP_PLANE
        MapBright = 0
        MapContrast = 0
        MapContour = False
        FocusSetAuto = True
        OnMapPaintObject = MapViewMapPaintObject
        Align = alClient
        AutoSize = True
        DockSite = True
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        TabStop = True
        OnKeyDown = MapViewKeyDown
        OnKeyPress = MapViewKeyPress
        OnKeyUp = MapViewKeyUp
        OnMouseDown = MapViewMouseDown
        OnMouseMove = MapViewMouseMove
        OnMouseUp = MapViewMouseUp
        OnBuildMtrProcess = MapViewBuildMtrProcess
        OnMapSortProcess = MapViewMapSortProcess
        OnAppendSite = MapViewAppendSite
        MapView = True
        OleVisible = True
        ViewScale = 0
        MapWinAPI = False
        PropertyFont.Charset = DEFAULT_CHARSET
        PropertyFont.Color = clWindowText
        PropertyFont.Height = -11
        PropertyFont.Name = 'Tahoma'
        PropertyFont.Style = []
        GroupEnable = False
        ErrorHeight = -111111.000000000000000000
        PrecisionHeight = False
        MapMtrs.MapMtr = ()
        MapMtqs.MapMtq = ()
        MapSites.MapSite = ()
        MapRsts.MapRst = ()
        MapWMS.MapWMS = ()
      end
      object ToolBar1: TToolBar
        Left = 0
        Top = 0
        Width = 800
        Height = 29
        Caption = 'ToolBar1'
        Images = ImageList1
        TabOrder = 1
        object ToolButton1: TToolButton
          Left = 0
          Top = 0
          Caption = 'ToolButton1'
          ImageIndex = 3
          OnClick = ToolButton1Click
        end
        object ToolButton2: TToolButton
          Left = 23
          Top = 0
          Caption = 'ToolButton2'
          ImageIndex = 4
          OnClick = ToolButton2Click
        end
        object ToolButton3: TToolButton
          Left = 46
          Top = 0
          Caption = 'ToolButton3'
          ImageIndex = 2
          OnClick = ToolButton3Click
        end
        object ToolButton4: TToolButton
          Left = 69
          Top = 0
          Caption = 'ToolButton4'
          ImageIndex = 5
          OnClick = ToolButton4Click
        end
        object ToolButton5: TToolButton
          Left = 92
          Top = 0
          Caption = 'ToolButton5'
          ImageIndex = 6
          OnClick = ToolButton5Click
        end
        object ToolButton6: TToolButton
          Left = 115
          Top = 0
          Caption = 'ToolButton6'
          ImageIndex = 1
          OnClick = ToolButton6Click
        end
        object ToolButton7: TToolButton
          Left = 138
          Top = 0
          Caption = 'ToolButton7'
          ImageIndex = 0
          OnClick = ToolButton7Click
        end
        object ToolButton8: TToolButton
          Left = 161
          Top = 0
          Caption = 'ToolButton8'
          ImageIndex = 0
          OnClick = ToolButton8Click
        end
        object ComboBox1: TComboBox
          Left = 184
          Top = 0
          Width = 145
          Height = 21
          ItemIndex = 0
          TabOrder = 0
          Text = '1:1'
          OnChange = ComboBox1Change
          Items.Strings = (
            '1:1'
            '1:10'
            '1:100'
            '1:1000'
            '1:10000'
            '1:100000'
            '1:1000000'
            '1:10000000'
            '1:100000000'
            '1:1000000000'
            '1:10000000000')
        end
      end
      object MemoGood: TMemo
        Left = 0
        Top = 644
        Width = 800
        Height = 137
        Align = alBottom
        Lines.Strings = (
          'MemoGood')
        TabOrder = 2
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1042#1077#1082#1090#1086#1088
      ImageIndex = 1
      object Draw3D1: TDraw3D
        Left = 0
        Top = 0
        Width = 800
        Height = 781
        View3DOptions.Elevation = 135
        View3DOptions.HorizOffset = 100
        View3DOptions.Orthogonal = False
        View3DOptions.Rotation = 45
        View3DOptions.VertOffset = 100
        View3DOptions.Zoom = 50
        OnPaint = Draw3D1Paint
        Align = alClient
        TabOrder = 0
        OnMouseMove = Draw3D1MouseMove
        object Label13: TLabel
          Left = 8
          Top = 149
          Width = 56
          Height = 13
          Caption = 'Perspective'
        end
        object Label15: TLabel
          Left = 8
          Top = 252
          Width = 26
          Height = 13
          Caption = 'Zoom'
        end
        object Label17: TLabel
          Left = 8
          Top = 168
          Width = 41
          Height = 13
          Caption = 'Rotation'
        end
        object Label18: TLabel
          Left = 8
          Top = 198
          Width = 14
          Height = 13
          Caption = 'Tilt'
        end
        object Label19: TLabel
          Left = 8
          Top = 222
          Width = 51
          Height = 13
          Caption = 'VertOffset'
        end
        object Label20: TLabel
          Left = 8
          Top = 15
          Width = 44
          Height = 13
          Caption = 'Elevation'
        end
        object Label21: TLabel
          Left = 8
          Top = 117
          Width = 54
          Height = 13
          Caption = 'Orthogonal'
        end
        object Label22: TLabel
          Left = 8
          Top = 90
          Width = 55
          Height = 13
          Caption = 'OrthoAngle'
        end
        object Label23: TLabel
          Left = 8
          Top = 63
          Width = 55
          Height = 13
          Caption = 'HorizOffset'
        end
        object Label24: TLabel
          Left = 8
          Top = 41
          Width = 48
          Height = 13
          Caption = 'FontZoom'
        end
        object CheckBox1: TCheckBox
          Left = 68
          Top = 309
          Width = 97
          Height = 17
          TabOrder = 0
        end
        object Elevation: TEdit
          Left = 68
          Top = 12
          Width = 75
          Height = 21
          TabOrder = 1
          Text = '0'
        end
        object FontZoom: TEdit
          Left = 68
          Top = 36
          Width = 75
          Height = 21
          TabOrder = 2
          Text = '0'
        end
        object HorizOffset: TEdit
          Left = 68
          Top = 60
          Width = 75
          Height = 21
          TabOrder = 3
          Text = '0'
        end
        object OrthoAngle: TEdit
          Left = 68
          Top = 87
          Width = 75
          Height = 21
          TabOrder = 4
          Text = '0'
        end
        object Orthogonal: TCheckBox
          Left = 70
          Top = 114
          Width = 97
          Height = 17
          TabOrder = 5
        end
        object Perspective: TEdit
          Left = 68
          Top = 141
          Width = 75
          Height = 21
          TabOrder = 6
          Text = '0'
        end
        object Rotation: TEdit
          Left = 68
          Top = 168
          Width = 75
          Height = 21
          TabOrder = 7
          Text = '0'
        end
        object Tilt: TEdit
          Left = 68
          Top = 195
          Width = 75
          Height = 21
          TabOrder = 8
          Text = '0'
        end
        object VertOffset: TEdit
          Left = 68
          Top = 222
          Width = 75
          Height = 21
          TabOrder = 9
          Text = '0'
        end
        object Zoom: TEdit
          Left = 68
          Top = 249
          Width = 75
          Height = 21
          TabOrder = 10
          Text = '0'
        end
        object Button4: TButton
          Left = 68
          Top = 276
          Width = 75
          Height = 25
          Caption = 'Button4'
          TabOrder = 11
          OnClick = Button4Click
        end
        object CheckBoxDrawRoom: TCheckBox
          Left = 70
          Top = 332
          Width = 97
          Height = 17
          TabOrder = 12
        end
        object CheckBoxGradient: TCheckBox
          Left = 70
          Top = 355
          Width = 97
          Height = 17
          TabOrder = 13
        end
        object CheckBoxDrawAxes: TCheckBox
          Left = 70
          Top = 378
          Width = 97
          Height = 17
          TabOrder = 14
        end
        object TrackBarZoom: TTrackBar
          Left = 160
          Top = 252
          Width = 150
          Height = 25
          Max = 200
          TabOrder = 15
          OnChange = TrackBarChange
        end
        object TrackBarVertOffset: TTrackBar
          Left = 160
          Top = 225
          Width = 150
          Height = 25
          Max = 1000
          TabOrder = 16
          OnChange = TrackBarChange
        end
        object TrackBarTilt: TTrackBar
          Left = 160
          Top = 188
          Width = 150
          Height = 25
          Max = 500
          TabOrder = 17
          OnChange = TrackBarChange
        end
        object TrackBarRotation: TTrackBar
          Left = 160
          Top = 164
          Width = 150
          Height = 21
          Max = 360
          TabOrder = 18
          OnChange = TrackBarChange
        end
        object TrackBarPerspective: TTrackBar
          Left = 160
          Top = 140
          Width = 150
          Height = 25
          Max = 360
          TabOrder = 19
          OnChange = TrackBarChange
        end
        object TrackBarOrthoAngle: TTrackBar
          Left = 160
          Top = 87
          Width = 150
          Height = 25
          Max = 360
          TabOrder = 20
          OnChange = TrackBarChange
        end
        object TrackBarHorizOffset: TTrackBar
          Left = 160
          Top = 63
          Width = 150
          Height = 25
          Max = 1000
          TabOrder = 21
          OnChange = TrackBarChange
        end
        object TrackBarFontZoom: TTrackBar
          Left = 160
          Top = 39
          Width = 150
          Height = 25
          Max = 200
          TabOrder = 22
          OnChange = TrackBarChange
        end
        object TrackBarElevation: TTrackBar
          Left = 160
          Top = 15
          Width = 150
          Height = 25
          Max = 360
          TabOrder = 23
          OnChange = TrackBarChange
        end
      end
    end
  end
  object OpenMapDialog: TOpenMapDialog
    Options = [ofHideReadOnly, ofFileMustExist]
    Title = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083' '#1082#1072#1088#1090#1099
    Preview = True
    DialogMode = dmNone
    Left = 40
    Top = 704
  end
  object MainMenu1: TMainMenu
    Left = 40
    Top = 656
    object Seting: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      object COMPort1: TMenuItem
        Caption = 'COM PORT'
        object COMGPS1: TMenuItem
          Caption = 'COM GPS'
          object SettingCOMGPS: TMenuItem
            Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1087#1086#1088#1090#1072'...'
            OnClick = N11Click
          end
          object OpenCOMGPS: TMenuItem
            Caption = #1054#1090#1082#1088#1099#1090#1100' '#1087#1086#1088#1090
            OnClick = OpenPortClick
          end
          object CloseCOMGPS: TMenuItem
            Caption = #1047#1072#1082#1088#1099#1090#1100' '#1087#1086#1088#1090
            OnClick = ClosePortClick
          end
        end
        object COMCMPS1: TMenuItem
          Caption = 'COM CMPS'
          object SettingCOMCMPS: TMenuItem
            Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1087#1086#1088#1090#1072'...'
            OnClick = SettingCOMCMPSClick
          end
          object OpenCOMCMPS: TMenuItem
            Caption = #1054#1090#1082#1088#1099#1090#1100' '#1087#1086#1088#1090
            OnClick = OpenCOMCMPSClick
          end
          object CloseCOMCMPS: TMenuItem
            Caption = #1047#1072#1082#1088#1099#1090#1100' '#1087#1086#1088#1090
            OnClick = CloseCOMCMPSClick
          end
        end
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object N2: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100' '#1082#1072#1088#1090#1091'...'
        OnClick = N2Click
      end
    end
  end
  object axMapPointPictureToGeo: TMapPoint
    PlaceInp = PP_PICTURE
    PlaceOut = PP_GEO
    Left = 160
    Top = 704
  end
  object axMapPointGeoToPicture: TMapPoint
    PlaceInp = PP_GEO
    PlaceOut = PP_PICTURE
    Left = 120
    Top = 704
  end
  object axMapPointGeoToPlane: TMapPoint
    PlaceInp = PP_GEO
    PlaceOut = PP_PLANE
    Left = 280
    Top = 704
  end
  object axMapPointPlaneToGeo: TMapPoint
    PlaceInp = PP_PLANE
    PlaceOut = PP_GEO
    Left = 240
    Top = 704
  end
  object axMapPointPictureToPlane: TMapPoint
    PlaceInp = PP_PICTURE
    PlaceOut = PP_PLANE
    Left = 200
    Top = 704
  end
  object axMapPointPlaneToPicture: TMapPoint
    PlaceInp = PP_PLANE
    PlaceOut = PP_PICTURE
    Left = 80
    Top = 704
  end
  object MapWMSPopupDialog1: TMapWMSPopupDialog
    MapView = MapView
    PopupLeft = 0
    PopupTop = 0
    Left = 320
    Top = 704
  end
  object ImageList1: TImageList
    Left = 88
    Top = 656
    Bitmap = {
      494C0101070008004C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B3C8C8
      C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E86060
      60BD484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B3C8C8
      C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8484848B3484848B3484848B300000000484848B3484848B34848
      48B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8484848B3484848B3484848B300000000484848B3484848B3C8C8
      C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8C8C8C8E8484848B3484848B300000000484848B3484848B34848
      48B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B3C8C8
      C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3A8A8A8DBC8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B3C8C8
      C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000484848B54848
      48B5484848B5484848B5484848B5484848B5484848B5484848B5484848B54848
      48B5484848B5484848B5484848B5000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B30000000000000000484848B5484848B54848
      48B5484848B5484848B5484848B5484848B5484848B5484848B5484848B54848
      48B5484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5484848B5484848B5484848B5484848B5484848B5484848B54848
      48B5484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3C8C8C8E8484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5484848B5484848B5999999D6C8C8C8E9C8C8C8E9484848B54848
      48B5484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5484848B5C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E96161
      61BF484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E86F6F6FC44848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8
      C8E9484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8C8C8C8E8484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8
      C8E9C8C8C8E9484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8C8C8C8E8484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5888888CFC8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8
      C8E9C8C8C8E9484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E84F4F4FB6484848B3484848B3484848B300000000484848B3484848B3C8C8
      C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8C8C8C8E8484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8
      C8E9C8C8C8E9484848B5484848B5484848B500000000484848B3484848B34848
      48B3676767C0676767C0C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E86767
      67C0676767C0484848B3484848B3484848B300000000484848B3484848B34848
      48B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8C8C8C8E8484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8
      C8E9484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8
      C8E8C8C8C8E8C8C8C8E8484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5484848B5C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E9C8C8C8E94848
      48B5484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3B8B8B8E2C8C8C8E8C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5484848B5484848B5484848B5C8C8C8E9585858BB484848B54848
      48B5484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3C8C8C8E8484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5484848B5484848B5484848B5484848B5484848B5484848B54848
      48B5484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E8C8C8C8E84848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B5484848B54848
      48B5484848B5484848B5484848B5484848B5484848B5484848B5484848B54848
      48B5484848B5484848B5484848B5484848B500000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B300000000484848B3484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3484848B30000000000000000484848B54848
      48B5484848B5484848B5484848B5484848B5484848B5484848B5484848B54848
      48B5484848B5484848B5484848B5000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000484848B34848
      48B3484848B3484848B3484848B3484848B3484848B3484848B3484848B34848
      48B3484848B3484848B3484848B3000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000200000000100010000000000000100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000}
  end
  object MapWMSBuildURLDialog1: TMapWMSBuildURLDialog
    MapView = MapView
    Left = 360
    Top = 704
  end
end
