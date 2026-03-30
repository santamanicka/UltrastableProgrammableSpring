object ProfileGeneratorForm: TProfileGeneratorForm
  Left = 134
  Top = 271
  BorderStyle = bsToolWindow
  Caption = 'Profile Generator'
  ClientHeight = 209
  ClientWidth = 589
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel9: TBevel
    Left = 4
    Top = 172
    Width = 513
    Height = 33
  end
  object Bevel8: TBevel
    Left = 4
    Top = 136
    Width = 513
    Height = 33
  end
  object Bevel5: TBevel
    Left = 120
    Top = 60
    Width = 157
    Height = 45
  end
  object Bevel2: TBevel
    Left = 388
    Top = 4
    Width = 129
    Height = 101
  end
  object Bevel1: TBevel
    Left = 280
    Top = 4
    Width = 101
    Height = 101
  end
  object Bevel4: TBevel
    Left = 120
    Top = 4
    Width = 157
    Height = 45
  end
  object Bevel3: TBevel
    Left = 520
    Top = 4
    Width = 65
    Height = 45
  end
  object Label1: TLabel
    Left = 392
    Top = 48
    Width = 58
    Height = 13
    Caption = 'Vertical Bias'
  end
  object Label2: TLabel
    Left = 528
    Top = 8
    Width = 50
    Height = 13
    Caption = 'Deadband'
  end
  object Bevel6: TBevel
    Left = 4
    Top = 4
    Width = 109
    Height = 101
  end
  object Label3: TLabel
    Left = 12
    Top = 8
    Width = 63
    Height = 16
    Caption = 'Function:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bevel7: TBevel
    Left = 4
    Top = 108
    Width = 513
    Height = 25
  end
  object SineFreqEdit: TLabeledEdit
    Left = 176
    Top = 24
    Width = 45
    Height = 21
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = 'Frequency'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
    Text = '0.1'
    OnExit = SineFreqEditExit
  end
  object SinHeightEdit: TLabeledEdit
    Left = 320
    Top = 44
    Width = 57
    Height = 21
    EditLabel.Width = 31
    EditLabel.Height = 13
    EditLabel.Caption = 'Height'
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 1
    Text = '100'
    OnExit = SinHeightEditExit
  end
  object SinStartEdit: TLabeledEdit
    Left = 176
    Top = 80
    Width = 45
    Height = 21
    EditLabel.Width = 70
    EditLabel.Height = 13
    EditLabel.Caption = 'Horizontal Bias'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
    Text = '1'
    OnExit = SinStartEditExit
  end
  object StartLeft1: TButton
    Left = 152
    Top = 80
    Width = 21
    Height = 21
    Caption = '<'
    TabOrder = 3
    OnClick = StartLeft1Click
  end
  object StartLeft10: TButton
    Left = 124
    Top = 80
    Width = 25
    Height = 21
    Caption = '<<'
    TabOrder = 4
    OnClick = StartLeft10Click
  end
  object StartRight10: TButton
    Left = 252
    Top = 80
    Width = 21
    Height = 21
    Caption = '>>'
    TabOrder = 5
    OnClick = StartRight10Click
  end
  object StartRight1: TButton
    Left = 224
    Top = 80
    Width = 25
    Height = 21
    Caption = '>'
    TabOrder = 6
    OnClick = StartRight1Click
  end
  object CancelButton: TButton
    Left = 524
    Top = 180
    Width = 59
    Height = 25
    Caption = 'Cancel'
    TabOrder = 7
    OnClick = CancelAndCloseExecute
  end
  object VBiasEdit: TEdit
    Left = 456
    Top = 44
    Width = 57
    Height = 21
    TabOrder = 8
    Text = '0'
    OnExit = VBiasEditExit
  end
  object VBisUp: TButton
    Left = 456
    Top = 24
    Width = 57
    Height = 16
    Caption = '+1'
    TabOrder = 9
    OnClick = VBisUpClick
  end
  object VBiasDown: TButton
    Left = 456
    Top = 68
    Width = 57
    Height = 16
    Caption = '-1'
    TabOrder = 10
    OnClick = VBiasDownClick
  end
  object SinButton: TRadioButton
    Left = 12
    Top = 32
    Width = 57
    Height = 17
    Caption = 'Sin'
    Checked = True
    TabOrder = 11
    TabStop = True
    OnClick = SinClickExecute
  end
  object TanhButton: TRadioButton
    Left = 12
    Top = 56
    Width = 69
    Height = 17
    Caption = 'Tanh'
    TabOrder = 12
    OnClick = TanhClickExecute
  end
  object FlipHorizontalBox: TCheckBox
    Left = 120
    Top = 112
    Width = 97
    Height = 17
    Caption = 'Flip Horizontal'
    TabOrder = 13
    OnClick = RegenerateFunctionExecute
  end
  object HorizontalMirrorMode: TCheckBox
    Left = 224
    Top = 112
    Width = 137
    Height = 17
    Caption = 'Horizontal Mirroring'
    TabOrder = 14
    OnClick = RegenerateFunctionExecute
  end
  object ExponentialButton: TRadioButton
    Left = 12
    Top = 80
    Width = 89
    Height = 17
    Caption = 'Exponential'
    TabOrder = 15
    OnClick = RegenerateFunctionExecute
  end
  object DeadBandEdit: TEdit
    Left = 532
    Top = 24
    Width = 41
    Height = 21
    TabOrder = 16
    Text = 'DeadBandEdit'
    OnExit = RegenerateFunctionExecute
  end
  object VBiasUp16Button: TButton
    Left = 456
    Top = 8
    Width = 57
    Height = 16
    Caption = '+16'
    TabOrder = 17
    OnClick = VBiasUp16ButtonClick
  end
  object VBiasDown16Button: TButton
    Left = 456
    Top = 84
    Width = 57
    Height = 16
    Caption = '-16'
    TabOrder = 18
    OnClick = VBiasDown16ButtonClick
  end
  object FreqUpButton: TButton
    Left = 224
    Top = 24
    Width = 25
    Height = 21
    Caption = '>'
    TabOrder = 19
    OnClick = FreqUpButtonClick
  end
  object FreqDownButton: TButton
    Left = 152
    Top = 24
    Width = 21
    Height = 21
    Caption = '<'
    TabOrder = 20
    OnClick = FreqDownButtonClick
  end
  object FreqUp1Button: TButton
    Left = 252
    Top = 24
    Width = 21
    Height = 21
    Caption = '>>'
    TabOrder = 21
    OnClick = FreqUp1ButtonClick
  end
  object FreqDown1Button: TButton
    Left = 124
    Top = 24
    Width = 25
    Height = 21
    Caption = '<<'
    TabOrder = 22
    OnClick = FreqDown1ButtonClick
  end
  object HeightUp16Button: TButton
    Left = 320
    Top = 8
    Width = 57
    Height = 16
    Caption = '+16'
    TabOrder = 23
    OnClick = HeightUp16ButtonClick
  end
  object HeightUp1Button: TButton
    Left = 320
    Top = 24
    Width = 57
    Height = 16
    Caption = '+1'
    TabOrder = 24
    OnClick = HeightUp1ButtonClick
  end
  object HeightDown1Button: TButton
    Left = 320
    Top = 68
    Width = 57
    Height = 16
    Caption = '-1'
    TabOrder = 25
    OnClick = HeightDown1ButtonClick
  end
  object HeightDown16Button: TButton
    Left = 320
    Top = 84
    Width = 57
    Height = 16
    Caption = '-16'
    TabOrder = 26
    OnClick = HeightDown16ButtonClick
  end
  object OKButton: TButton
    Left = 524
    Top = 152
    Width = 59
    Height = 25
    Caption = 'OK'
    TabOrder = 27
    OnClick = SaveAndCloseExecute
  end
  object ApplyToNDampBox: TCheckBox
    Left = 12
    Top = 144
    Width = 153
    Height = 17
    Caption = 'Apply To Negative Damping'
    TabOrder = 28
    OnClick = RegenerateFunctionExecute
  end
  object ApplyToPDampBox: TCheckBox
    Left = 12
    Top = 180
    Width = 157
    Height = 17
    Caption = 'Apply To Positive Damping'
    TabOrder = 29
    OnClick = RegenerateFunctionExecute
  end
  object ApplyToForceBox: TCheckBox
    Left = 12
    Top = 112
    Width = 101
    Height = 17
    Caption = 'Apply To Force'
    Checked = True
    State = cbChecked
    TabOrder = 30
    OnClick = RegenerateFunctionExecute
  end
  object ActionList1: TActionList
    Left = 428
    Top = 136
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object UpdateMainImage: TAction
      Caption = 'UpdateMainImage'
      OnExecute = UpdateMainImageExecute
    end
    object RegenerateFunction: TAction
      Caption = 'RegenerateFunction'
      OnExecute = RegenerateFunctionExecute
    end
    object CancelAndClose: TAction
      Caption = 'CancelAndClose'
      OnExecute = CancelAndCloseExecute
    end
    object GenerateSin: TAction
      Caption = 'GenerateSin'
      OnExecute = GenerateSinExecute
    end
    object GenerateTanh: TAction
      Caption = 'GenerateTanh'
      OnExecute = GenerateTanhExecute
    end
    object GenerateExponential: TAction
      Caption = 'GenerateExponential'
      OnExecute = GenerateExponentialExecute
    end
    object TanhClick: TAction
      Caption = 'TanhClick'
      OnExecute = TanhClickExecute
    end
    object SinClick: TAction
      Caption = 'SinClick'
      OnExecute = SinClickExecute
    end
    object SaveAndClose: TAction
      Caption = 'SaveAndClose'
      OnExecute = SaveAndCloseExecute
    end
  end
end
