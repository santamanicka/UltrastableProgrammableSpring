object CommandForm: TCommandForm
  Left = 38
  Top = 169
  BorderStyle = bsToolWindow
  Caption = 'Actuator Control'
  ClientHeight = 277
  ClientWidth = 969
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
    Left = 564
    Top = 244
    Width = 297
    Height = 29
  end
  object Bevel8: TBevel
    Left = 564
    Top = 212
    Width = 297
    Height = 29
  end
  object Bevel6: TBevel
    Left = 4
    Top = 212
    Width = 557
    Height = 61
  end
  object Bevel1: TBevel
    Left = 4
    Top = 4
    Width = 857
    Height = 49
  end
  object ValueText1: TLabel
    Left = 412
    Top = 8
    Width = 54
    Height = 13
    Caption = 'ValueText1'
  end
  object Bevel2: TBevel
    Left = 4
    Top = 56
    Width = 857
    Height = 49
  end
  object ValueText2: TLabel
    Left = 412
    Top = 60
    Width = 54
    Height = 13
    Caption = 'ValueText1'
  end
  object Bevel3: TBevel
    Left = 4
    Top = 108
    Width = 857
    Height = 49
  end
  object ValueText3: TLabel
    Left = 412
    Top = 112
    Width = 54
    Height = 13
    Caption = 'ValueText1'
  end
  object Bevel4: TBevel
    Left = 4
    Top = 160
    Width = 857
    Height = 49
  end
  object ValueText4: TLabel
    Left = 412
    Top = 164
    Width = 54
    Height = 13
    Caption = 'ValueText1'
  end
  object Bevel5: TBevel
    Left = 864
    Top = 108
    Width = 101
    Height = 101
  end
  object Bevel7: TBevel
    Left = 864
    Top = 4
    Width = 101
    Height = 101
  end
  object Label1: TLabel
    Left = 776
    Top = 10
    Width = 35
    Height = 13
    Caption = 'Scaling'
  end
  object Label2: TLabel
    Left = 776
    Top = 62
    Width = 35
    Height = 13
    Caption = 'Scaling'
  end
  object Label3: TLabel
    Left = 776
    Top = 114
    Width = 35
    Height = 13
    Caption = 'Scaling'
  end
  object Label4: TLabel
    Left = 776
    Top = 166
    Width = 35
    Height = 13
    Caption = 'Scaling'
  end
  object Label5: TLabel
    Left = 592
    Top = 252
    Width = 100
    Height = 13
    Caption = #39'A'#39' or '#39'B'#39' Packet type:'
  end
  object VarBar1: TTrackBar
    Left = 8
    Top = 28
    Width = 850
    Height = 24
    Max = 256
    Min = -256
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    ThumbLength = 16
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = ChangeVar1Execute
  end
  object ZeroButton1: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 17
    Caption = 'Zero'
    TabOrder = 1
    OnClick = Zero1Execute
  end
  object VarBar2: TTrackBar
    Left = 8
    Top = 80
    Width = 850
    Height = 24
    Max = 256
    Min = -256
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 2
    ThumbLength = 16
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = ChangeVar2Execute
  end
  object ZeroButton2: TButton
    Left = 8
    Top = 60
    Width = 75
    Height = 17
    Caption = 'Zero'
    TabOrder = 3
    OnClick = Zero2Execute
  end
  object VarBar3: TTrackBar
    Left = 8
    Top = 132
    Width = 850
    Height = 24
    Max = 256
    Min = -256
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 4
    ThumbLength = 16
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = ChangeVar3Execute
  end
  object ZeroButton3: TButton
    Left = 8
    Top = 112
    Width = 75
    Height = 17
    Caption = 'Zero'
    TabOrder = 5
    OnClick = Zero3Execute
  end
  object VarBar4: TTrackBar
    Left = 8
    Top = 184
    Width = 850
    Height = 24
    Max = 256
    Min = -256
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 6
    ThumbLength = 16
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = ChangeVar4Execute
  end
  object ZeroButton4: TButton
    Left = 8
    Top = 164
    Width = 75
    Height = 17
    Caption = 'Zero'
    TabOrder = 7
    OnClick = Zero4Execute
  end
  object FlagBox1: TCheckBox
    Left = 872
    Top = 8
    Width = 53
    Height = 17
    Caption = 'Flag 1'
    TabOrder = 8
    OnClick = ChangeFlag1Execute
  end
  object FlagBox2: TCheckBox
    Left = 872
    Top = 32
    Width = 53
    Height = 17
    Caption = 'Flag 2'
    TabOrder = 9
    OnClick = ChangeFlag2Execute
  end
  object FlagBox3: TCheckBox
    Left = 872
    Top = 56
    Width = 53
    Height = 17
    Caption = 'Flag 3'
    TabOrder = 10
    OnClick = ChangeFlag3Execute
  end
  object FlagBox4: TCheckBox
    Left = 872
    Top = 80
    Width = 53
    Height = 17
    Caption = 'Flag 4'
    TabOrder = 11
    OnClick = ChangeFlag4Execute
  end
  object SendButton: TButton
    Left = 80
    Top = 218
    Width = 73
    Height = 21
    Caption = 'Send'
    TabOrder = 12
    OnClick = TransmitCommandsExecute
  end
  object AutoTXButton: TRadioButton
    Left = 12
    Top = 248
    Width = 133
    Height = 17
    Caption = 'Auto Send (per second)'
    TabOrder = 13
  end
  object OnChangeTXButton: TRadioButton
    Left = 160
    Top = 220
    Width = 105
    Height = 17
    Caption = 'Send on Change'
    TabOrder = 14
  end
  object ManualTXButton: TRadioButton
    Left = 12
    Top = 220
    Width = 61
    Height = 17
    Caption = 'Manual'
    Checked = True
    TabOrder = 15
    TabStop = True
  end
  object TxRateEdit: TEdit
    Left = 148
    Top = 246
    Width = 41
    Height = 21
    TabOrder = 16
    Text = '10'
  end
  object RequestReplyBox: TCheckBox
    Left = 456
    Top = 252
    Width = 97
    Height = 17
    Caption = 'Request Reply'
    TabOrder = 17
  end
  object StartStopTxButton: TButton
    Left = 192
    Top = 246
    Width = 73
    Height = 21
    Caption = 'Start'
    TabOrder = 18
    OnClick = StartStopAutoTxExecute
  end
  object ScaleEdit1: TEdit
    Left = 816
    Top = 7
    Width = 41
    Height = 21
    TabOrder = 19
    Text = '1.0'
  end
  object ScaleEdit2: TEdit
    Left = 816
    Top = 59
    Width = 41
    Height = 21
    TabOrder = 20
    Text = '1.0'
  end
  object ScaleEdit3: TEdit
    Left = 816
    Top = 111
    Width = 41
    Height = 21
    TabOrder = 21
    Text = '1.0'
  end
  object ScaleEdit4: TEdit
    Left = 816
    Top = 163
    Width = 41
    Height = 21
    TabOrder = 22
    Text = '1.0'
  end
  object ResetActuatorButton: TButton
    Left = 872
    Top = 112
    Width = 85
    Height = 21
    Caption = 'Reset Actuator'
    TabOrder = 23
    OnClick = ResetActuatorButtonClick
  end
  object HaltActuatorButton: TButton
    Left = 872
    Top = 148
    Width = 85
    Height = 21
    Caption = 'Halt Actuator'
    TabOrder = 24
    OnClick = HaltActuatorButtonClick
  end
  object StartActuatorButton: TButton
    Left = 872
    Top = 184
    Width = 85
    Height = 21
    Caption = 'Start Actuator'
    TabOrder = 25
    OnClick = StartActuatorButtonClick
  end
  object PrintProfileButton: TButton
    Left = 752
    Top = 216
    Width = 105
    Height = 21
    Caption = 'Print This Profile'
    TabOrder = 26
    OnClick = PrintProfileButtonClick
  end
  object SwitchProfileButton: TButton
    Left = 568
    Top = 216
    Width = 113
    Height = 21
    Caption = 'Switch To profile:'
    TabOrder = 27
    OnClick = SwitchProfileButtonClick
  end
  object SwitchProfileBox: TComboBox
    Left = 688
    Top = 216
    Width = 57
    Height = 21
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 28
    Text = '0'
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
  object StaticText1: TStaticText
    Left = 868
    Top = 216
    Width = 93
    Height = 17
    AutoSize = False
    Caption = '0'
    TabOrder = 29
  end
  object PacketTypeBox: TComboBox
    Left = 712
    Top = 248
    Width = 145
    Height = 21
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 30
    Text = 'Type '#39'A'#39
    Items.Strings = (
      'Type '#39'A'#39
      'Type '#39'B'#39)
  end
  object ActionList1: TActionList
    Left = 928
    Top = 36
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object Zero1: TAction
      Caption = 'Zero1'
      OnExecute = Zero1Execute
    end
    object Zero2: TAction
      Caption = 'Zero2'
      OnExecute = Zero2Execute
    end
    object Zero3: TAction
      Caption = 'Zero3'
      OnExecute = Zero3Execute
    end
    object Zero4: TAction
      Caption = 'Zero4'
      OnExecute = Zero4Execute
    end
    object ChangeVar1: TAction
      Caption = 'ChangeVar1'
      OnExecute = ChangeVar1Execute
    end
    object ChangeVar2: TAction
      Caption = 'ChangeVar2'
      OnExecute = ChangeVar2Execute
    end
    object ChangeVar3: TAction
      Caption = 'ChangeVar3'
      OnExecute = ChangeVar3Execute
    end
    object ChangeVar4: TAction
      Caption = 'ChangeVar4'
      OnExecute = ChangeVar4Execute
    end
    object ChangeFlag1: TAction
      Caption = 'ChangeFlag1'
      OnExecute = ChangeFlag1Execute
    end
    object ChangeFlag2: TAction
      Caption = 'ChangeFlag2'
      OnExecute = ChangeFlag2Execute
    end
    object ChangeFlag3: TAction
      Caption = 'ChangeFlag3'
      OnExecute = ChangeFlag3Execute
    end
    object ChangeFlag4: TAction
      Caption = 'ChangeFlag4'
      OnExecute = ChangeFlag4Execute
    end
    object TransmitCommands: TAction
      Caption = 'TransmitCommands'
      OnExecute = TransmitCommandsExecute
    end
    object StartStopAutoTx: TAction
      Caption = 'StartStopAutoTx'
      OnExecute = StartStopAutoTxExecute
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 928
    Top = 8
  end
end
