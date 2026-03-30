object CANEditForm: TCANEditForm
  Left = 434
  Top = 143
  Width = 301
  Height = 389
  Caption = 'CAN Bus Editor'
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
    Top = 32
    Width = 285
    Height = 141
  end
  object Bevel1: TBevel
    Left = 4
    Top = 176
    Width = 285
    Height = 141
  end
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 202
    Height = 19
    Caption = 'CAN Bus I/O for Profile No '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 12
    Top = 64
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 1'
  end
  object Label2: TLabel
    Left = 12
    Top = 92
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 2'
  end
  object Label4: TLabel
    Left = 12
    Top = 120
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 1'
  end
  object Label5: TLabel
    Left = 12
    Top = 148
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 2'
  end
  object Label6: TLabel
    Left = 12
    Top = 208
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 1'
  end
  object Label7: TLabel
    Left = 12
    Top = 236
    Width = 119
    Height = 13
    Caption = 'Variable Output Source 2'
  end
  object Label8: TLabel
    Left = 12
    Top = 264
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 1'
  end
  object Label9: TLabel
    Left = 12
    Top = 292
    Width = 114
    Height = 13
    Caption = 'Trigger Output Source 2'
  end
  object Label12: TLabel
    Left = 12
    Top = 180
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
  object ComboBox1: TComboBox
    Left = 140
    Top = 60
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 0
    Text = 'ComboBox1'
  end
  object ComboBox2: TComboBox
    Left = 140
    Top = 88
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 1
    Text = 'ComboBox1'
  end
  object ComboBox3: TComboBox
    Left = 140
    Top = 116
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 2
    Text = 'ComboBox1'
  end
  object ComboBox4: TComboBox
    Left = 140
    Top = 144
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 3
    Text = 'ComboBox1'
  end
  object Button1: TButton
    Left = 132
    Top = 324
    Width = 75
    Height = 25
    Caption = 'OK'
    Enabled = False
    ModalResult = 1
    TabOrder = 4
  end
  object Button2: TButton
    Left = 212
    Top = 324
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
  end
  object ComboBox5: TComboBox
    Left = 140
    Top = 204
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 6
    Text = 'ComboBox1'
  end
  object ComboBox6: TComboBox
    Left = 140
    Top = 232
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 7
    Text = 'ComboBox1'
  end
  object ComboBox7: TComboBox
    Left = 140
    Top = 260
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 8
    Text = 'ComboBox1'
  end
  object ComboBox8: TComboBox
    Left = 140
    Top = 288
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 9
    Text = 'ComboBox1'
  end
  object ActionList1: TActionList
    Left = 80
    Top = 316
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
  end
end
