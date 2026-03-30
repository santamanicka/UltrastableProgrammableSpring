object DigitalIOForm: TDigitalIOForm
  Left = 154
  Top = 101
  Width = 273
  Height = 168
  Caption = 'Digital I/O Editor'
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
    Left = 4
    Top = 32
    Width = 257
    Height = 65
  end
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 180
    Height = 19
    Caption = 'Digital I/O for Profile No '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label12: TLabel
    Left = 12
    Top = 44
    Width = 75
    Height = 13
    Caption = 'ExOut 1 Source'
  end
  object Label2: TLabel
    Left = 12
    Top = 72
    Width = 75
    Height = 13
    Caption = 'ExOut 2 Source'
  end
  object ExOutBox1: TComboBox
    Left = 108
    Top = 40
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 0
    Text = 'ExOutBox1'
  end
  object ExOutBox2: TComboBox
    Left = 108
    Top = 68
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 1
    Text = 'ComboBox1'
  end
  object Button1: TButton
    Left = 104
    Top = 104
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 184
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
    OnClick = Button2Click
  end
  object DefaultButton: TButton
    Left = 8
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 4
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
