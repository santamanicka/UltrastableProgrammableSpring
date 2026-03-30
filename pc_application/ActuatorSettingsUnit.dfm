object ActuatorSettingsForm: TActuatorSettingsForm
  Left = 469
  Top = 187
  Width = 283
  Height = 249
  Caption = 'Actuator Settings'
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
    Left = 28
    Top = 16
    Width = 68
    Height = 13
    Caption = 'Starting Profile'
  end
  object Label2: TLabel
    Left = 28
    Top = 44
    Width = 66
    Height = 13
    Caption = 'Starting Mode'
  end
  object Label3: TLabel
    Left = 28
    Top = 100
    Width = 76
    Height = 13
    Caption = 'CAN BUS Node'
  end
  object Label4: TLabel
    Left = 28
    Top = 72
    Width = 91
    Height = 13
    Caption = 'RS232 Serial Node'
  end
  object Label5: TLabel
    Left = 40
    Top = 128
    Width = 59
    Height = 13
    Caption = 'Delay period'
  end
  object StartProfileBox: TComboBox
    Left = 124
    Top = 12
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    Text = 'StartProfileBox'
  end
  object StartModeBox: TComboBox
    Left = 124
    Top = 40
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = 'ComboBox1'
  end
  object RS232NodeBox: TComboBox
    Left = 124
    Top = 68
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 2
    Text = 'ComboBox1'
  end
  object CANBUSNodeBox: TComboBox
    Left = 124
    Top = 96
    Width = 145
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 3
    Text = 'ComboBox1'
  end
  object OKButton: TButton
    Left = 192
    Top = 184
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 4
    OnClick = SaveAndCloseExecute
  end
  object CancelButton: TButton
    Left = 108
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
    OnClick = CancelAndCloseExecute
  end
  object DefaultButton: TButton
    Left = 8
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Defaults'
    TabOrder = 6
    OnClick = SetDefaultsExecute
  end
  object PassAlongCommandsBox: TCheckBox
    Left = 124
    Top = 156
    Width = 141
    Height = 17
    Caption = 'Pass Along Commands'
    TabOrder = 7
    OnClick = PassAlongCommandsBoxClick
  end
  object DelayValueBox: TEdit
    Left = 128
    Top = 128
    Width = 121
    Height = 21
    TabOrder = 8
    Text = '0'
  end
  object ActionList1: TActionList
    Left = 8
    Top = 4
    object SetupForm: TAction
      Caption = 'SaveAndClose'
      OnExecute = SetupFormExecute
    end
    object SaveAndClose: TAction
      Caption = 'SaveAndClose'
      OnExecute = SaveAndCloseExecute
    end
    object CancelAndClose: TAction
      Caption = 'CancelAndClose'
      OnExecute = CancelAndCloseExecute
    end
    object SetDefaults: TAction
      Caption = 'SetDefaults'
      OnExecute = SetDefaultsExecute
    end
  end
end
