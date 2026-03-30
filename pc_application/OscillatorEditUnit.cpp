//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OscillatorEditUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOscillatorEditForm *OscillatorEditForm;
//---------------------------------------------------------------------------
__fastcall TOscillatorEditForm::TOscillatorEditForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TOscillatorEditForm::SetupFormExecute(TObject *Sender)
{
	/*
    Int16 Variables
    //the iterator value for the oscillator (the actual value that is added to the output to update it)
	#define 	_Iterator				15
	//the Minimum value that it can reach
	#define 	_OSC1Min					16
	//the maximum value it can reach
	#define 	_OSC1Max					17

    Int8 Variables:
    //Oscillator step size for iterating
	#define 	_StepSize				6

	//A prescaler to allow the iteration rate for the oscillator to be less than that of the profile
	#define 	_SkipRate				7
	*/
    AnsiString Title;
    Title = "Oscillator for Profile Group: ";
    Title +=  ProfileEditForm->CurrentEditingProfile;
    Label1->Caption = Title;
    StepEdit->Text 		= ProfileEditForm->TempI8Var[ _StepSize ];
    PrescaleEdit->Text 	= ProfileEditForm->TempI8Var[ _SkipRate ];

    MaxEdit->Text		= ProfileEditForm->TempSI16Var[ _OSC1Max ];
    MinEdit->Text		= ProfileEditForm->TempSI16Var[ _OSC1Min ];
}
//---------------------------------------------------------------------------
void __fastcall TOscillatorEditForm::SaveAndCloseExecute(TObject *Sender)
{
	//
    ProfileEditForm->TempI8Var[ _StepSize ] = StepEdit->Text.ToInt();
    ProfileEditForm->TempI8Var[ _SkipRate ] = PrescaleEdit->Text.ToInt();

    ProfileEditForm->TempSI16Var[ _OSC1Max ] = MaxEdit->Text.ToInt();
    ProfileEditForm->TempSI16Var[ _OSC1Min ] = MinEdit->Text.ToInt();
    ProfileEditForm->TempSI16Var[ _Iterator ] = ProfileEditForm->TempI8Var[ _StepSize ];
}
//---------------------------------------------------------------------------


void __fastcall TOscillatorEditForm::Button2Click(TObject *Sender)
{
       SaveAndClose->Execute();
       OscillatorEditForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TOscillatorEditForm::Button3Click(TObject *Sender)
{
	//
    StepEdit->Text 		= 16;
    PrescaleEdit->Text 	= 1;
    MaxEdit->Text		= 1024;
    MinEdit->Text		= -1024;
}
//---------------------------------------------------------------------------

void __fastcall TOscillatorEditForm::Button1Click(TObject *Sender)
{
    OscillatorEditForm->Close();
}
//---------------------------------------------------------------------------

