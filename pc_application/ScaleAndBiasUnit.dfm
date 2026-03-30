object ScaleAndBiasForm: TScaleAndBiasForm
  Left = 145
  Top = 115
  Width = 549
  Height = 347
  Caption = 'Scale and Bias Editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel5: TBevel
    Left = 8
    Top = 124
    Width = 525
    Height = 41
  end
  object Bevel4: TBevel
    Left = 8
    Top = 228
    Width = 525
    Height = 41
  end
  object Bevel3: TBevel
    Left = 8
    Top = 80
    Width = 525
    Height = 41
  end
  object Bevel2: TBevel
    Left = 8
    Top = 184
    Width = 525
    Height = 41
  end
  object Bevel1: TBevel
    Left = 8
    Top = 36
    Width = 525
    Height = 41
  end
  object Label2: TLabel
    Left = 16
    Top = 48
    Width = 98
    Height = 16
    Caption = 'Horizontal Scale'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 132
    Top = 48
    Width = 75
    Height = 13
    Caption = 'Source Variable'
  end
  object Label1: TLabel
    Left = 12
    Top = 8
    Width = 221
    Height = 19
    Caption = 'Scale and Bias for Profile No '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 380
    Top = 48
    Width = 64
    Height = 13
    Caption = 'Default Value'
  end
  object Label5: TLabel
    Left = 16
    Top = 196
    Width = 83
    Height = 16
    Caption = 'Vertical Scale'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 132
    Top = 196
    Width = 75
    Height = 13
    Caption = 'Source Variable'
  end
  object Label7: TLabel
    Left = 380
    Top = 196
    Width = 64
    Height = 13
    Caption = 'Default Value'
  end
  object Label8: TLabel
    Left = 16
    Top = 92
    Width = 90
    Height = 16
    Caption = 'Horizontal Bias'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 132
    Top = 92
    Width = 75
    Height = 13
    Caption = 'Source Variable'
  end
  object Label10: TLabel
    Left = 380
    Top = 92
    Width = 64
    Height = 13
    Caption = 'Default Value'
  end
  object Label11: TLabel
    Left = 16
    Top = 240
    Width = 75
    Height = 16
    Caption = 'Vertical Bias'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label12: TLabel
    Left = 132
    Top = 240
    Width = 75
    Height = 13
    Caption = 'Source Variable'
  end
  object Label13: TLabel
    Left = 380
    Top = 240
    Width = 64
    Height = 13
    Caption = 'Default Value'
  end
  object Label14: TLabel
    Left = 16
    Top = 136
    Width = 115
    Height = 16
    Caption = 'Horizontal EQ Point'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label15: TLabel
    Left = 132
    Top = 136
    Width = 75
    Height = 13
    Caption = 'Source Variable'
  end
  object Button1: TButton
    Left = 456
    Top = 280
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
    OnClick = Button1Click
  end
  object HScaleSourceBox: TComboBox
    Left = 220
    Top = 44
    Width = 145
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 1
    Text = 'HScaleSourceBox'
  end
  object HScaleEdit: TEdit
    Left = 448
    Top = 44
    Width = 73
    Height = 21
    TabOrder = 2
    Text = 'HScaleEdit'
  end
  object VScaleSourceBox: TComboBox
    Left = 220
    Top = 192
    Width = 145
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 3
    Text = 'ComboBox1'
  end
  object VScaleEdit: TEdit
    Left = 448
    Top = 192
    Width = 73
    Height = 21
    TabOrder = 4
    Text = 'Edit1'
  end
  object HBiasSourceBox: TComboBox
    Left = 220
    Top = 88
    Width = 145
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 5
    Text = 'ComboBox1'
  end
  object HBiasEdit: TEdit
    Left = 448
    Top = 88
    Width = 73
    Height = 21
    TabOrder = 6
    Text = 'Edit1'
  end
  object VBiasSourceBox: TComboBox
    Left = 220
    Top = 236
    Width = 145
    Height = 21
    DropDownCount = 20
    ItemHeight = 13
    TabOrder = 7
    Text = 'ComboBox1'
  end
  object VBiasEdit: TEdit
    Left = 448
    Top = 236
    Width = 73
    Height = 21
    TabOrder = 8
    Text = 'Edit1'
  end
  object EQEdit: TEdit
    Left = 220
    Top = 132
    Width = 73
    Height = 21
    TabOrder = 9
    Text = 'Edit1'
  end
  object Button2: TButton
    Left = 372
    Top = 280
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 10
    OnClick = Button2Click
  end
  object SetDefaultsButton: TButton
    Left = 12
    Top = 280
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 11
    OnClick = SetDefaultsButtonClick
  end
  object ActionList1: TActionList
    Left = 328
    Top = 280
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object SaveAndClose: TAction
      Caption = 'SaveAndClose'
      OnExecute = SaveAndCloseExecute
    end
  end
end
