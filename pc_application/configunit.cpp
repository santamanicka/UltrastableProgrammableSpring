//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configunit.h"
#include "Bcb_pgm.h"

#define WSC_Baud9600   5
#define WSC_Baud19200  6
#define WSC_Baud38400  7
#define WSC_Baud57600  8
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConfigureForm *ConfigureForm;
//---------------------------------------------------------------------------
__fastcall TConfigureForm::TConfigureForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConfigureForm::ChangeBAUDRateExecute(TObject *Sender)
{
	//set the baud rate
    int item = BaudSelectorBox->ItemIndex;
    AnsiString line = "Baud rate set to ";
    switch (item)
    {
    	case 0:
            REMOTE->TheBaud = WSC_Baud9600;
            line += "9600";
            PrintMessage(line);
            REMOTE->BaudText->Caption = "9600";
            break;
        case 1:
            REMOTE->TheBaud = WSC_Baud19200;
            line += "19200";
            PrintMessage(line);
            REMOTE->BaudText->Caption = "19200";
            break;
        case 2:
            REMOTE->TheBaud = WSC_Baud38400;
            line += "38400";
            PrintMessage(line);
            REMOTE->BaudText->Caption = "38400";
            break;
        case 3:
            REMOTE->TheBaud = WSC_Baud57600;
            line += "57600";
            PrintMessage(line);
            REMOTE->BaudText->Caption = "57600";
            break;
        default:
            REMOTE->TheBaud = WSC_Baud9600;
            line += "DEFAULTING - 9600";
            PrintMessage(line);
            REMOTE->BaudText->Caption = "9600";
    }
}
//---------------------------------------------------------------------------

void TConfigureForm::PrintMessage(AnsiString Line)
{
     Memo1->Lines->Add(Line);

}
//---------------------------------------------------------------------------

void __fastcall TConfigureForm::ChangeCOMMPortExecute(TObject *Sender)
{
        AnsiString line = "Comm Port Set To ";
        REMOTE->ThePort = CommPortSelectorBox->ItemIndex;
        if(REMOTE->ThePort < 0) REMOTE->ThePort = 0;
        line += REMOTE->ThePort + 1;

        REMOTE->CommText->Caption = (REMOTE->ThePort + 1);

        PrintMessage( line);
}
//---------------------------------------------------------------------------


void __fastcall TConfigureForm::FormDestroy(TObject *Sender)
{
	//
         REMOTE->ThePort = CommPortSelectorBox->ItemIndex;
         REMOTE->CommText->Caption = (REMOTE->ThePort + 1);
}
//---------------------------------------------------------------------------

void __fastcall TConfigureForm::FormCreate(TObject *Sender)
{
       RobotScaleEdit->Text = "NULL";
       int BaudRate = REMOTE->TheBaud;
       int port = REMOTE->ThePort;
       switch (BaudRate)
    {
    	case 5:
            BaudSelectorBox->ItemIndex = 0;
            break;
        case 6:
            BaudSelectorBox->ItemIndex = 1;
            break;
        case 7:
            BaudSelectorBox->ItemIndex = 2;
            break;
        case 8:
            BaudSelectorBox->ItemIndex = 3;
            break;
        default:
            BaudSelectorBox->ItemIndex = 2;
    }
    CommPortSelectorBox->ItemIndex = port;

       //StaticText1->Caption = BaudRate;
}
//---------------------------------------------------------------------------

