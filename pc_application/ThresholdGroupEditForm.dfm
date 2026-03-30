object ThresholdGroupEditorForm: TThresholdGroupEditorForm
  Left = 310
  Top = 164
  Width = 329
  Height = 401
  Caption = 'Threshold Group Editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 2
    Top = 200
    Width = 315
    Height = 129
  end
  object Bevel2: TBevel
    Left = 2
    Top = 68
    Width = 315
    Height = 129
  end
  object Label10: TLabel
    Left = 12
    Top = 74
    Width = 297
    Height = 19
    AutoSize = False
    Caption = 'Positive Threshold (PT)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsItalic]
    ParentFont = False
  end
  object Label14: TLabel
    Left = 12
    Top = 238
    Width = 84
    Height = 13
    Caption = 'Threshold Source'
  end
  object Label15: TLabel
    Left = 12
    Top = 170
    Width = 63
    Height = 13
    Caption = 'Default Level'
  end
  object Label13: TLabel
    Left = 12
    Top = 270
    Width = 70
    Height = 13
    Caption = 'Enable Source'
  end
  object Label20: TLabel
    Left = 12
    Top = 206
    Width = 297
    Height = 19
    AutoSize = False
    Caption = 'NegativeThreshold (NT)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsItalic]
    ParentFont = False
  end
  object Label24: TLabel
    Left = 12
    Top = 106
    Width = 84
    Height = 13
    Caption = 'Threshold Source'
  end
  object Label25: TLabel
    Left = 12
    Top = 302
    Width = 55
    Height = 13
    Caption = 'NT1Default'
  end
  object Label22: TLabel
    Left = 12
    Top = 38
    Width = 74
    Height = 13
    Caption = 'Variable to Test'
  end
  object Label23: TLabel
    Left = 12
    Top = 138
    Width = 70
    Height = 13
    Caption = 'Enable Source'
  end
  object Label1: TLabel
    Left = 12
    Top = 6
    Width = 297
    Height = 19
    AutoSize = False
    Caption = 'Threshold Group'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object PT1DefaultEdit: TEdit
    Left = 104
    Top = 166
    Width = 57
    Height = 21
    HelpType = htKeyword
    HelpKeyword = 'Default'
    TabOrder = 0
    Text = '1024'
  end
  object PT1SourceList: TComboBox
    Left = 104
    Top = 34
    Width = 203
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 1
  end
  object PT1LevelList: TComboBox
    Left = 104
    Top = 102
    Width = 203
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 2
  end
  object PT1EnableList: TComboBox
    Left = 104
    Top = 134
    Width = 203
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 3
  end
  object NT1DefaultEdit: TEdit
    Left = 104
    Top = 298
    Width = 57
    Height = 21
    HelpType = htKeyword
    HelpKeyword = 'Default'
    TabOrder = 4
    Text = '-1024'
  end
  object NT1LevelList: TComboBox
    Left = 104
    Top = 234
    Width = 201
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 5
  end
  object NT1EnableList: TComboBox
    Left = 104
    Top = 266
    Width = 201
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 6
  end
  object OKButton: TButton
    Left = 152
    Top = 336
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 7
    OnClick = OKButtonClick
  end
  object CancelButton: TButton
    Left = 236
    Top = 336
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 8
    OnClick = CancelButtonClick
  end
  object StaticText1: TStaticText
    Left = 260
    Top = 8
    Width = 58
    Height = 17
    Caption = 'StaticText1'
    TabOrder = 9
  end
  object Button1: TButton
    Left = 8
    Top = 336
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 10
    OnClick = Button1Click
  end
  object ActionList1: TActionList
    Left = 288
    Top = 316
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object SaveAndExit: TAction
      Caption = 'SaveAndExit'
      OnExecute = SaveAndExitExecute
    end
    object CancelAndExit: TAction
      Caption = 'CancelAndExit'
    end
  end
end
