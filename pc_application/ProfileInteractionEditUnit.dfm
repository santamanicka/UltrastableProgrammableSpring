object ProfileInteractionEditForm: TProfileInteractionEditForm
  Left = 390
  Top = 123
  BorderStyle = bsDialog
  Caption = 'Profile Group Interaction Editor'
  ClientHeight = 553
  ClientWidth = 447
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
    Left = 370
    Top = 525
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 0
    OnClick = CancelAndCloseExecute
  end
  object Button2: TButton
    Left = 290
    Top = 525
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
    OnClick = SaveAndCloseExecute
  end
  object Button3: TButton
    Left = 2
    Top = 525
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 2
    OnClick = SetDefaultsExecute
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 445
    Height = 521
    ActivePage = ProfileSwitchingTab
    TabIndex = 0
    TabOrder = 3
    object ProfileSwitchingTab: TTabSheet
      Caption = 'Profile Switching'
      object Bevel7: TBevel
        Left = 10
        Top = 417
        Width = 413
        Height = 72
      end
      object WarningLabel2: TLabel
        Left = 16
        Top = 456
        Width = 401
        Height = 29
        AutoSize = False
        WordWrap = True
      end
      object Bevel3: TBevel
        Left = 4
        Top = 29
        Width = 427
        Height = 284
        Style = bsRaised
      end
      object Bevel5: TBevel
        Left = 10
        Top = 273
        Width = 413
        Height = 33
      end
      object Bevel4: TBevel
        Left = 10
        Top = 213
        Width = 413
        Height = 33
      end
      object Bevel2: TBevel
        Left = 10
        Top = 153
        Width = 413
        Height = 33
      end
      object Bevel1: TBevel
        Left = 10
        Top = 93
        Width = 413
        Height = 33
      end
      object SwitcherTitle: TLabel
        Left = 8
        Top = 4
        Width = 303
        Height = 19
        Caption = 'Conditional Profile Switchers for Profile '
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label1: TLabel
        Left = 78
        Top = 68
        Width = 90
        Height = 16
        Caption = 'Trigger Source'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 334
        Top = 68
        Width = 77
        Height = 16
        Caption = 'Alt Profile No'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label52: TLabel
        Left = 22
        Top = 100
        Width = 9
        Height = 19
        Caption = '1'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label53: TLabel
        Left = 22
        Top = 160
        Width = 9
        Height = 19
        Caption = '2'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label56: TLabel
        Left = 22
        Top = 221
        Width = 9
        Height = 19
        Caption = '3'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label59: TLabel
        Left = 22
        Top = 281
        Width = 9
        Height = 19
        Caption = '4'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label68: TLabel
        Left = 22
        Top = 132
        Width = 9
        Height = 19
        Caption = #175
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Symbol'
        Font.Style = []
        ParentFont = False
      end
      object Label62: TLabel
        Left = 22
        Top = 253
        Width = 9
        Height = 19
        Caption = #175
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Symbol'
        Font.Style = []
        ParentFont = False
      end
      object Label63: TLabel
        Left = 22
        Top = 193
        Width = 9
        Height = 19
        Caption = #175
        Font.Charset = SYMBOL_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Symbol'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 62
        Top = 104
        Width = 6
        Height = 13
        Caption = 'If'
      end
      object Label4: TLabel
        Left = 222
        Top = 104
        Width = 100
        Height = 13
        Caption = 'Switch To Profile No:'
      end
      object Label5: TLabel
        Left = 222
        Top = 164
        Width = 100
        Height = 13
        Caption = 'Switch To Profile No:'
      end
      object Label6: TLabel
        Left = 42
        Top = 164
        Width = 29
        Height = 13
        Caption = 'Else If'
      end
      object Label7: TLabel
        Left = 222
        Top = 224
        Width = 100
        Height = 13
        Caption = 'Switch To Profile No:'
      end
      object Label9: TLabel
        Left = 222
        Top = 284
        Width = 100
        Height = 13
        Caption = 'Switch To Profile No:'
      end
      object Label8: TLabel
        Left = 42
        Top = 224
        Width = 29
        Height = 13
        Caption = 'Else If'
      end
      object Label10: TLabel
        Left = 42
        Top = 284
        Width = 29
        Height = 13
        Caption = 'Else If'
      end
      object Bevel6: TBevel
        Left = 4
        Top = 312
        Width = 427
        Height = 98
        Style = bsRaised
      end
      object Label12: TLabel
        Left = 10
        Top = 40
        Width = 143
        Height = 16
        Caption = 'Jump to alternate Profile'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label13: TLabel
        Left = 10
        Top = 320
        Width = 183
        Height = 16
        Caption = 'Incriment or Deincriment Profile'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 14
        Top = 348
        Width = 87
        Height = 13
        Caption = 'Incriment Profile If:'
      end
      object Label14: TLabel
        Left = 14
        Top = 380
        Width = 104
        Height = 13
        Caption = 'De-Incriment Profile If:'
      end
      object Label15: TLabel
        Left = 274
        Top = 348
        Width = 89
        Height = 13
        Caption = 'New Profile will be:'
      end
      object Label16: TLabel
        Left = 274
        Top = 380
        Width = 89
        Height = 13
        Caption = 'New Profile will be:'
      end
      object WarningLabel: TLabel
        Left = 16
        Top = 424
        Width = 401
        Height = 29
        AutoSize = False
        WordWrap = True
      end
      object AltproTriggerlist1: TComboBox
        Left = 76
        Top = 100
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 0
        OnChange = TriggerListWarningExecute
      end
      object AltProTargetlist1: TComboBox
        Left = 330
        Top = 100
        Width = 89
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        Text = '0'
      end
      object AltProTargetlist2: TComboBox
        Left = 334
        Top = 160
        Width = 85
        Height = 21
        ItemHeight = 13
        TabOrder = 2
        Text = '0'
      end
      object AltproTriggerlist2: TComboBox
        Left = 76
        Top = 160
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 3
        OnChange = TriggerListWarningExecute
      end
      object AltProTargetlist3: TComboBox
        Left = 334
        Top = 219
        Width = 85
        Height = 21
        ItemHeight = 13
        TabOrder = 4
        Text = '0'
      end
      object AltproTriggerlist3: TComboBox
        Left = 76
        Top = 219
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 5
        OnChange = TriggerListWarningExecute
      end
      object AltProTargetlist4: TComboBox
        Left = 334
        Top = 279
        Width = 85
        Height = 21
        ItemHeight = 13
        TabOrder = 6
        Text = '0'
      end
      object AltproTriggerlist4: TComboBox
        Left = 76
        Top = 279
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 7
        OnChange = TriggerListWarningExecute
        Items.Strings = (
          '')
      end
      object IncrimentTriggerBox: TComboBox
        Left = 128
        Top = 344
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 8
        OnChange = TriggerListWarningExecute
      end
      object DeincrimentTriggerBox: TComboBox
        Left = 128
        Top = 376
        Width = 141
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 9
        OnChange = TriggerListWarningExecute
      end
    end
    object InterProfileCommTab: TTabSheet
      Caption = 'Inter-Profile Communications'
      ImageIndex = 1
      object Bevel8: TBevel
        Left = 10
        Top = 240
        Width = 413
        Height = 93
      end
      object Bevel10: TBevel
        Left = 10
        Top = 36
        Width = 413
        Height = 93
      end
      object Bevel9: TBevel
        Left = 10
        Top = 140
        Width = 413
        Height = 93
      end
      object CommTitle: TLabel
        Left = 8
        Top = 4
        Width = 303
        Height = 19
        Caption = 'Inter Profile Communications for Profile '
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label17: TLabel
        Left = 58
        Top = 72
        Width = 84
        Height = 13
        Caption = 'Variable Source 1'
      end
      object Label18: TLabel
        Left = 58
        Top = 100
        Width = 84
        Height = 13
        Caption = 'Variable Source 2'
      end
      object Label19: TLabel
        Left = 58
        Top = 176
        Width = 79
        Height = 13
        Caption = 'Trigger Source 1'
      end
      object Label20: TLabel
        Left = 58
        Top = 204
        Width = 79
        Height = 13
        Caption = 'Trigger Source 2'
      end
      object Label21: TLabel
        Left = 18
        Top = 148
        Width = 138
        Height = 16
        Caption = 'Trigger Output Sources'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label22: TLabel
        Left = 18
        Top = 44
        Width = 145
        Height = 16
        Caption = 'Variable Output Sources'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label23: TLabel
        Left = 16
        Top = 244
        Width = 401
        Height = 45
        AutoSize = False
        Caption = 
          'Variable and Trigger outputs can be '#39'seen'#39' by any other profile ' +
          'but their values are only updated if the profile they belong to ' +
          'is active.  You can use them to capture information from one pro' +
          'file and pass it on to another.'
        WordWrap = True
      end
      object Label24: TLabel
        Left = 16
        Top = 288
        Width = 401
        Height = 29
        AutoSize = False
        Caption = 
          'For example you can take the angular velocity that one profile w' +
          'as measuring when it switched to a different profile and use tha' +
          't value to set the bias for the new profile.'
        WordWrap = True
      end
      object VariableSourceBox1: TComboBox
        Left = 156
        Top = 68
        Width = 205
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 0
        OnChange = TriggerListWarningExecute
      end
      object VariableSourceBox2: TComboBox
        Left = 156
        Top = 96
        Width = 205
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 1
        OnChange = TriggerListWarningExecute
      end
      object FlagSourceBox2: TComboBox
        Left = 156
        Top = 200
        Width = 205
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 2
        OnChange = TriggerListWarningExecute
      end
      object FlagSourceBox1: TComboBox
        Left = 156
        Top = 172
        Width = 205
        Height = 21
        DropDownCount = 20
        ItemHeight = 13
        TabOrder = 3
        OnChange = TriggerListWarningExecute
      end
    end
  end
  object ActionList1: TActionList
    Left = 80
    Top = 524
    object SetupProfileSwitchTab: TAction
      Caption = 'SetupProfileSwitchTab'
      OnExecute = SetupProfileSwitchTabExecute
    end
    object SetupInterProfileCommTab: TAction
      Caption = 'SetupInterProfileCommTab'
      OnExecute = SetupInterProfileCommTabExecute
    end
    object SaveAndClose: TAction
      Caption = 'SaveAndClose'
      OnExecute = SaveAndCloseExecute
    end
    object TriggerListWarning: TAction
      Caption = 'TriggerListWarning'
      OnExecute = TriggerListWarningExecute
    end
    object SaveProfileSwitchTab: TAction
      Caption = 'SaveProfileSwitchTab'
      OnExecute = SaveProfileSwitchTabExecute
    end
    object SaveInterProfileCommTab: TAction
      Caption = 'SaveInterProfileCommTab'
      OnExecute = SaveInterProfileCommTabExecute
    end
    object CancelAndClose: TAction
      Caption = 'CancelAndClose'
      OnExecute = CancelAndCloseExecute
    end
    object SetDefaults: TAction
      Caption = 'SetDefaults'
      OnExecute = SetDefaultsExecute
    end
    object SetSwitcherDefaults: TAction
      Caption = 'SetSwitcherDefaults'
      OnExecute = SetSwitcherDefaultsExecute
    end
    object SetInterCommDefaults: TAction
      Caption = 'SetInterCommDefaults'
      OnExecute = SetInterCommDefaultsExecute
    end
  end
end
