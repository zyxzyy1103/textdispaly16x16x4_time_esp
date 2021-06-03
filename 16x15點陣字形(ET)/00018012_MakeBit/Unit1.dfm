object Form1: TForm1
  Left = 93
  Top = 86
  Width = 544
  Height = 375
  Caption = '將字型轉為Bit碼'
  Color = clBtnFace
  Font.Charset = CHINESEBIG5_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = '細明體'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 64
    Height = 16
    Caption = '文字內容'
  end
  object Button1: TButton
    Left = 224
    Top = 304
    Width = 75
    Height = 25
    Caption = '產生字型'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 40
    Width = 513
    Height = 257
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 80
    Top = 8
    Width = 441
    Height = 24
    TabOrder = 2
    Text = 'Delphi K.Top討論區'
  end
end
