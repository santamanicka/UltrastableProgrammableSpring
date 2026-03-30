object AnalogIOForm: TAnalogIOForm
  Left = 155
  Top = 121
  Width = 281
  Height = 239
  Caption = 'Analog I/O Editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 186
    Height = 19
    Caption = 'Analog I/O for Profile No '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 12
    Top = 44
    Width = 99
    Height = 13
    Caption = 'Analog Out 1 Source'
  end
  object Label3: TLabel
    Left = 12
    Top = 112
    Width = 99
    Height = 13
    Caption = 'Analog Out 2 Source'
  end
  object Label4: TLabel
    Left = 12
    Top = 72
    Width = 87
    Height = 13
    Caption = 'Analog Out 1 Gain'
  end
  object Label5: TLabel
    Left = 12
    Top = 140
    Width = 87
    Height = 13
    Caption = 'Analog Out 2 Gain'
  end
  object AnOutBox1: TComboBox
    Left = 120
    Top = 40
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 0
    Text = 'AnOutBox1'
  end
  object AnOutBox2: TComboBox
    Left = 120
    Top = 108
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 1
    Text = 'ComboBox1'
  end
  object Button1: TButton
    Left = 108
    Top = 172
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 188
    Top = 172
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
    OnClick = Button2Click
  end
  object GainEdit1: TEdit
    Left = 120
    Top = 68
    Width = 145
    Height = 21
    TabOrder = 4
    Text = 'GainEdit1'
  end
  object GainEdit2: TEdit
    Left = 120
    Top = 136
    Width = 145
    Height = 21
    TabOrder = 5
    Text = 'Edit1'
  end
  object DefaultButton: TButton
    Left = 8
    Top = 172
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 6
    OnClick = DefaultButtonClick
  end
  object ActionList1: TActionList
    Left = 208
    Top = 8
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
