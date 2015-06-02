object FormPorts: TFormPorts
  Left = 202
  Top = 106
  Caption = #1055#1086#1089#1083#1077#1076#1086#1074#1072#1090#1077#1083#1100#1085#1099#1077' '#1087#1086#1088#1090#1099
  ClientHeight = 315
  ClientWidth = 387
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = ttitt
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label5: TLabel
    Left = 22
    Top = 8
    Width = 38
    Height = 16
    Caption = #1055#1086#1088#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 7
    Top = 40
    Width = 180
    Height = 217
    Caption = #1054#1089#1085#1086#1074#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
    TabOrder = 1
    object Label1: TLabel
      Left = 15
      Top = 24
      Width = 98
      Height = 13
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100' '#1087#1077#1088#1077#1076#1072#1095#1080
    end
    object Label3: TLabel
      Left = 15
      Top = 72
      Width = 66
      Height = 13
      Caption = #1041#1080#1090#1099' '#1076#1072#1085#1085#1099#1093
    end
    object Label2: TLabel
      Left = 15
      Top = 120
      Width = 48
      Height = 13
      Caption = #1063#1077#1090#1085#1086#1089#1090#1100
    end
    object Label4: TLabel
      Left = 15
      Top = 168
      Width = 78
      Height = 13
      Caption = #1057#1090#1086#1087#1086#1074#1099#1077' '#1073#1080#1090#1099
    end
    object CBBaudRate: TComboBox
      Left = 15
      Top = 40
      Width = 145
      Height = 21
      Style = csDropDownList
      TabOrder = 0
      Items.Strings = (
        '110'
        '300'
        '600'
        '1200'
        '2400'
        '4800'
        '9600'
        '14400'
        '19200'
        '38400'
        '56000'
        '57600'
        '115200'
        '128000'
        '256000')
    end
    object CBByteSize: TComboBox
      Left = 15
      Top = 88
      Width = 145
      Height = 21
      Style = csDropDownList
      TabOrder = 1
      Items.Strings = (
        '4'
        '5'
        '6'
        '7'
        '8')
    end
    object CBParity: TComboBox
      Left = 15
      Top = 136
      Width = 145
      Height = 21
      Style = csDropDownList
      TabOrder = 2
      Items.Strings = (
        #1053#1077#1090
        #1063#1077#1090
        #1053#1077#1095#1077#1090
        #1052#1072#1088#1082#1077#1088
        #1055#1088#1086#1073#1077#1083)
    end
    object CBStopBits: TComboBox
      Left = 15
      Top = 184
      Width = 145
      Height = 21
      Style = csDropDownList
      TabOrder = 3
      Items.Strings = (
        '1'
        '1,5'
        '2')
    end
  end
  object GroupBox2: TGroupBox
    Left = 199
    Top = 40
    Width = 180
    Height = 217
    Caption = #1048#1085#1090#1077#1088#1074#1072#1083#1099' '#1074#1088#1077#1084#1077#1085#1080' ('#1084#1089')'
    TabOrder = 2
    object Label6: TLabel
      Left = 15
      Top = 24
      Width = 153
      Height = 13
      Caption = #1052#1077#1078#1076#1091' '#1089#1080#1084#1074#1086#1083#1072#1084#1080' '#1087#1088#1080' '#1095#1090#1077#1085#1080#1080
    end
    object Label7: TLabel
      Left = 15
      Top = 96
      Width = 58
      Height = 13
      Caption = #1052#1085#1086#1078#1080#1090#1077#1083#1100
    end
    object Label10: TLabel
      Left = 96
      Top = 96
      Width = 53
      Height = 13
      Caption = #1050#1086#1085#1089#1090#1072#1085#1090#1072
    end
    object Label9: TLabel
      Left = 15
      Top = 168
      Width = 58
      Height = 13
      Caption = #1052#1085#1086#1078#1080#1090#1077#1083#1100
    end
    object Label11: TLabel
      Left = 96
      Top = 168
      Width = 53
      Height = 13
      Caption = #1050#1086#1085#1089#1090#1072#1085#1090#1072
    end
    object Label8: TLabel
      Left = 71
      Top = 72
      Width = 44
      Height = 13
      Caption = #1063#1090#1077#1085#1080#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 71
      Top = 144
      Width = 44
      Height = 13
      Caption = #1047#1072#1087#1080#1089#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EReadIntervalTimeout: TEdit
      Left = 16
      Top = 40
      Width = 145
      Height = 21
      TabOrder = 0
    end
    object EReadTotalTimeoutMultiplier: TEdit
      Left = 16
      Top = 112
      Width = 65
      Height = 21
      TabOrder = 1
    end
    object EReadTotalTimeoutConstant: TEdit
      Left = 96
      Top = 112
      Width = 65
      Height = 21
      TabOrder = 2
    end
    object EWriteTotalTimeoutConstant: TEdit
      Left = 96
      Top = 184
      Width = 65
      Height = 21
      TabOrder = 3
    end
    object EWriteTotalTimeoutMultiplier: TEdit
      Left = 16
      Top = 184
      Width = 65
      Height = 21
      TabOrder = 4
    end
  end
  object ComboBox1: TComboBox
    Left = 66
    Top = 10
    Width = 294
    Height = 21
    Style = csDropDownList
    Sorted = True
    TabOrder = 0
    OnCloseUp = ComboBox1CloseUp
  end
  object Button1: TButton
    Left = 7
    Top = 264
    Width = 180
    Height = 41
    Caption = #1063#1090#1077#1085#1080#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 200
    Top = 264
    Width = 179
    Height = 41
    Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
    Enabled = False
    TabOrder = 4
    OnClick = Button2Click
  end
  object TimerWrite: TTimer
    Enabled = False
    Interval = 50
    OnTimer = TimerWriteTimer
    Top = 8
  end
  object TimerRead: TTimer
    Enabled = False
    OnTimer = TimerReadTimer
    Left = 32
    Top = 8
  end
end
