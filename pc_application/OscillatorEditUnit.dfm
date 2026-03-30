object OscillatorEditForm: TOscillatorEditForm
  Left = 168
  Top = 137
  Width = 274
  Height = 221
  Caption = 'Profile Oscillator Editor'
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
    Left = 6
    Top = 4
    Width = 186
    Height = 19
    Caption = 'Oscillator for Profile No: '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 12
    Top = 36
    Width = 45
    Height = 13
    Caption = 'Step Size'
  end
  object Label3: TLabel
    Left = 12
    Top = 64
    Width = 44
    Height = 13
    Caption = 'Prescaler'
  end
  object Label4: TLabel
    Left = 12
    Top = 92
    Width = 74
    Height = 13
    Caption = 'Maximum Value'
  end
  object Label5: TLabel
    Left = 12
    Top = 120
    Width = 71
    Height = 13
    Caption = 'Minimum Value'
  end
  object Button2: TButton
    Left = 100
    Top = 156
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
    OnClick = Button2Click
  end
  object Button1: TButton
    Left = 184
    Top = 156
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button3: TButton
    Left = 6
    Top = 156
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 2
    OnClick = Button3Click
  end
  object StepEdit: TEdit
    Left = 96
    Top = 32
    Width = 161
    Height = 21
    TabOrder = 3
    Text = 'StepEdit'
  end
  object PrescaleEdit: TEdit
    Left = 96
    Top = 60
    Width = 161
    Height = 21
    TabOrder = 4
    Text = 'Edit1'
  end
  object MaxEdit: TEdit
    Left = 96
    Top = 88
    Width = 161
    Height = 21
    TabOrder = 5
    Text = 'Edit1'
  end
  object MinEdit: TEdit
    Left = 96
    Top = 116
    Width = 161
    Height = 21
    TabOrder = 6
    Text = 'Edit1'
  end
  object ActionList1: TActionList
    Left = 8
    Top = 124
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
    end
  end
end
