object ModulatorsEditForm: TModulatorsEditForm
  Left = 323
  Top = 162
  Width = 601
  Height = 421
  Caption = 'Modulating Variable Editor for Profile '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 512
    Top = 356
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
    OnClick = CancelAndCloseExecute
  end
  object Button2: TButton
    Left = 428
    Top = 356
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
    OnClick = SaveAndCloseExecute
  end
  object SetDefaultsButton: TButton
    Left = 4
    Top = 356
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 2
    OnClick = SetDefaultsExecute
  end
  object PageControl1: TPageControl
    Left = 4
    Top = 4
    Width = 585
    Height = 345
    ActivePage = ParametersTab
    TabIndex = 3
    TabOrder = 3
    object ScaleAndBiasTab: TTabSheet
      Caption = 'Scale and Bias'
      object Bevel6: TBevel
        Left = 4
        Top = 272
        Width = 568
        Height = 41
      end
      object Bevel5: TBevel
        Left = 4
        Top = 124
        Width = 568
        Height = 41
      end
      object Bevel4: TBevel
        Left = 4
        Top = 228
        Width = 568
        Height = 41
      end
      object Bevel3: TBevel
        Left = 4
        Top = 80
        Width = 568
        Height = 41
      end
      object Bevel2: TBevel
        Left = 4
        Top = 184
        Width = 568
        Height = 41
      end
      object Bevel1: TBevel
        Left = 4
        Top = 36
        Width = 568
        Height = 41
      end
      object Label2: TLabel
        Left = 12
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
        Left = 128
        Top = 48
        Width = 75
        Height = 13
        Caption = 'Source Variable'
      end
      object ScaleAndBiasTitle: TLabel
        Left = 8
        Top = 8
        Width = 247
        Height = 19
        Caption = 'Scale and Bias for Profile Group '
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label4: TLabel
        Left = 412
        Top = 48
        Width = 64
        Height = 13
        Caption = 'Default Value'
      end
      object Label5: TLabel
        Left = 12
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
        Left = 128
        Top = 196
        Width = 75
        Height = 13
        Caption = 'Source Variable'
      end
      object Label7: TLabel
        Left = 412
        Top = 196
        Width = 64
        Height = 13
        Caption = 'Default Value'
      end
      object Label8: TLabel
        Left = 12
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
        Left = 128
        Top = 92
        Width = 75
        Height = 13
        Caption = 'Source Variable'
      end
      object Label10: TLabel
        Left = 412
        Top = 92
        Width = 64
        Height = 13
        Caption = 'Default Value'
      end
      object Label11: TLabel
        Left = 12
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
        Left = 128
        Top = 240
        Width = 75
        Height = 13
        Caption = 'Source Variable'
      end
      object Label13: TLabel
        Left = 412
        Top = 240
        Width = 64
        Height = 13
        Caption = 'Default Value'
      end
      object Label14: TLabel
        Left = 12
        Top = 136
        Width = 192
        Height = 16
        Caption = 'Horizontal Scaling Origin (Angle)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 12
        Top = 284
        Width = 177
        Height = 16
        Caption = 'Vertical Scaling Origin (Angle)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object HScaleSourceBox: TComboBox
        Left = 216
        Top = 44
        Width = 185
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 0
        Text = 'HScaleSourceBox'
      end
      object HScaleEdit: TEdit
        Left = 480
        Top = 44
        Width = 73
        Height = 21
        TabOrder = 1
        Text = 'HScaleEdit'
      end
      object VScaleSourceBox: TComboBox
        Left = 216
        Top = 192
        Width = 185
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 2
        Text = 'ComboBox1'
      end
      object VScaleEdit: TEdit
        Left = 480
        Top = 192
        Width = 73
        Height = 21
        TabOrder = 3
        Text = 'Edit1'
      end
      object HBiasSourceBox: TComboBox
        Left = 216
        Top = 88
        Width = 185
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 4
        Text = 'ComboBox1'
      end
      object HBiasEdit: TEdit
        Left = 480
        Top = 88
        Width = 73
        Height = 21
        TabOrder = 5
        Text = 'Edit1'
      end
      object VBiasSourceBox: TComboBox
        Left = 216
        Top = 236
        Width = 185
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 6
        Text = 'ComboBox1'
      end
      object VBiasEdit: TEdit
        Left = 480
        Top = 236
        Width = 73
        Height = 21
        TabOrder = 7
        Text = 'Edit1'
      end
      object EQEdit: TEdit
        Left = 216
        Top = 132
        Width = 73
        Height = 21
        TabOrder = 8
        Text = 'Edit1'
      end
      object VerticalReferenceEdit: TEdit
        Left = 216
        Top = 280
        Width = 73
        Height = 21
        TabOrder = 9
        Text = 'VerticalReferenceEdit'
      end
    end
    object InternalOscillatorTab: TTabSheet
      Caption = 'Internal Oscillator'
      ImageIndex = 1
      object OscillatorTitle: TLabel
        Left = 6
        Top = 4
        Width = 206
        Height = 19
        Caption = 'Oscillator for Profile Group '
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label15: TLabel
        Left = 12
        Top = 36
        Width = 45
        Height = 13
        Caption = 'Step Size'
      end
      object Label16: TLabel
        Left = 12
        Top = 64
        Width = 44
        Height = 13
        Caption = 'Prescaler'
      end
      object Label17: TLabel
        Left = 12
        Top = 92
        Width = 74
        Height = 13
        Caption = 'Maximum Value'
      end
      object Label18: TLabel
        Left = 12
        Top = 120
        Width = 71
        Height = 13
        Caption = 'Minimum Value'
      end
      object StepEdit: TEdit
        Left = 96
        Top = 32
        Width = 161
        Height = 21
        TabOrder = 0
        Text = 'StepEdit'
      end
      object PrescaleEdit: TEdit
        Left = 96
        Top = 60
        Width = 161
        Height = 21
        TabOrder = 1
        Text = 'Edit1'
      end
      object MaxEdit: TEdit
        Left = 96
        Top = 88
        Width = 161
        Height = 21
        TabOrder = 2
        Text = 'Edit1'
      end
      object MinEdit: TEdit
        Left = 96
        Top = 116
        Width = 161
        Height = 21
        TabOrder = 3
        Text = 'Edit1'
      end
    end
    object RandomiserTab: TTabSheet
      Caption = 'Randomisers'
      ImageIndex = 2
      object Bevel8: TBevel
        Left = 4
        Top = 136
        Width = 525
        Height = 149
      end
      object Bevel7: TBevel
        Left = 12
        Top = 36
        Width = 525
        Height = 93
      end
      object RandomisersTitle: TLabel
        Left = 8
        Top = 8
        Width = 236
        Height = 19
        Caption = 'Randomisers for Profile Group '
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label20: TLabel
        Left = 12
        Top = 48
        Width = 117
        Height = 16
        Caption = 'Randomise Force if'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label22: TLabel
        Left = 12
        Top = 152
        Width = 76
        Height = 13
        Caption = 'Mutation Range'
      end
      object Label23: TLabel
        Left = 12
        Top = 180
        Width = 86
        Height = 13
        Caption = 'Cap values above'
      end
      object Label24: TLabel
        Left = 184
        Top = 180
        Width = 49
        Height = 13
        Caption = 'and below'
      end
      object Label25: TLabel
        Left = 12
        Top = 208
        Width = 48
        Height = 13
        Caption = 'Bias using'
      end
      object Label26: TLabel
        Left = 284
        Top = 208
        Width = 34
        Height = 13
        Caption = 'Default'
      end
      object Label19: TLabel
        Left = 12
        Top = 76
        Width = 146
        Height = 16
        Caption = 'Randomise PDamping if'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label21: TLabel
        Left = 12
        Top = 104
        Width = 147
        Height = 16
        Caption = 'Randomise NDamping if'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label27: TLabel
        Left = 12
        Top = 236
        Width = 42
        Height = 13
        Caption = 'Scale By'
      end
      object Label28: TLabel
        Left = 184
        Top = 152
        Width = 134
        Height = 13
        Caption = '(percentage of actual range)'
      end
      object MutationBiasSourceBox: TComboBox
        Left = 64
        Top = 204
        Width = 213
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 0
        Text = 'MutationBiasBox'
      end
      object RangeEdit: TEdit
        Left = 104
        Top = 148
        Width = 73
        Height = 21
        TabOrder = 1
        Text = '50'
      end
      object ForceRandomiserTriggerList: TComboBox
        Left = 168
        Top = 44
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 2
      end
      object MaxValEdit: TEdit
        Left = 104
        Top = 176
        Width = 73
        Height = 21
        TabOrder = 3
        Text = 'MaxValue'
      end
      object MinValEdit: TEdit
        Left = 244
        Top = 176
        Width = 73
        Height = 21
        TabOrder = 4
        Text = 'MinValue'
      end
      object DefaultMutateBiasBox: TEdit
        Left = 324
        Top = 204
        Width = 73
        Height = 21
        TabOrder = 5
        Text = 'MaxValue'
      end
      object PDampRandomiserTriggerList: TComboBox
        Left = 168
        Top = 72
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 6
      end
      object NDampRandomiserTriggerList: TComboBox
        Left = 168
        Top = 100
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 7
      end
      object BiasScaleEdit: TEdit
        Left = 64
        Top = 232
        Width = 73
        Height = 21
        TabOrder = 8
        Text = 'Scale'
      end
    end
    object ParametersTab: TTabSheet
      Caption = 'Parameters'
      ImageIndex = 3
      object PolygonSides: TLabel
        Left = 96
        Top = 42
        Width = 77
        Height = 13
        Caption = 'Angle of rotation'
      end
      object TVZRadius: TLabel
        Left = 82
        Top = 76
        Width = 90
        Height = 13
        Caption = 'TVZ Radius Factor'
      end
      object Label29: TLabel
        Left = 61
        Top = 107
        Width = 137
        Height = 13
        Caption = 'TVZ Radius drop/Rise factor'
      end
      object Label30: TLabel
        Left = 93
        Top = 139
        Width = 86
        Height = 13
        Caption = 'Viability Zone Size'
      end
      object Label31: TLabel
        Left = 74
        Top = 171
        Width = 125
        Height = 13
        Caption = 'Pre-analysis actuation time'
      end
      object Label32: TLabel
        Left = 90
        Top = 203
        Width = 106
        Height = 13
        Caption = 'Mutation Range factor'
      end
      object Label33: TLabel
        Left = 88
        Top = 235
        Width = 115
        Height = 13
        Caption = 'Damping mutation factor'
      end
      object Label34: TLabel
        Left = 113
        Top = 267
        Width = 79
        Height = 13
        Caption = 'Analysis samples'
      end
      object PolygonSidesEdit: TEdit
        Left = 232
        Top = 40
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '20'
      end
      object TVZRadiusEdit: TEdit
        Left = 232
        Top = 72
        Width = 121
        Height = 21
        TabOrder = 1
        Text = '2'
      end
      object ViabilityAngle: TEdit
        Left = 232
        Top = 136
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '30'
      end
      object TVZDropByEdit: TEdit
        Left = 232
        Top = 104
        Width = 121
        Height = 21
        TabOrder = 3
        Text = '6'
      end
      object EvalTimeEdit: TEdit
        Left = 232
        Top = 168
        Width = 121
        Height = 21
        TabOrder = 4
        Text = '30'
      end
      object ViabilityVelocity: TEdit
        Left = 303
        Top = 136
        Width = 49
        Height = 21
        TabOrder = 5
        Text = '30'
      end
      object MutationRangeEdit: TEdit
        Left = 232
        Top = 200
        Width = 121
        Height = 21
        TabOrder = 6
        Text = '80'
      end
      object dampingMutationEdit: TEdit
        Left = 232
        Top = 232
        Width = 121
        Height = 21
        TabOrder = 7
        Text = '20'
      end
      object AnalysisSamplesEdit: TEdit
        Left = 232
        Top = 264
        Width = 121
        Height = 21
        TabOrder = 8
        Text = '10'
      end
    end
  end
  object ActionList1: TActionList
    Left = 320
    Top = 356
    object SetupScaleAndBiasTab: TAction
      Caption = 'SetupScaleAndBiasTab'
      OnExecute = SetupScaleAndBiasTabExecute
    end
    object SaveAndClose: TAction
      Caption = 'SaveAndClose'
      OnExecute = SaveAndCloseExecute
    end
    object CancelAndClose: TAction
      Caption = 'CancelAndClose'
      OnExecute = CancelAndCloseExecute
    end
    object SetupOscillatorTab: TAction
      Caption = 'SetupOscillatorTab'
      OnExecute = SetupOscillatorTabExecute
    end
    object SaveScaleAndBiasTab: TAction
      Caption = 'SaveScaleAndBiasTab'
      OnExecute = SaveScaleAndBiasTabExecute
    end
    object SaveOscillatorTab: TAction
      Caption = 'SaveOscillatorTab'
      OnExecute = SaveOscillatorTabExecute
    end
    object SetDefaults: TAction
      Caption = 'SetDefaults'
      OnExecute = SetDefaultsExecute
    end
    object SetDefaultScaleAndBiasTab: TAction
      Caption = 'SetDefaultScaleAndBiasTab'
      OnExecute = SetDefaultScaleAndBiasTabExecute
    end
    object SetDefaultOscillatorTab: TAction
      Caption = 'SetDefaultOscillatorTab'
      OnExecute = SetDefaultOscillatorTabExecute
    end
    object SetupRandomisersTab: TAction
      Caption = 'SetupRandomisersTab'
      OnExecute = SetupRandomisersTabExecute
    end
    object SetDefaultRandomisersTab: TAction
      Caption = 'SetDefaultRandomisersTab'
      OnExecute = SetDefaultRandomisersTabExecute
    end
    object SaveRandomisersTab: TAction
      Caption = 'SaveRandomisersTab'
      OnExecute = SaveRandomisersTabExecute
    end
    object SaveParametersTab: TAction
      Caption = 'SaveParametersTab'
      OnExecute = SaveParametersTabExecute
    end
    object SetupParametersTab: TAction
      Caption = 'SetupParametersTab'
      OnExecute = SetupParametersTabExecute
    end
    object SetDefaultParametersTab: TAction
      Caption = 'SetDefaultParametersTab'
      OnExecute = SetDefaultParametersTabExecute
    end
  end
end
