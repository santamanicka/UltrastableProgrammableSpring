object MotorEnableForm: TMotorEnableForm
  Left = 141
  Top = 104
  Width = 362
  Height = 269
  Caption = 'Motor and Force Control enable settings'
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
    Left = 8
    Top = 112
    Width = 341
    Height = 85
  end
  object Bevel1: TBevel
    Left = 8
    Top = 32
    Width = 341
    Height = 77
  end
  object Title: TLabel
    Left = 8
    Top = 8
    Width = 316
    Height = 19
    Caption = 'Motor and Force Enable for Profile Group '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 44
    Width = 133
    Height = 13
    Caption = 'Enable Motor Power Source'
  end
  object Label3: TLabel
    Left = 16
    Top = 124
    Width = 136
    Height = 13
    Caption = 'Enable Force Control Source'
  end
  object Label4: TLabel
    Left = 16
    Top = 68
    Width = 325
    Height = 33
    AutoSize = False
    Caption = 
      'Motor Power Enable allows you to determine when the actuator wil' +
      'l apply power to the motor.  Normally this would be permanently ' +
      'on.'
    WordWrap = True
  end
  object Label5: TLabel
    Left = 16
    Top = 148
    Width = 325
    Height = 41
    AutoSize = False
    Caption = 
      'With Force Control enabled the actuator will output the force ge' +
      'nerated by the profile group.  When disabled it will produce zer' +
      'o force.'
    WordWrap = True
  end
  object MotorEnableBox: TComboBox
    Left = 164
    Top = 40
    Width = 181
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 0
    Text = 'MotorBox'
  end
  object DefaultButton: TButton
    Left = 8
    Top = 205
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 1
    OnClick = SetDefaultsExecute
  end
  object Button1: TButton
    Left = 192
    Top = 204
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 2
    OnClick = SaveAndExitExecute
  end
  object Button2: TButton
    Left = 272
    Top = 204
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
    OnClick = CancelAndExitExecute
  end
  object ForceEnableBox: TComboBox
    Left = 164
    Top = 120
    Width = 181
    Height = 21
    DropDownCount = 32
    ItemHeight = 13
    TabOrder = 4
    Text = 'ForceBox'
  end
  object ActionList1: TActionList
    Left = 116
    Top = 204
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object SaveForm: TAction
      Caption = 'SaveForm'
      OnExecute = SaveFormExecute
    end
    object SaveAndExit: TAction
      Caption = 'SaveAndExit'
      OnExecute = SaveAndExitExecute
    end
    object CancelAndExit: TAction
      Caption = 'CancelAndExit'
      OnExecute = CancelAndExitExecute
    end
    object SetDefaults: TAction
      Caption = 'SetDefaults'
      OnExecute = SetDefaultsExecute
    end
  end
end
