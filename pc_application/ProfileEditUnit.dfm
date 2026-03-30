object ProfileEditForm: TProfileEditForm
  Left = 37
  Top = 152
  Width = 1006
  Height = 737
  Caption = 'Profile Editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnActivate = FormActivate
  OnHide = FormHide
  OnPaint = RedrawAndRefreshExecute
  OnResize = RedrawAndRefreshExecute
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel2: TBevel
    Left = 0
    Top = 548
    Width = 345
    Height = 69
  end
  object Bevel5: TBevel
    Left = 0
    Top = 448
    Width = 345
    Height = 93
  end
  object Bevel15: TBevel
    Left = 348
    Top = 448
    Width = 301
    Height = 233
  end
  object Bevel14: TBevel
    Left = 652
    Top = 448
    Width = 337
    Height = 33
  end
  object Bevel8: TBevel
    Left = 0
    Top = 0
    Width = 697
    Height = 29
  end
  object Bevel7: TBevel
    Left = 700
    Top = 0
    Width = 161
    Height = 29
  end
  object Label65: TLabel
    Left = 356
    Top = 4
    Width = 36
    Height = 18
    Caption = 'Edit: '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label66: TLabel
    Left = 4
    Top = 4
    Width = 59
    Height = 18
    Caption = 'Display: '
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label67: TLabel
    Left = 708
    Top = 8
    Width = 101
    Height = 13
    Caption = 'Change Profile Group'
  end
  object Label64: TLabel
    Left = 660
    Top = 456
    Width = 33
    Height = 13
    Caption = 'Angle'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label69: TLabel
    Left = 772
    Top = 456
    Width = 33
    Height = 13
    Caption = 'Value'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Image2: TImage
    Left = 356
    Top = 456
    Width = 293
    Height = 225
    Visible = False
  end
  object PaintBox2: TPaintBox
    Left = 352
    Top = 452
    Width = 293
    Height = 225
  end
  object Bevel3: TBevel
    Left = 652
    Top = 484
    Width = 337
    Height = 73
  end
  object Label1: TLabel
    Left = 8
    Top = 456
    Width = 101
    Height = 13
    Caption = 'Uniform Damping:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 480
    Width = 78
    Height = 13
    Caption = 'Source Variable:'
  end
  object Label3: TLabel
    Left = 20
    Top = 512
    Width = 67
    Height = 13
    Caption = 'Default Value:'
  end
  object Label5: TLabel
    Left = 8
    Top = 580
    Width = 329
    Height = 29
    AutoSize = False
    Caption = 
      'Enabling profile summation will set the EVEN numbered profile as' +
      ' the master and sum its output with the one above.'
    WordWrap = True
  end
  object Label4: TLabel
    Left = 672
    Top = 568
    Width = 124
    Height = 13
    Caption = 'Timer Overflow Threshold:'
  end
  object EditThresholdGroupButton: TButton
    Left = 660
    Top = 492
    Width = 105
    Height = 25
    Caption = 'Threshold Groups'
    TabOrder = 0
    OnClick = EditThresholdsExecute
  end
  object EditForceProfileRadio: TRadioButton
    Left = 404
    Top = 4
    Width = 49
    Height = 17
    Caption = 'Force'
    Checked = True
    TabOrder = 1
    TabStop = True
  end
  object EditPDampProfileRadio: TRadioButton
    Left = 460
    Top = 4
    Width = 105
    Height = 17
    Caption = 'Positive Damping'
    TabOrder = 2
  end
  object EditNDampProfileRadio: TRadioButton
    Left = 568
    Top = 4
    Width = 109
    Height = 17
    Caption = 'Negative Damping'
    TabOrder = 3
  end
  object DrawForceCheckBox: TCheckBox
    Left = 76
    Top = 4
    Width = 49
    Height = 17
    Caption = 'Force'
    Checked = True
    State = cbChecked
    TabOrder = 4
    OnClick = RedrawAndRefreshExecute
  end
  object DrawPDampCheckBox: TCheckBox
    Left = 132
    Top = 4
    Width = 105
    Height = 17
    Caption = 'Positive Damping'
    Checked = True
    State = cbChecked
    TabOrder = 5
    OnClick = RedrawAndRefreshExecute
  end
  object DrawNDampCheckBox: TCheckBox
    Left = 240
    Top = 4
    Width = 109
    Height = 17
    Caption = 'Negative Damping'
    Checked = True
    State = cbChecked
    TabOrder = 6
    OnClick = RedrawAndRefreshExecute
  end
  object SelectProfileBox: TComboBox
    Left = 816
    Top = 4
    Width = 41
    Height = 21
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 7
    Text = '0'
    OnChange = SelectProfileBoxChange
    Items.Strings = (
      '0'
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7')
  end
  object AngleText: TStaticText
    Left = 700
    Top = 456
    Width = 52
    Height = 17
    Caption = '00000000'
    TabOrder = 8
  end
  object ValueText: TStaticText
    Left = 812
    Top = 456
    Width = 52
    Height = 17
    Caption = '00000000'
    TabOrder = 9
  end
  object ProfileInteractionEditButton: TButton
    Left = 768
    Top = 492
    Width = 105
    Height = 25
    Caption = 'Profile Interaction'
    TabOrder = 10
    OnClick = EditProfileInteractionsExecute
  end
  object ModulatorsEditButton: TButton
    Left = 768
    Top = 524
    Width = 105
    Height = 25
    Caption = 'Modulators'
    TabOrder = 11
    OnClick = EditModulatorsExecute
  end
  object OKButton: TButton
    Left = 836
    Top = 648
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 12
    OnClick = OKButtonClick
  end
  object CancelButton: TButton
    Left = 920
    Top = 648
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 13
    OnClick = CancelButtonClick
  end
  object EditOutputsButton: TButton
    Left = 660
    Top = 524
    Width = 105
    Height = 25
    Caption = 'External Outputs'
    TabOrder = 14
    OnClick = EditOutputsExecute
  end
  object SummedFlagButton: TButton
    Left = 876
    Top = 492
    Width = 105
    Height = 25
    Caption = 'Group Trigger'
    TabOrder = 15
    OnClick = EditGroupTriggerExecute
  end
  object UniDampSourceBox: TComboBox
    Left = 92
    Top = 476
    Width = 245
    Height = 21
    ItemHeight = 13
    TabOrder = 16
    Text = '0'
    OnChange = SelectProfileBoxChange
  end
  object UniDampDefaultEdit: TEdit
    Left = 92
    Top = 508
    Width = 109
    Height = 21
    TabOrder = 17
    Text = 'UniDampDefaultEdit'
  end
  object MotorEnableButton: TButton
    Left = 876
    Top = 524
    Width = 105
    Height = 25
    Caption = 'Motor and Force'
    TabOrder = 18
    OnClick = EditMotorEnableExecute
  end
  object ProfileSummationBox: TCheckBox
    Left = 8
    Top = 556
    Width = 201
    Height = 17
    Caption = 'Profile Summation Enabled'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 19
    OnClick = RedrawAndRefreshExecute
  end
  object GenerateSurfaceButton: TButton
    Left = 240
    Top = 652
    Width = 105
    Height = 25
    Caption = 'Generate Surface'
    TabOrder = 20
    OnClick = OpenSurfacePlotWindowExecute
  end
  object ShowVThresholdsBox: TCheckBox
    Left = 196
    Top = 628
    Width = 145
    Height = 17
    Caption = 'Show Velocity Thresholds'
    Checked = True
    State = cbChecked
    TabOrder = 21
    OnClick = RedrawVelocityGraphicsExecute
  end
  object Panel1: TPanel
    Left = 0
    Top = 32
    Width = 989
    Height = 413
    Caption = 'Panel1'
    TabOrder = 22
    object Image1: TImage
      Left = 5
      Top = 4
      Width = 980
      Height = 405
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
      OnMouseUp = Image1MouseUp
    end
  end
  object TimerThresholdEdit: TEdit
    Left = 800
    Top = 564
    Width = 109
    Height = 21
    TabOrder = 23
    Text = 'Threshold'
  end
  object DefaultTimerButton: TButton
    Left = 912
    Top = 564
    Width = 75
    Height = 21
    Caption = 'Default'
    TabOrder = 24
    OnClick = DefaultTimerButtonClick
  end
  object ActionList1: TActionList
    Left = 900
    Top = 6
    object RefreshImage: TAction
      Caption = 'RefreshImage'
      OnExecute = RefreshImageExecute
    end
    object SetupComboBoxes: TAction
      Caption = 'SetupComboBoxes'
      OnExecute = SetupComboBoxesExecute
    end
    object DrawProfile: TAction
      Caption = 'DrawProfile'
      OnExecute = DrawProfileExecute
    end
    object CopyToLocalArrays: TAction
      Caption = 'CopyToLocalArrays'
      OnExecute = CopyToLocalArraysExecute
    end
    object UpdateMainProfileData: TAction
      Caption = 'UpdateMainProfileData'
      OnExecute = UpdateMainProfileDataExecute
    end
    object RedrawAndRefresh: TAction
      Caption = 'RedrawAndRefresh'
      OnExecute = RedrawAndRefreshExecute
    end
    object DrawProfileText: TAction
      Caption = 'DrawProfileText'
    end
    object DrawAngleThresholds: TAction
      Caption = 'DrawAngleThresholds'
      OnExecute = DrawAngleThresholdsExecute
    end
    object DrawProfileBackground: TAction
      Caption = 'DrawProfileBackground'
      OnExecute = DrawProfileBackgroundExecute
    end
    object DrawProfileGraphAndText: TAction
      Caption = 'DrawProfileGraphAndText'
      OnExecute = DrawProfileGraphAndTextExecute
    end
    object CheckThresholdsForAngle: TAction
      Caption = 'CheckThresholdsForAngle'
      OnExecute = CheckThresholdsForAngleExecute
    end
    object DrawEQP: TAction
      Caption = 'DrawEQP'
      OnExecute = DrawEQPExecute
    end
    object DrawForceThresholds: TAction
      Caption = 'DrawForceThresholds'
      OnExecute = DrawForceThresholdsExecute
    end
    object DrawVelocityBackground: TAction
      Caption = 'DrawVelocityBackground'
      OnExecute = DrawVelocityBackgroundExecute
    end
    object DrawVelocityThresholds: TAction
      Caption = 'DrawVelocityThresholds'
      OnExecute = DrawVelocityThresholdsExecute
    end
    object TabbedTest: TAction
      Caption = 'TabbedTest'
    end
    object EditThresholds: TAction
      Caption = 'EditThresholds'
      OnExecute = EditThresholdsExecute
    end
    object EditModulators: TAction
      Caption = 'EditModulators'
      OnExecute = EditModulatorsExecute
    end
    object EditProfileInteractions: TAction
      Caption = 'EditProfileInteractions'
      OnExecute = EditProfileInteractionsExecute
    end
    object EditOutputs: TAction
      Caption = 'EditOutputs'
      OnExecute = EditOutputsExecute
    end
    object EditGroupTrigger: TAction
      Caption = 'EditGroupTrigger'
      OnExecute = EditGroupTriggerExecute
    end
    object EditMotorEnable: TAction
      Caption = 'EditMotorEnable'
      OnExecute = EditMotorEnableExecute
    end
    object OpenProfileGenerator: TAction
      Caption = 'OpenProfileGenerator'
      OnExecute = OpenProfileGeneratorExecute
    end
    object FlipProfileVertical: TAction
      Caption = 'FlipProfileVertical'
      OnExecute = FlipProfileVerticalExecute
    end
    object FlipProfileHorizontal: TAction
      Caption = 'FlipProfileHorizontal'
      OnExecute = FlipProfileHorizontalExecute
    end
    object OpenSurfacePlotWindow: TAction
      Caption = 'OpenSurfacePlotWindow'
      OnExecute = OpenSurfacePlotWindowExecute
    end
    object DrawForceMap: TAction
      Caption = 'DrawForceMap'
      OnExecute = DrawForceMapExecute
    end
    object RedrawVelocityGraphics: TAction
      Caption = 'RedrawVelocityGraphics'
      OnExecute = RedrawVelocityGraphicsExecute
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 868
    Top = 4
  end
  object MainMenu1: TMainMenu
    Left = 941
    Top = 2
    object Edit1: TMenuItem
      Caption = 'Group Settings'
      object ThresholdGroups1: TMenuItem
        Caption = 'Threshold Groups'
        object Group11: TMenuItem
          Caption = 'Group1'
          OnClick = Group11Click
        end
        object Group21: TMenuItem
          Caption = 'Group 2'
          OnClick = Group21Click
        end
        object Group31: TMenuItem
          Caption = 'Group 3'
          OnClick = Group31Click
        end
        object Group41: TMenuItem
          Caption = 'Group 4'
          OnClick = Group41Click
        end
      end
      object ProfileGroupInteraction1: TMenuItem
        Caption = 'Profile Group Interaction'
        object ProfileSwitching1: TMenuItem
          Caption = 'Profile Switching'
          OnClick = ProfileSwitching1Click
        end
        object InterprofileCommunications1: TMenuItem
          Caption = 'Inter-profile Communications'
          OnClick = InterprofileCommunications1Click
        end
      end
      object Modulators1: TMenuItem
        Caption = 'Modulators'
        object ScaleAndBias1: TMenuItem
          Caption = 'Scale And Bias'
          OnClick = ScaleAndBias1Click
        end
        object InternalOscillator1: TMenuItem
          Caption = 'Internal Oscillator'
          OnClick = InternalOscillator1Click
        end
      end
      object ExternalOutputs1: TMenuItem
        Caption = 'External Outputs'
        object RS232SerialOutput1: TMenuItem
          Caption = 'RS232 Serial Output'
          OnClick = RS232SerialOutput1Click
        end
        object CANBUSOutput1: TMenuItem
          Caption = 'CAN BUS Output'
          OnClick = CANBUSOutput1Click
        end
        object DiscreteAnalogandDigitalOutputs1: TMenuItem
          Caption = 'Discrete Analog and Digital Outputs'
          OnClick = DiscreteAnalogandDigitalOutputs1Click
        end
      end
      object GroupTrigger1: TMenuItem
        Caption = 'Group Trigger'
      end
      object MotorandForceenable1: TMenuItem
        Caption = 'Motor and Force enable'
      end
    end
    object ProfileGenerators1: TMenuItem
      Caption = 'Profile Settings'
      object GenerateAutoProfile1: TMenuItem
        Caption = 'Generate Auto-Profile'
        OnClick = OpenProfileGeneratorExecute
      end
      object Modify: TMenuItem
        Caption = 'Modify'
        object FlipHorizontal1: TMenuItem
          Caption = 'Flip Horizontal'
          OnClick = FlipProfileHorizontalExecute
        end
        object FlipVertical1: TMenuItem
          Caption = 'Flip Vertical'
          OnClick = FlipProfileVerticalExecute
        end
      end
    end
  end
end
