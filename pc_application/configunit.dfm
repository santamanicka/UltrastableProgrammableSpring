object ConfigureForm: TConfigureForm
  Left = 553
  Top = 287
  Width = 314
  Height = 327
  Caption = 'Configure Serial Port'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    306
    293)
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 0
    Width = 169
    Height = 53
  end
  object Label1: TLabel
    Left = 12
    Top = 8
    Width = 55
    Height = 13
    Caption = 'COMM Port'
  end
  object Label2: TLabel
    Left = 12
    Top = 32
    Width = 56
    Height = 13
    Caption = 'BAUD Rate'
  end
  object Label3: TLabel
    Left = 8
    Top = 60
    Width = 72
    Height = 13
    Caption = 'Display Scaling'
  end
  object OKButton: TButton
    Left = 228
    Top = 4
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
  end
  object BaudSelectorBox: TComboBox
    Left = 80
    Top = 28
    Width = 85
    Height = 21
    ItemHeight = 13
    ItemIndex = 2
    TabOrder = 1
    Text = '38400'
    OnChange = ChangeBAUDRateExecute
    Items.Strings = (
      '9600'
      '19200'
      '38400'
      '57600')
  end
  object CommPortSelectorBox: TComboBox
    Left = 80
    Top = 4
    Width = 85
    Height = 21
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 2
    Text = '1'
    OnChange = ChangeCOMMPortExecute
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12'
      '13'
      '14'
      '15'
      '16')
  end
  object Memo1: TMemo
    Left = 4
    Top = 132
    Width = 297
    Height = 157
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 3
  end
  object RobotScaleEdit: TMaskEdit
    Left = 88
    Top = 56
    Width = 77
    Height = 21
    TabOrder = 4
    Text = '2.0'
  end
  object StaticText1: TStaticText
    Left = 140
    Top = 88
    Width = 58
    Height = 17
    Caption = 'StaticText1'
    TabOrder = 5
  end
  object ActionList1: TActionList
    Left = 192
    Top = 4
    object ChangeCOMMPort: TAction
      Caption = 'ChangeCOMMPort'
      OnExecute = ChangeCOMMPortExecute
    end
    object ChangeBAUDRate: TAction
      Caption = 'ChangeBAUDRate'
      OnExecute = ChangeBAUDRateExecute
    end
  end
end
