object ProfileSwitchEditForm: TProfileSwitchEditForm
  Left = 170
  Top = 87
  BorderStyle = bsDialog
  Caption = 'Profile Switch Editor'
  ClientHeight = 513
  ClientWidth = 435
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel3: TBevel
    Left = 4
    Top = 29
    Width = 427
    Height = 284
    Style = bsRaised
  end
  object Bevel5: TBevel
    Left = 10
    Top = 273
    Width = 413
    Height = 33
  end
  object Bevel4: TBevel
    Left = 10
    Top = 213
    Width = 413
    Height = 33
  end
  object Bevel2: TBevel
    Left = 10
    Top = 153
    Width = 413
    Height = 33
  end
  object Bevel1: TBevel
    Left = 10
    Top = 93
    Width = 413
    Height = 33
  end
  object Label49: TLabel
    Left = 8
    Top = 4
    Width = 329
    Height = 19
    Caption = 'Conditional Profile Switchers for Profile No '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 78
    Top = 68
    Width = 90
    Height = 16
    Caption = 'Trigger Source'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 334
    Top = 68
    Width = 77
    Height = 16
    Caption = 'Alt Profile No'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label52: TLabel
    Left = 22
    Top = 100
    Width = 9
    Height = 19
    Caption = '1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label53: TLabel
    Left = 22
    Top = 160
    Width = 9
    Height = 19
    Caption = '2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label56: TLabel
    Left = 22
    Top = 221
    Width = 9
    Height = 19
    Caption = '3'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label59: TLabel
    Left = 22
    Top = 281
    Width = 9
    Height = 19
    Caption = '4'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label68: TLabel
    Left = 22
    Top = 132
    Width = 9
    Height = 19
    Caption = #175
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Symbol'
    Font.Style = []
    ParentFont = False
  end
  object Label62: TLabel
    Left = 22
    Top = 253
    Width = 9
    Height = 19
    Caption = #175
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Symbol'
    Font.Style = []
    ParentFont = False
  end
  object Label63: TLabel
    Left = 22
    Top = 193
    Width = 9
    Height = 19
    Caption = #175
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Symbol'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 62
    Top = 104
    Width = 6
    Height = 13
    Caption = 'If'
  end
  object Label4: TLabel
    Left = 222
    Top = 104
    Width = 100
    Height = 13
    Caption = 'Switch To Profile No:'
  end
  object Label5: TLabel
    Left = 222
    Top = 164
    Width = 100
    Height = 13
    Caption = 'Switch To Profile No:'
  end
  object Label6: TLabel
    Left = 42
    Top = 164
    Width = 29
    Height = 13
    Caption = 'Else If'
  end
  object Label7: TLabel
    Left = 222
    Top = 224
    Width = 100
    Height = 13
    Caption = 'Switch To Profile No:'
  end
  object Label9: TLabel
    Left = 222
    Top = 284
    Width = 100
    Height = 13
    Caption = 'Switch To Profile No:'
  end
  object Label8: TLabel
    Left = 42
    Top = 224
    Width = 29
    Height = 13
    Caption = 'Else If'
  end
  object Label10: TLabel
    Left = 42
    Top = 284
    Width = 29
    Height = 13
    Caption = 'Else If'
  end
  object Bevel6: TBevel
    Left = 4
    Top = 312
    Width = 427
    Height = 98
    Style = bsRaised
  end
  object Label12: TLabel
    Left = 10
    Top = 40
    Width = 143
    Height = 16
    Caption = 'Jump to alternate Profile'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label13: TLabel
    Left = 10
    Top = 320
    Width = 183
    Height = 16
    Caption = 'Incriment or Deincriment Profile'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label11: TLabel
    Left = 14
    Top = 348
    Width = 87
    Height = 13
    Caption = 'Incriment Profile If:'
  end
  object Label14: TLabel
    Left = 14
    Top = 380
    Width = 104
    Height = 13
    Caption = 'De-Incriment Profile If:'
  end
  object Label15: TLabel
    Left = 274
    Top = 348
    Width = 89
    Height = 13
    Caption = 'New Profile will be:'
  end
  object Label16: TLabel
    Left = 274
    Top = 380
    Width = 89
    Height = 13
    Caption = 'New Profile will be:'
  end
  object Bevel7: TBevel
    Left = 10
    Top = 417
    Width = 413
    Height = 60
  end
  object AltproTriggerlist1: TComboBox
    Left = 76
    Top = 100
    Width = 141
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 0
    OnChange = TriggerListWarningExecute
  end
  object AltProTargetlist1: TComboBox
    Left = 330
    Top = 100
    Width = 89
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = '0'
  end
  object AltProTargetlist2: TComboBox
    Left = 334
    Top = 160
    Width = 85
    Height = 21
    ItemHeight = 13
    TabOrder = 2
    Text = '0'
  end
  object AltproTriggerlist2: TComboBox
    Left = 76
    Top = 160
    Width = 141
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 3
    OnChange = TriggerListWarningExecute
  end
  object AltProTargetlist3: TComboBox
    Left = 334
    Top = 219
    Width = 85
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = '0'
  end
  object AltproTriggerlist3: TComboBox
    Left = 76
    Top = 219
    Width = 141
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 5
    OnChange = TriggerListWarningExecute
  end
  object AltProTargetlist4: TComboBox
    Left = 334
    Top = 279
    Width = 85
    Height = 21
    ItemHeight = 13
    TabOrder = 6
    Text = '0'
  end
  object AltproTriggerlist4: TComboBox
    Left = 76
    Top = 279
    Width = 141
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 7
    OnChange = TriggerListWarningExecute
    Items.Strings = (
      '')
  end
  object Button1: TButton
    Left = 350
    Top = 481
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 8
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 270
    Top = 481
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 9
    OnClick = Button2Click
  end
  object IncrimentTriggerBox: TComboBox
    Left = 128
    Top = 344
    Width = 141
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 10
    OnChange = TriggerListWarningExecute
  end
  object DeincrimentTriggerBox: TComboBox
    Left = 128
    Top = 376
    Width = 141
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 11
    OnChange = TriggerListWarningExecute
  end
  object Button3: TButton
    Left = 10
    Top = 481
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 12
    OnClick = Button3Click
  end
  object StaticText1: TStaticText
    Left = 16
    Top = 424
    Width = 7
    Height = 17
    Caption = ' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
  end
  object StaticText2: TStaticText
    Left = 16
    Top = 452
    Width = 7
    Height = 17
    Caption = ' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
  end
  object ActionList1: TActionList
    Left = 224
    Top = 480
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object SaveAndClose: TAction
      Caption = 'SaveAndClose'
      OnExecute = SaveAndCloseExecute
    end
    object TriggerListWarning: TAction
      Caption = 'TriggerListWarning'
      OnExecute = TriggerListWarningExecute
    end
  end
end
