unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    Edit1: TEdit;
    Label1: TLabel;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.Button1Click(Sender: TObject);
var bitmap:tbitmap;
    i,j:integer;
    b,m:byte;
    s:string;
begin
  bitmap:=tBitMap.Create;
  bitmap.Canvas.Font.name:='²Ó©úÅé';
  bitmap.Canvas.Font.size:=12;
  bitmap.width:=bitmap.Canvas.TextWidth(edit1.text);
  bitmap.height:=bitmap.Canvas.TextHeight(edit1.text);
  bitmap.Canvas.TextOut(0,0,edit1.text);
  for j:=0 to bitmap.Height-1 do
  begin
     s:='';
     b:=0;
     m:=$80;
     for i:=0 to bitmap.width-1 do
     begin
        if bitmap.Canvas.pixels [i,j]=0 then
          b:=(b or m);
        m:=m shr 1;
        if m=0 then
        begin
           s:=s+format('%2.2x,',[b]);
           m:=$80;
           b:=0;
        end;
     end;
     if m<>$80 then s:=s+Format('%2.2x,',[b]);
     memo1.lines.add(s);
     s:='';
  end;
  bitmap.Free;
end;

end.
