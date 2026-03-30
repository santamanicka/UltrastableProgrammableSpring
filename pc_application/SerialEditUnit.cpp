//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SerialEditUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSerialEditForm *SerialEditForm;
//---------------------------------------------------------------------------
__fastcall TSerialEditForm::TSerialEditForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TSerialEditForm::SetupFormExecute(TObject *Sender)
{
	//
    AnsiString Title;
    Title = "RS232 Serial I/O for Profile No ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Label1->Caption = Title;

    VarOutBoxA1->Items = ProfileEditForm->VariableList16;
    VarOutBoxA1->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out1_ptr];
    TrigOutBoxA1->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA1->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut1_ptr];

    VarOutBoxA2->Items = ProfileEditForm->VariableList16;
    VarOutBoxA2->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out2_ptr];
    TrigOutBoxA2->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA2->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut2_ptr];

    VarOutBoxA3->Items = ProfileEditForm->VariableList16;
    VarOutBoxA3->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out3_ptr];
    TrigOutBoxA3->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA3->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut3_ptr];

    VarOutBoxA4->Items = ProfileEditForm->VariableList16;
    VarOutBoxA4->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out4_ptr];
    TrigOutBoxA4->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA4->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut4_ptr];


    VarOutBoxB1->Items = ProfileEditForm->VariableList16;
    VarOutBoxB1->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out5_ptr];
    TrigOutBoxB1->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB1->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut5_ptr];

    VarOutBoxB2->Items = ProfileEditForm->VariableList16;
    VarOutBoxB2->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out6_ptr];
    TrigOutBoxB2->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB2->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut6_ptr];

    VarOutBoxB3->Items = ProfileEditForm->VariableList16;
    VarOutBoxB3->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out7_ptr];
    TrigOutBoxB3->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB3->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut7_ptr];

    VarOutBoxB4->Items = ProfileEditForm->VariableList16;
    VarOutBoxB4->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out8_ptr];
    TrigOutBoxB4->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB4->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut8_ptr];

}
//---------------------------------------------------------------------------

void __fastcall TSerialEditForm::SaveFormExecute(TObject *Sender)
{
	//

    ProfileEditForm->TempSI16Ptr[_RS232Out1_ptr] = VarOutBoxA1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut1_ptr] = TrigOutBoxA1->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out2_ptr] = VarOutBoxA2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut2_ptr] = TrigOutBoxA2->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out3_ptr] = VarOutBoxA3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut3_ptr] = TrigOutBoxA3->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out4_ptr] = VarOutBoxA4->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut4_ptr] = TrigOutBoxA4->ItemIndex;


    ProfileEditForm->TempSI16Ptr[_RS232Out5_ptr] = VarOutBoxB1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut5_ptr] = TrigOutBoxB1->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out6_ptr] = VarOutBoxB2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut6_ptr] = TrigOutBoxB2->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out7_ptr] = VarOutBoxB3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut7_ptr] = TrigOutBoxB3->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out8_ptr] = VarOutBoxB4->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut8_ptr] = TrigOutBoxB4->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TSerialEditForm::Button2Click(TObject *Sender)
{
	//cancel
    SerialEditForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TSerialEditForm::Button1Click(TObject *Sender)
{
	//save
    SaveForm->Execute();
    SerialEditForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TSerialEditForm::Button3Click(TObject *Sender)
{
	//defaults
    VarOutBoxA1->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA1->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxA2->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA2->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxA3->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA3->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxA4->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA4->ItemIndex = _GlobalDefaultFalse;


    VarOutBoxB1->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB1->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxB2->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB2->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxB3->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB3->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxB4->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB4->ItemIndex = _GlobalDefaultFalse;
}
//---------------------------------------------------------------------------

