//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SerialPortMonitorUnit.h"
#include "bcb_pgm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSerialPortMonitorForm *SerialPortMonitorForm;
//---------------------------------------------------------------------------
__fastcall TSerialPortMonitorForm::TSerialPortMonitorForm(TComponent* Owner)
	: TForm(Owner)
{
	CurrentLine = 0;
    LineLength = 0;
    MessageLine = COMMMemo->Lines->Strings[CurrentLine];
}
//---------------------------------------------------------------------------
void __fastcall TSerialPortMonitorForm::ClearButtonClick(TObject *Sender)
{
	COMMMemo->Clear();
    CurrentLine = 0;
    LineLength = 0;
    MessageLine = COMMMemo->Lines->Strings[CurrentLine];
}
//---------------------------------------------------------------------------
void TSerialPortMonitorForm::PrintCommData(int ByteValue, int flag)
{
	//Adds the byte to the COMMMemo
    if(flag == 0)
    {
        if(ByteValue > 31)
            {
                //if the byte is a character then add
                MessageLine+= (char)ByteValue;
                LineLength++;
            }
         //otherwise add this
            else
            {
                if(ShowHiddenCharsBox->Checked == true) MessageLine += '>';
                LineLength++;
            }
         //if the byte was a CR or LF or line length is to long
         //then write the line to the memo
         //then get the new line
            if(ByteValue == 13 || ByteValue == 10 || LineLength > 120)
            {
                    //Put the line back in the memo
                    COMMMemo->Lines->Strings[CurrentLine] = MessageLine;
                    //Clear the line buffer
                    MessageLine = "";
                    //Move on to the next line
                    CurrentLine++;
                    LineLength = 0;
                    //Add a blank line to the memo (move it on to the next line)
                    COMMMemo->Lines->Add(MessageLine);
            }
            //COMMMemo->Lines->Strings[CurrentLine] = MessagesLine;
    }
    else if(flag==1)
    {
        MessageLine+= (int)ByteValue;
        LineLength++;
    }
}
void __fastcall TSerialPortMonitorForm::UpdateMemoExecute(TObject *Sender)
{
	COMMMemo->Lines->Strings[CurrentLine] = MessageLine;
}
//---------------------------------------------------------------------------

