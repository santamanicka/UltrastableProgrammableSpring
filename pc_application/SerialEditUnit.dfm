object SerialEditForm: TSerialEditForm
  Left = 294
  Top = 221
  BorderStyle = bsDialog
  Caption = 'RS232 Serial I/O Editor'
  ClientHeight = 352
  ClientWidth = 578
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel2: TBevel
    Left = 4
    Top = 172
    Width = 569
    Height = 137
  end
  object Bevel1: TBevel
    Left = 4
    Top = 32
    Width = 569
    Height = 137
  end
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 229
    Height = 19
    Caption = 'RS232 Serial I/O for Profile No '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 12
    Top = 60
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 1'
  end
  object Label3: TLabel
    Left = 12
    Top = 88
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 2'
  end
  object Label4: TLabel
    Left = 12
    Top = 116
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 3'
  end
  object Label5: TLabel
    Left = 12
    Top = 144
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 4'
  end
  object Label6: TLabel
    Left = 12
    Top = 200
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 1'
  end
  object Label7: TLabel
    Left = 12
    Top = 228
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 2'
  end
  object Label8: TLabel
    Left = 12
    Top = 256
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 3'
  end
  object Label9: TLabel
    Left = 12
    Top = 284
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 4'
  end
  object Label10: TLabel
    Left = 12
    Top = 36
    Width = 61
    Height = 16
    Caption = 'Group A:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label11: TLabel
    Left = 12
    Top = 176
    Width = 61
    Height = 16
    Caption = 'Group B:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label12: TLabel
    Left = 296
    Top = 60
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 1'
  end
  object Label13: TLabel
    Left = 296
    Top = 88
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 2'
  end
  object Label14: TLabel
    Left = 296
    Top = 116
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 3'
  end
  object Label15: TLabel
    Left = 296
    Top = 144
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 4'
  end
  object Label16: TLabel
    Left = 296
    Top = 284
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 4'
  end
  object Label17: TLabel
    Left = 296
    Top = 256
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 3'
  end
  object Label18: TLabel
    Left = 296
    Top = 228
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 2'
  end
  object Label19: TLabel
    Left = 296
    Top = 200
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 1'
  end
  object VarOutBoxA1: TComboBox
    Left = 140
    Top = 56
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 0
    Text = 'VarOutBoxA1'
  end
  object VarOutBoxA2: TComboBox
    Left = 140
    Top = 84
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 1
    Text = 'ComboBox1'
  end
  object VarOutBoxA3: TComboBox
    Left = 140
    Top = 112
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 2
    Text = 'ComboBox1'
  end
  object VarOutBoxA4: TComboBox
    Left = 140
    Top = 140
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 3
    Text = 'ComboBox1'
  end
  object Button1: TButton
    Left = 416
    Top = 320
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 496
    Top = 320
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
    OnClick = Button2Click
  end
  object VarOutBoxB1: TComboBox
    Left = 140
    Top = 196
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 6
    Text = 'ComboBox1'
  end
  object VarOutBoxB2: TComboBox
    Left = 140
    Top = 224
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 7
    Text = 'ComboBox1'
  end
  object VarOutBoxB3: TComboBox
    Left = 140
    Top = 252
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 8
    Text = 'ComboBox1'
  end
  object VarOutBoxB4: TComboBox
    Left = 140
    Top = 280
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 9
    Text = 'ComboBox1'
  end
  object TrigOutBoxA1: TComboBox
    Left = 420
    Top = 56
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 10
    Text = 'ComboBox1'
  end
  object TrigOutBoxA2: TComboBox
    Left = 420
    Top = 84
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 11
    Text = 'ComboBox1'
  end
  object TrigOutBoxA3: TComboBox
    Left = 420
    Top = 112
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 12
    Text = 'ComboBox1'
  end
  object TrigOutBoxA4: TComboBox
    Left = 420
    Top = 140
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 13
    Text = 'ComboBox1'
  end
  object TrigOutBoxB1: TComboBox
    Left = 420
    Top = 196
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 14
    Text = 'ComboBox1'
  end
  object TrigOutBoxB2: TComboBox
    Left = 420
    Top = 224
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 15
    Text = 'ComboBox1'
  end
  object TrigOutBoxB3: TComboBox
    Left = 420
    Top = 252
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 16
    Text = 'ComboBox1'
  end
  object TrigOutBoxB4: TComboBox
    Left = 420
    Top = 280
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 17
    Text = 'ComboBox1'
  end
  object Button3: TButton
    Left = 8
    Top = 320
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 18
    OnClick = Button3Click
  end
  object ActionList1: TActionList
    Left = 116
    Top = 316
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object SaveForm: TAction
      Caption = 'SaveForm'
      OnExecute = SaveFormExecute
    end
  end
end
