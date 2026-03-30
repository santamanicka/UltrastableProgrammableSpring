object DownloadProgressForm: TDownloadProgressForm
  Left = 373
  Top = 291
  BorderStyle = bsSingle
  Caption = 'Download Progress'
  ClientHeight = 82
  ClientWidth = 391
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 4
    Width = 373
    Height = 41
    AutoSize = False
    WordWrap = True
  end
  object ProgressBar1: TProgressBar
    Left = 6
    Top = 50
    Width = 379
    Height = 27
    Min = 0
    Max = 100
    Smooth = True
    TabOrder = 0
  end
  object ActionList1: TActionList
    Left = 312
    Top = 4
    object ClearLabels: TAction
      Caption = 'ClearLabels'
      OnExecute = ClearLabelsExecute
    end
  end
end
