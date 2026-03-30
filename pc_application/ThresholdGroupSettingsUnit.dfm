object ThresholdGroupSettingsForm: TThresholdGroupSettingsForm
  Left = 104
  Top = 159
  Width = 416
  Height = 478
  Caption = 'Threshold Group Settings '
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
    Width = 407
    Height = 413
    ActivePage = ThresholdGroup1
    TabIndex = 0
    TabOrder = 0
    object ThresholdGroup1: TTabSheet
      Caption = 'Threshold Group 1'
      object Bevel1: TBevel
        Left = 46
        Top = 204
        Width = 315
        Height = 129
      end
      object Bevel2: TBevel
        Left = 46
        Top = 72
        Width = 315
        Height = 129
      end
      object Label10: TLabel
        Left = 56
        Top = 78
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Positive Threshold (PT) 1'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label14: TLabel
        Left = 56
        Top = 242
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label15: TLabel
        Left = 56
        Top = 174
        Width = 86
        Height = 13
        Caption = 'PT1 Default Level'
      end
      object Label13: TLabel
        Left = 56
        Top = 274
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Label20: TLabel
        Left = 56
        Top = 210
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'NegativeThreshold (NT) 1'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label24: TLabel
        Left = 56
        Top = 110
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label25: TLabel
        Left = 56
        Top = 306
        Width = 87
        Height = 13
        Caption = 'NT1 Default Level'
      end
      object Label22: TLabel
        Left = 56
        Top = 42
        Width = 74
        Height = 13
        Caption = 'Variable to Test'
      end
      object Label23: TLabel
        Left = 56
        Top = 142
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Tab1Title: TLabel
        Left = 56
        Top = 10
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Threshold Group 1'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object PT1DefaultEdit1: TEdit
        Left = 148
        Top = 170
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 0
        Text = '1024'
      end
      object PT1SourceList1: TComboBox
        Left = 148
        Top = 38
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 1
      end
      object PT1LevelList1: TComboBox
        Left = 148
        Top = 106
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 2
      end
      object PT1EnableList1: TComboBox
        Left = 148
        Top = 138
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 3
      end
      object NT1DefaultEdit1: TEdit
        Left = 148
        Top = 302
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 4
        Text = '-1024'
      end
      object NT1LevelList1: TComboBox
        Left = 148
        Top = 238
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 5
      end
      object NT1EnableList1: TComboBox
        Left = 148
        Top = 270
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 6
      end
    end
    object ThresholdGroup2: TTabSheet
      Caption = 'Threshold Group 2'
      ImageIndex = 1
      object Bevel3: TBevel
        Left = 46
        Top = 72
        Width = 315
        Height = 129
      end
      object Tab2Title: TLabel
        Left = 56
        Top = 10
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Threshold Group 2'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label3: TLabel
        Left = 56
        Top = 42
        Width = 74
        Height = 13
        Caption = 'Variable to Test'
      end
      object Label4: TLabel
        Left = 56
        Top = 78
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Positive Threshold (PT) 2'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label5: TLabel
        Left = 56
        Top = 110
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label6: TLabel
        Left = 56
        Top = 142
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Label7: TLabel
        Left = 56
        Top = 174
        Width = 86
        Height = 13
        Caption = 'PT2 Default Level'
      end
      object Bevel4: TBevel
        Left = 46
        Top = 204
        Width = 315
        Height = 129
      end
      object Label8: TLabel
        Left = 56
        Top = 210
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'NegativeThreshold (NT) 2'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label9: TLabel
        Left = 56
        Top = 242
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label11: TLabel
        Left = 56
        Top = 274
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Label12: TLabel
        Left = 56
        Top = 306
        Width = 87
        Height = 13
        Caption = 'NT2 Default Level'
      end
      object PT1SourceList2: TComboBox
        Left = 148
        Top = 38
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 0
      end
      object PT1LevelList2: TComboBox
        Left = 148
        Top = 106
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 1
      end
      object PT1EnableList2: TComboBox
        Left = 148
        Top = 138
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 2
      end
      object PT1DefaultEdit2: TEdit
        Left = 148
        Top = 170
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 3
        Text = '1024'
      end
      object NT1LevelList2: TComboBox
        Left = 148
        Top = 238
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 4
      end
      object NT1EnableList2: TComboBox
        Left = 148
        Top = 270
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 5
      end
      object NT1DefaultEdit2: TEdit
        Left = 148
        Top = 302
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 6
        Text = '-1024'
      end
    end
    object ThresholdGroup3: TTabSheet
      Caption = 'Threshold Group 3'
      ImageIndex = 2
      object Bevel5: TBevel
        Left = 46
        Top = 72
        Width = 315
        Height = 129
      end
      object Tab3Title: TLabel
        Left = 56
        Top = 10
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Threshold Group 3'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label17: TLabel
        Left = 56
        Top = 42
        Width = 74
        Height = 13
        Caption = 'Variable to Test'
      end
      object Label18: TLabel
        Left = 56
        Top = 78
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Positive Threshold (PT) 3'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label19: TLabel
        Left = 56
        Top = 110
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label21: TLabel
        Left = 56
        Top = 142
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Label26: TLabel
        Left = 56
        Top = 174
        Width = 86
        Height = 13
        Caption = 'PT3 Default Level'
      end
      object Bevel6: TBevel
        Left = 46
        Top = 204
        Width = 315
        Height = 129
      end
      object Label27: TLabel
        Left = 56
        Top = 210
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'NegativeThreshold (NT) 3'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label28: TLabel
        Left = 56
        Top = 242
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label29: TLabel
        Left = 56
        Top = 274
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Label30: TLabel
        Left = 56
        Top = 306
        Width = 87
        Height = 13
        Caption = 'NT3 Default Level'
      end
      object PT1SourceList3: TComboBox
        Left = 148
        Top = 38
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 0
      end
      object PT1LevelList3: TComboBox
        Left = 148
        Top = 106
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 1
      end
      object PT1EnableList3: TComboBox
        Left = 148
        Top = 138
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 2
      end
      object PT1DefaultEdit3: TEdit
        Left = 148
        Top = 170
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 3
        Text = '1024'
      end
      object NT1LevelList3: TComboBox
        Left = 148
        Top = 238
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 4
      end
      object NT1EnableList3: TComboBox
        Left = 148
        Top = 270
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 5
      end
      object NT1DefaultEdit3: TEdit
        Left = 148
        Top = 302
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 6
        Text = '-1024'
      end
    end
    object ThresholdGroup4: TTabSheet
      Caption = 'Threshold Group 4'
      ImageIndex = 3
      object Bevel7: TBevel
        Left = 46
        Top = 72
        Width = 315
        Height = 129
      end
      object Tab4Title: TLabel
        Left = 56
        Top = 10
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Threshold Group 4'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label32: TLabel
        Left = 56
        Top = 42
        Width = 74
        Height = 13
        Caption = 'Variable to Test'
      end
      object Label33: TLabel
        Left = 56
        Top = 78
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'Positive Threshold (PT) 4'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label34: TLabel
        Left = 56
        Top = 110
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label35: TLabel
        Left = 56
        Top = 142
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Label36: TLabel
        Left = 56
        Top = 174
        Width = 86
        Height = 13
        Caption = 'PT4 Default Level'
      end
      object Bevel8: TBevel
        Left = 46
        Top = 204
        Width = 315
        Height = 129
      end
      object Label37: TLabel
        Left = 56
        Top = 210
        Width = 297
        Height = 19
        AutoSize = False
        Caption = 'NegativeThreshold (NT) 4'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Label38: TLabel
        Left = 56
        Top = 242
        Width = 84
        Height = 13
        Caption = 'Threshold Source'
      end
      object Label39: TLabel
        Left = 56
        Top = 274
        Width = 70
        Height = 13
        Caption = 'Enable Source'
      end
      object Label40: TLabel
        Left = 56
        Top = 306
        Width = 87
        Height = 13
        Caption = 'NT4 Default Level'
      end
      object PT1SourceList4: TComboBox
        Left = 148
        Top = 38
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 0
      end
      object PT1LevelList4: TComboBox
        Left = 148
        Top = 106
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 1
      end
      object PT1EnableList4: TComboBox
        Left = 148
        Top = 138
        Width = 203
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 2
      end
      object PT1DefaultEdit4: TEdit
        Left = 148
        Top = 170
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 3
        Text = '1024'
      end
      object NT1LevelList4: TComboBox
        Left = 148
        Top = 238
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 4
      end
      object NT1EnableList4: TComboBox
        Left = 148
        Top = 270
        Width = 201
        Height = 21
        DropDownCount = 32
        ItemHeight = 13
        TabOrder = 5
      end
      object NT1DefaultEdit4: TEdit
        Left = 148
        Top = 302
        Width = 57
        Height = 21
        HelpType = htKeyword
        HelpKeyword = 'Default'
        TabOrder = 6
        Text = '-1024'
      end
    end
  end
  object OKButton: TButton
    Left = 244
    Top = 416
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
    OnClick = SaveAndExitExecute
  end
  object CancelButton: TButton
    Left = 328
    Top = 416
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
    OnClick = CancelAndExitExecute
  end
  object SetDefaultButton: TButton
    Left = 4
    Top = 416
    Width = 75
    Height = 25
    Caption = 'Set Defaults'
    TabOrder = 3
    OnClick = SetDefaultsExecute
  end
  object ActionList: TActionList
    Left = 156
    Top = 416
    object SetupForm: TAction
      Caption = 'SetupForm'
      OnExecute = SetupFormExecute
    end
    object SaveAndExit: TAction
      Caption = 'SaveAndExit'
      OnExecute = SaveAndExitExecute
    end
    object CancelAndExit: TAction
      Caption = 'CancelAndExit'
      OnExecute = CancelAndExitExecute
    end
    object ChangeTab: TAction
      Caption = 'ChangeTab'
    end
    object SetupTab1: TAction
      Caption = 'SetupTab1'
      OnExecute = SetupTab1Execute
    end
    object SetupTab2: TAction
      Caption = 'SetupTab2'
      OnExecute = SetupTab2Execute
    end
    object SetupTab3: TAction
      Caption = 'SetupTab3'
      OnExecute = SetupTab3Execute
    end
    object SetupTab4: TAction
      Caption = 'SetupTab4'
      OnExecute = SetupTab4Execute
    end
    object SetDefaults: TAction
      Caption = 'SetDefaults'
      OnExecute = SetDefaultsExecute
    end
    object DefaultTab1: TAction
      Caption = 'DefaultTab1'
      OnExecute = DefaultTab1Execute
    end
    object DefaultTab2: TAction
      Caption = 'DefaultTab2'
      OnExecute = DefaultTab2Execute
    end
    object DefaultTab3: TAction
      Caption = 'DefaultTab3'
      OnExecute = DefaultTab3Execute
    end
    object DefaultTab4: TAction
      Caption = 'DefaultTab4'
      OnExecute = DefaultTab4Execute
    end
    object SaveTab1: TAction
      Caption = 'SaveTab1'
      OnExecute = SaveTab1Execute
    end
    object SaveTab2: TAction
      Caption = 'SaveTab2'
      OnExecute = SaveTab2Execute
    end
    object SaveTab3: TAction
      Caption = 'SaveTab3'
      OnExecute = SaveTab3Execute
    end
    object SaveTab4: TAction
      Caption = 'SaveTab4'
      OnExecute = SaveTab4Execute
    end
  end
end
