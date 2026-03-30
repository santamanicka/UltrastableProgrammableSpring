object InputOutputForm: TInputOutputForm
  Left = 300
  Top = 151
  Width = 634
  Height = 531
  Caption = 'External Output Editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 625
    Height = 465
    ActivePage = RS232Tab
    TabIndex = 0
    TabOrder = 0
    object RS232Tab: TTabSheet
      Caption = 'RS232'
      object Bevel7: TBevel
        Left = 4
        Top = 32
        Width = 609
        Height = 197
      end
      object Bevel2: TBevel
        Left = 4
        Top = 236
        Width = 609
        Height = 197
      end
      object SerialTabTitle: TLabel
        Left = 8
        Top = 8
        Width = 162
        Height = 19
        Caption = 'RS232 Serial Outputs'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label2: TLabel
        Left = 12
        Top = 60
        Width = 67
        Height = 13
        Caption = 'Variable Out 1'
      end
      object Label3: TLabel
        Left = 12
        Top = 88
        Width = 67
        Height = 13
        Caption = 'Variable Out 2'
      end
      object Label4: TLabel
        Left = 12
        Top = 116
        Width = 67
        Height = 13
        Caption = 'Variable Out 3'
      end
      object Label5: TLabel
        Left = 12
        Top = 144
        Width = 67
        Height = 13
        Caption = 'Variable Out 4'
      end
      object Label10: TLabel
        Left = 12
        Top = 36
        Width = 61
        Height = 16
        Caption = 'Group A:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label11: TLabel
        Left = 12
        Top = 240
        Width = 61
        Height = 16
        Caption = 'Group B:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label12: TLabel
        Left = 316
        Top = 60
        Width = 62
        Height = 13
        Caption = 'Trigger Out 1'
      end
      object Label13: TLabel
        Left = 316
        Top = 88
        Width = 62
        Height = 13
        Caption = 'Trigger Out 2'
      end
      object Label14: TLabel
        Left = 316
        Top = 116
        Width = 62
        Height = 13
        Caption = 'Trigger Out 3'
      end
      object Label15: TLabel
        Left = 316
        Top = 144
        Width = 62
        Height = 13
        Caption = 'Trigger Out 4'
      end
      object Label16: TLabel
        Left = 316
        Top = 348
        Width = 62
        Height = 13
        Caption = 'Trigger Out 4'
      end
      object Label17: TLabel
        Left = 316
        Top = 320
        Width = 62
        Height = 13
        Caption = 'Trigger Out 3'
      end
      object Label18: TLabel
        Left = 316
        Top = 292
        Width = 62
        Height = 13
        Caption = 'Trigger Out 2'
      end
      object Label19: TLabel
        Left = 316
        Top = 264
        Width = 62
        Height = 13
        Caption = 'Trigger Out 1'
      end
      object Label39: TLabel
        Left = 12
        Top = 380
        Width = 70
        Height = 13
        Caption = 'Auto TxTrigger'
      end
      object Label40: TLabel
        Left = 12
        Top = 176
        Width = 70
        Height = 13
        Caption = 'Auto TxTrigger'
      end
      object Label1: TLabel
        Left = 12
        Top = 264
        Width = 67
        Height = 13
        Caption = 'Variable Out 1'
      end
      object Label20: TLabel
        Left = 12
        Top = 292
        Width = 67
        Height = 13
        Caption = 'Variable Out 2'
      end
      object Label31: TLabel
        Left = 12
        Top = 320
        Width = 67
        Height = 13
        Caption = 'Variable Out 3'
      end
      object Label34: TLabel
        Left = 12
        Top = 348
        Width = 67
        Height = 13
        Caption = 'Variable Out 4'
      end
      object Label8: TLabel
        Left = 20
        Top = 408
        Width = 60
        Height = 13
        Caption = 'Target Node'
      end
      object Label9: TLabel
        Left = 20
        Top = 204
        Width = 60
        Height = 13
        Caption = 'Target Node'
      end
      object Label43: TLabel
        Left = 336
        Top = 176
        Width = 117
        Height = 13
        Caption = 'Cycles before transmition'
      end
      object Label44: TLabel
        Left = 336
        Top = 380
        Width = 117
        Height = 13
        Caption = 'Cycles before transmition'
      end
      object Label6: TLabel
        Left = 176
        Top = 408
        Width = 48
        Height = 13
        Caption = 'Serial Port'
      end
      object Label7: TLabel
        Left = 176
        Top = 204
        Width = 48
        Height = 13
        Caption = 'Serial Port'
      end
      object VarOutBoxA1: TComboBox
        Left = 84
        Top = 56
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 0
        Text = 'VarOutBoxA1'
      end
      object VarOutBoxA2: TComboBox
        Left = 84
        Top = 84
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 1
        Text = 'ComboBox1'
      end
      object VarOutBoxA3: TComboBox
        Left = 84
        Top = 112
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 2
        Text = 'ComboBox1'
      end
      object VarOutBoxA4: TComboBox
        Left = 84
        Top = 140
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 3
        Text = 'ComboBox1'
      end
      object VarOutBoxB1: TComboBox
        Left = 84
        Top = 260
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 4
        Text = 'ComboBox1'
      end
      object VarOutBoxB2: TComboBox
        Left = 84
        Top = 288
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 5
        Text = 'ComboBox1'
      end
      object VarOutBoxB3: TComboBox
        Left = 84
        Top = 316
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 6
        Text = 'ComboBox1'
      end
      object VarOutBoxB4: TComboBox
        Left = 84
        Top = 344
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 7
        Text = 'ComboBox1'
      end
      object TrigOutBoxA1: TComboBox
        Left = 384
        Top = 56
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 8
        Text = 'ComboBox1'
      end
      object TrigOutBoxA2: TComboBox
        Left = 384
        Top = 84
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 9
        Text = 'ComboBox1'
      end
      object TrigOutBoxA3: TComboBox
        Left = 384
        Top = 112
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 10
        Text = 'ComboBox1'
      end
      object TrigOutBoxA4: TComboBox
        Left = 384
        Top = 140
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 11
        Text = 'ComboBox1'
      end
      object TrigOutBoxB1: TComboBox
        Left = 384
        Top = 260
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 12
        Text = 'ComboBox1'
      end
      object TrigOutBoxB2: TComboBox
        Left = 384
        Top = 288
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 13
        Text = 'ComboBox1'
      end
      object TrigOutBoxB3: TComboBox
        Left = 384
        Top = 316
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 14
        Text = 'ComboBox1'
      end
      object TrigOutBoxB4: TComboBox
        Left = 384
        Top = 344
        Width = 221
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 15
        Text = 'ComboBox1'
      end
      object AutoTXTriggerB: TComboBox
        Left = 88
        Top = 376
        Width = 240
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 16
        Text = 'AutoTXTriggerB'
      end
      object AutoTXTriggerA: TComboBox
        Left = 88
        Top = 172
        Width = 240
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 17
        Text = 'AutoTXTriggerA'
      end
      object TargetNodeBoxA: TComboBox
        Left = 88
        Top = 200
        Width = 60
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 18
        Text = '0'
      end
      object TargetNodeBoxB: TComboBox
        Left = 88
        Top = 404
        Width = 60
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 19
        Text = '0'
      end
      object TxDelayBoxB: TComboBox
        Left = 456
        Top = 376
        Width = 53
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 20
        Text = '0'
      end
      object TxDelayBoxA: TComboBox
        Left = 456
        Top = 172
        Width = 53
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 21
        Text = '0'
      end
      object GetReplyBoxA: TCheckBox
        Left = 356
        Top = 202
        Width = 73
        Height = 17
        Caption = 'Get Reply'
        TabOrder = 22
      end
      object GetReplyBoxB: TCheckBox
        Left = 356
        Top = 406
        Width = 73
        Height = 17
        Caption = 'Get Reply'
        TabOrder = 23
      end
      object CopySettingsToAllBox: TCheckBox
        Left = 404
        Top = 8
        Width = 209
        Height = 17
        Caption = 'Copy these settings to all profile groups'
        TabOrder = 24
      end
      object SerialPortBoxB: TComboBox
        Left = 232
        Top = 404
        Width = 110
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 25
        Text = '0'
      end
      object SerialPortBoxA: TComboBox
        Left = 232
        Top = 200
        Width = 110
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 26
        Text = '0'
      end
    end
    object CANBUSTab: TTabSheet
      Caption = 'CAN BUS'
      ImageIndex = 1
      object Bevel1: TBevel
        Left = 4
        Top = 32
        Width = 605
        Height = 173
      end
      object Bevel4: TBevel
        Left = 4
        Top = 216
        Width = 605
        Height = 173
      end
      object CanTabTitle: TLabel
        Left = 8
        Top = 8
        Width = 135
        Height = 19
        Caption = 'CAN Bus Outputs'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label21: TLabel
        Left = 12
        Top = 60
        Width = 119
        Height = 13
        Caption = 'Variable Output Source 1'
      end
      object Label22: TLabel
        Left = 12
        Top = 88
        Width = 119
        Height = 13
        Caption = 'Variable Output Source 2'
      end
      object Label23: TLabel
        Left = 12
        Top = 116
        Width = 114
        Height = 13
        Caption = 'Trigger Output Source 1'
      end
      object Label24: TLabel
        Left = 12
        Top = 144
        Width = 114
        Height = 13
        Caption = 'Trigger Output Source 2'
      end
      object Label25: TLabel
        Left = 12
        Top = 244
        Width = 119
        Height = 13
        Caption = 'Variable Output Source 1'
      end
      object Label26: TLabel
        Left = 12
        Top = 272
        Width = 119
        Height = 13
        Caption = 'Variable Output Source 2'
      end
      object Label27: TLabel
        Left = 12
        Top = 300
        Width = 114
        Height = 13
        Caption = 'Trigger Output Source 1'
      end
      object Label28: TLabel
        Left = 12
        Top = 328
        Width = 114
        Height = 13
        Caption = 'Trigger Output Source 2'
      end
      object Label29: TLabel
        Left = 12
        Top = 220
        Width = 61
        Height = 16
        Caption = 'Group B:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label30: TLabel
        Left = 12
        Top = 36
        Width = 61
        Height = 16
        Caption = 'Group A:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label41: TLabel
        Left = 12
        Top = 360
        Width = 101
        Height = 13
        Caption = 'Auto Transmit Trigger'
      end
      object Label42: TLabel
        Left = 12
        Top = 176
        Width = 101
        Height = 13
        Caption = 'Auto Transmit Trigger'
      end
      object Label45: TLabel
        Left = 468
        Top = 176
        Width = 70
        Height = 13
        Caption = 'Transmit Delay'
      end
      object Label46: TLabel
        Left = 328
        Top = 176
        Width = 60
        Height = 13
        Caption = 'Target Node'
      end
      object Label47: TLabel
        Left = 328
        Top = 360
        Width = 60
        Height = 13
        Caption = 'Target Node'
      end
      object Label48: TLabel
        Left = 468
        Top = 360
        Width = 70
        Height = 13
        Caption = 'Transmit Delay'
      end
      object CANVarOutBoxA1: TComboBox
        Left = 140
        Top = 56
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 0
        Text = 'CANVarOutBoxA1'
      end
      object CANVarOutBoxA2: TComboBox
        Left = 140
        Top = 84
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 1
        Text = 'ComboBox1'
      end
      object CANTrigOutBoxA1: TComboBox
        Left = 140
        Top = 112
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 2
        Text = 'ComboBox1'
      end
      object CANTrigOutBoxA2: TComboBox
        Left = 140
        Top = 140
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 3
        Text = 'ComboBox1'
      end
      object CANVarOutBoxB1: TComboBox
        Left = 140
        Top = 240
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 4
        Text = 'ComboBox1'
      end
      object CANVarOutBoxB2: TComboBox
        Left = 140
        Top = 268
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 5
        Text = 'ComboBox1'
      end
      object CANTrigOutBoxB1: TComboBox
        Left = 140
        Top = 296
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 6
        Text = 'ComboBox1'
      end
      object CANTrigOutBoxB2: TComboBox
        Left = 140
        Top = 324
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 7
        Text = 'ComboBox1'
      end
      object CANAutoTxTriggerB: TComboBox
        Left = 120
        Top = 356
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 8
        Text = 'AutoTXTriggerB'
      end
      object CANAutoTxTriggerA: TComboBox
        Left = 120
        Top = 172
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 9
        Text = 'AutoTXTriggerB'
        OnChange = CANAutoTxTriggerAChange
      end
      object CANTargetNodeBoxA: TComboBox
        Left = 396
        Top = 172
        Width = 53
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 10
        Text = '0'
      end
      object CANTxDelayBoxA: TComboBox
        Left = 544
        Top = 172
        Width = 53
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 11
        Text = '0'
      end
      object CANTargetNodeBoxB: TComboBox
        Left = 396
        Top = 356
        Width = 53
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 12
        Text = '0'
      end
      object CANTxDelayBoxB: TComboBox
        Left = 544
        Top = 356
        Width = 53
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 13
        Text = '0'
      end
    end
    object DiscreteIOTab: TTabSheet
      Caption = 'Discrete I/O'
      ImageIndex = 2
      object Bevel6: TBevel
        Left = 88
        Top = 164
        Width = 429
        Height = 157
      end
      object Bevel5: TBevel
        Left = 88
        Top = 64
        Width = 429
        Height = 93
      end
      object DiscreteTabTitle1: TLabel
        Left = 92
        Top = 68
        Width = 113
        Height = 19
        Caption = 'Digital Outputs'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label32: TLabel
        Left = 96
        Top = 104
        Width = 75
        Height = 13
        Caption = 'ExOut 1 Source'
      end
      object Label33: TLabel
        Left = 96
        Top = 132
        Width = 75
        Height = 13
        Caption = 'ExOut 2 Source'
      end
      object DiscreteTabTitle2: TLabel
        Left = 92
        Top = 168
        Width = 119
        Height = 19
        Caption = 'Analog Outputs'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label35: TLabel
        Left = 96
        Top = 204
        Width = 99
        Height = 13
        Caption = 'Analog Out 1 Source'
      end
      object Label36: TLabel
        Left = 92
        Top = 268
        Width = 99
        Height = 13
        Caption = 'Analog Out 2 Source'
      end
      object Label37: TLabel
        Left = 96
        Top = 232
        Width = 87
        Height = 13
        Caption = 'Analog Out 1 Gain'
      end
      object Label38: TLabel
        Left = 92
        Top = 296
        Width = 87
        Height = 13
        Caption = 'Analog Out 2 Gain'
      end
      object ExOutBox1: TComboBox
        Left = 208
        Top = 100
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 0
        Text = 'ExOutBox1'
      end
      object ExOutBox2: TComboBox
        Left = 208
        Top = 128
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 1
        Text = 'ComboBox1'
      end
      object AnOutBox1: TComboBox
        Left = 208
        Top = 196
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 2
        Text = 'AnOutBox1'
      end
      object AnOutBox2: TComboBox
        Left = 208
        Top = 264
        Width = 301
        Height = 21
        DropDownCount = 32
        ItemHeight = 0
        TabOrder = 3
        Text = 'ComboBox1'
      end
      object GainEdit1: TEdit
        Left = 208
        Top = 224
        Width = 61
        Height = 21
        TabOrder = 4
        Text = 'GainEdit1'
      end
      object GainEdit2: TEdit
        Left = 208
        Top = 292
        Width = 61
        Height = 21
        TabOrder = 5
        Text = 'Edit1'
      end
    end
  end
  object Button3: TButton
    Left = 4
    Top = 468
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 1
    OnClick = SetDefaultsExecute
  end
  object Button1: TButton
    Left = 468
    Top = 468
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 2
    OnClick = SaveAndCloseExecute
  end
  object Button2: TButton
    Left = 548
    Top = 468
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
    OnClick = CancelAndCloseExecute
  end
  object ActionList1: TActionList
    Left = 88
    Top = 464
    object SetupSerialTab: TAction
      Caption = 'SetupSerialTab'
      OnExecute = SetupSerialTabExecute
    end
    object SetupCANTab: TAction
      Caption = 'SetupCANTab'
      OnExecute = SetupCANTabExecute
    end
    object SetupDiscreteTab: TAction
      Caption = 'SetupDiscreteTab'
      OnExecute = SetupDiscreteTabExecute
    end
    object DefaultSerialTab: TAction
      Caption = 'DefaultSerialTab'
      OnExecute = DefaultSerialTabExecute
    end
    object DefaultCANTab: TAction
      Caption = 'DefaultCANTab'
      OnExecute = DefaultCANTabExecute
    end
    object DefaultDiscreteTab: TAction
      Caption = 'DefaultDiscreteTab'
      OnExecute = DefaultDiscreteTabExecute
    end
    object SetDefaults: TAction
      Caption = 'SetDefaults'
      OnExecute = SetDefaultsExecute
    end
    object SaveSerialTab: TAction
      Caption = 'SaveSerialTab'
      OnExecute = SaveSerialTabExecute
    end
    object SaveCANTab: TAction
      Caption = 'SaveCANTab'
      OnExecute = SaveCANTabExecute
    end
    object SaveDiscreteTab: TAction
      Caption = 'SaveDiscreteTab'
      OnExecute = SaveDiscreteTabExecute
    end
    object SaveAndClose: TAction
      Caption = 'SaveAndClose'
      OnExecute = SaveAndCloseExecute
    end
    object CancelAndClose: TAction
      Caption = 'CancelAndClose'
      OnExecute = CancelAndCloseExecute
    end
  end
end
