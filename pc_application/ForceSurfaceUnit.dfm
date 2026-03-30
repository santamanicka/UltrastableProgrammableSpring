object ForceSurfacePlotForm: TForceSurfacePlotForm
  Left = 31
  Top = -4
  Width = 989
  Height = 753
  Caption = 'Force Surface plot'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 4
    Top = 4
    Width = 800
    Height = 600
    Visible = False
  end
  object PaintBox1: TPaintBox
    Left = 8
    Top = 8
    Width = 800
    Height = 600
  end
  object Label1: TLabel
    Left = 816
    Top = 648
    Width = 20
    Height = 13
    Caption = 'Bias'
  end
  object Label2: TLabel
    Left = 816
    Top = 620
    Width = 23
    Height = 13
    Caption = 'View'
  end
  object Label3: TLabel
    Left = 816
    Top = 684
    Width = 27
    Height = 13
    Caption = 'Scale'
  end
  object Button1: TButton
    Left = 852
    Top = 76
    Width = 75
    Height = 25
    Caption = 'Redraw'
    TabOrder = 0
    OnClick = DrawGraphsExecute
  end
  object RadioButton1: TRadioButton
    Left = 816
    Top = 4
    Width = 113
    Height = 17
    Caption = '3D Mesh'
    Checked = True
    TabOrder = 1
    TabStop = True
    OnClick = DrawGraphsExecute
  end
  object RadioButton2: TRadioButton
    Left = 816
    Top = 52
    Width = 113
    Height = 17
    Caption = 'Contour Map'
    TabOrder = 2
    OnClick = DrawGraphsExecute
  end
  object SaveButton: TButton
    Left = 852
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 3
    OnClick = SaveImageExecute
  end
  object FilledBox: TCheckBox
    Left = 816
    Top = 28
    Width = 97
    Height = 17
    Caption = 'Filled'
    TabOrder = 4
    OnClick = DrawGraphsExecute
  end
  object TrackBar1: TTrackBar
    Left = 4
    Top = 608
    Width = 805
    Height = 35
    Max = 100
    Orientation = trHorizontal
    Frequency = 1
    Position = 50
    SelEnd = 0
    SelStart = 0
    TabOrder = 5
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = DrawGraphsExecute
  end
  object HBiasBar: TTrackBar
    Left = 4
    Top = 644
    Width = 805
    Height = 35
    Max = 64
    Min = -64
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 6
    ThumbLength = 16
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = DrawGraphsExecute
  end
  object StaticText1: TStaticText
    Left = 848
    Top = 648
    Width = 10
    Height = 17
    Caption = '0'
    TabOrder = 7
  end
  object HScaleBar: TTrackBar
    Left = 4
    Top = 680
    Width = 805
    Height = 35
    Max = 20
    Min = 1
    Orientation = trHorizontal
    Frequency = 1
    Position = 10
    SelEnd = 0
    SelStart = 0
    TabOrder = 8
    ThumbLength = 16
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = DrawGraphsExecute
  end
  object StaticText2: TStaticText
    Left = 848
    Top = 684
    Width = 10
    Height = 17
    Caption = '0'
    TabOrder = 9
  end
  object VBiasBar: TTrackBar
    Left = 816
    Top = 76
    Width = 35
    Height = 529
    Max = 100
    Min = -100
    Orientation = trVertical
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 10
    ThumbLength = 16
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = DrawGraphsExecute
  end
  object ActionList1: TActionList
    Left = 768
    Top = 560
    object DrawSurface: TAction
      Caption = 'DrawSurface'
      OnExecute = DrawSurfaceExecute
    end
    object UpdateImage: TAction
      Caption = 'UpdateImage'
      OnExecute = UpdateImageExecute
    end
    object CreateGraphData: TAction
      Caption = 'CreateGraphData'
      OnExecute = CreateGraphDataExecute
    end
    object DrawGraphs: TAction
      Caption = 'DrawGraphs'
      OnExecute = DrawGraphsExecute
    end
    object DrawContour: TAction
      Caption = 'DrawContour'
      OnExecute = DrawContourExecute
    end
    object ClearImage: TAction
      Caption = 'ClearImage'
      OnExecute = ClearImageExecute
    end
    object SaveImage: TAction
      Caption = 'SaveImage'
      OnExecute = SaveImageExecute
    end
  end
  object SavePictureDialog1: TSavePictureDialog
    DefaultExt = 'bmp'
    FileName = 'Image.bmp'
    FilterIndex = 2
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 732
    Top = 560
  end
end
