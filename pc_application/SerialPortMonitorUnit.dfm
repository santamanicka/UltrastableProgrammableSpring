object SerialPortMonitorForm: TSerialPortMonitorForm
  Left = 23
  Top = 536
  Width = 984
  Height = 199
  BorderStyle = bsSizeToolWin
  Caption = 'Serial Port Monitor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  DesignSize = (
    976
    165)
  PixelsPerInch = 96
  TextHeight = 13
  object Label10: TLabel
    Left = 24
    Top = 27
    Width = 63
    Height = 13
    Caption = 'Byte  :  ASCII'
  end
  object Label1: TLabel
    Left = 128
    Top = 7
    Width = 124
    Height = 13
    Caption = 'Serial Port Formatted Data'
  end
  object RawListMemo: TMemo
    Left = 4
    Top = 44
    Width = 117
    Height = 117
    Anchors = [akLeft, akTop, akBottom]
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object COMMMemo: TMemo
    Left = 124
    Top = 24
    Width = 847
    Height = 137
    Anchors = [akLeft, akTop, akRight, akBottom]
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object PrintRawDataBox: TCheckBox
    Left = 4
    Top = 5
    Width = 113
    Height = 17
    Caption = 'Print Raw Data'
    TabOrder = 2
  end
  object ClearButton: TButton
    Left = 264
    Top = 4
    Width = 57
    Height = 17
    Caption = 'Clear'
    TabOrder = 3
    OnClick = ClearButtonClick
  end
  object ShowHiddenCharsBox: TCheckBox
    Left = 360
    Top = 4
    Width = 221
    Height = 17
    Caption = 'Show non character values as >'
    TabOrder = 4
  end
  object ActionList1: TActionList
    Left = 764
    Top = 8
    object CloseForm: TAction
      Caption = 'CloseForm'
    end
    object UpdateMemo: TAction
      Caption = 'UpdateMemo'
      OnExecute = UpdateMemoExecute
    end
  end
end
