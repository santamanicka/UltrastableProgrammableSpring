object GroupTriggerForm: TGroupTriggerForm
  Left = 181
  Top = 302
  Width = 306
  Height = 220
  Caption = 'Group Trigger Editor'
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
    Width = 250
    Height = 19
    Caption = 'Group Triggers for Profile Group '
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
    Width = 79
    Height = 13
    Caption = 'Trigger Source 1'
  end
  object Label3: TLabel
    Left = 12
    Top = 72
    Width = 79
    Height = 13
    Caption = 'Trigger Source 2'
  end
  object Label4: TLabel
    Left = 12
    Top = 100
    Width = 79
    Height = 13
    Caption = 'Trigger Source 3'
  end
  object Label5: TLabel
    Left = 12
    Top = 128
    Width = 79
    Height = 13
    Caption = 'Trigger Source 4'
  end
  object SourceBox1: TComboBox
    Left = 112
    Top = 40
    Width = 181
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 0
    Text = 'SourceBox1'
  end
  object SourceBox2: TComboBox
    Left = 112
    Top = 68
    Width = 181
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 1
    Text = 'ComboBox1'
  end
  object SourceBox3: TComboBox
    Left = 112
    Top = 96
    Width = 181
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 2
    Text = 'ComboBox1'
  end
  object SourceBox4: TComboBox
    Left = 112
    Top = 124
    Width = 181
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 3
    Text = 'ComboBox1'
  end
  object Button1: TButton
    Left = 136
    Top = 156
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 216
    Top = 156
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
    OnClick = Button2Click
  end
  object DefaultButton: TButton
    Left = 8
    Top = 157
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 6
    OnClick = DefaultButtonClick
  end
  object ActionList1: TActionList
    Left = 268
    Top = 4
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
