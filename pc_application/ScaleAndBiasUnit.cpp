//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ScaleAndBiasUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TScaleAndBiasForm *ScaleAndBiasForm;
//---------------------------------------------------------------------------
__fastcall TScaleAndBiasForm::TScaleAndBiasForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TScaleAndBiasForm::SetupFormExecute(TObject *Sender)
{
	//setup the form
    double TempVal;
    int TempInt;

    HScaleSourceBox->Items = ProfileEditForm->VariableList16;
    VScaleSourceBox->Items = ProfileEditForm->VariableList16;
    HBiasSourceBox->Items = ProfileEditForm->VariableList16;
    VBiasSourceBox->Items = ProfileEditForm->VariableList16;


    HScaleSourceBox->ItemIndex = ProfileEditForm->TempSI16Ptr[ _HScale_ptr ];
    VScaleSourceBox->ItemIndex = ProfileEditForm->TempSI16Ptr[ _VScale_ptr ];
    HBiasSourceBox->ItemIndex = ProfileEditForm->TempSI16Ptr[ _HBias_ptr ];
    VBiasSourceBox->ItemIndex = ProfileEditForm->TempSI16Ptr[ _VBias_ptr ];

    TempVal = (double)ProfileEditForm->TempSI16Var[ _DefaultHScale ];
    TempVal/=100;
    HScaleEdit->Text = TempVal;

    TempVal = (double)ProfileEditForm->TempSI16Var[ _DefaultVScale ];
    TempVal/=100;
    VScaleEdit->Text =  TempVal;
    HBiasEdit->Text = ProfileEditForm->TempSI16Var[ _DefaultHBias ];
    VBiasEdit->Text = ProfileEditForm->TempSI16Var[ _DefaultVBias ];
    EQEdit->Text = ProfileEditForm->TempSI16Var[ _EQAngle ];
}
//---------------------------------------------------------------------------
void __fastcall TScaleAndBiasForm::SaveAndCloseExecute(TObject *Sender)
{
	//
    double TempVal;
    int TempInt;
    ProfileEditForm->TempSI16Ptr[ _HScale_ptr ] = HScaleSourceBox->ItemIndex;
    ProfileEditForm->TempSI16Ptr[ _VScale_ptr ] = VScaleSourceBox->ItemIndex;
    ProfileEditForm->TempSI16Ptr[ _HBias_ptr ] = HBiasSourceBox->ItemIndex;
   	ProfileEditForm->TempSI16Ptr[ _VBias_ptr ] = VBiasSourceBox->ItemIndex;

    TempVal = HScaleEdit->Text.ToDouble();
    TempVal *= 100;
    ProfileEditForm->TempSI16Var[ _DefaultHScale ] = (int)TempVal;

    TempVal = VScaleEdit->Text.ToDouble();
    TempVal *= 100;
    ProfileEditForm->TempSI16Var[ _DefaultVScale ] = (int)TempVal;

    TempInt = HBiasEdit->Text.ToInt();

    ProfileEditForm->TempSI16Var[ _DefaultHBias ] = TempInt;
    ProfileEditForm->TempSI16Var[ _DefaultVBias ] = VBiasEdit->Text.ToInt();

    TempInt = EQEdit->Text.ToInt();

    ProfileEditForm->TempSI16Var[ _EQAngle ] = TempInt;
}
//---------------------------------------------------------------------------
void __fastcall TScaleAndBiasForm::Button1Click(TObject *Sender)
{
	ScaleAndBiasForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TScaleAndBiasForm::Button2Click(TObject *Sender)
{
    SaveAndClose->Execute();
    ScaleAndBiasForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TScaleAndBiasForm::SetDefaultsButtonClick(TObject *Sender)
{
	//Setup defaults

    HScaleSourceBox->ItemIndex = _DefaultHScale;
    VScaleSourceBox->ItemIndex = _DefaultVScale;
    HBiasSourceBox->ItemIndex = _DefaultHBias;
    VBiasSourceBox->ItemIndex = _DefaultVBias;

    HScaleEdit->Text = 1.00;
    VScaleEdit->Text = 1.00;
    HBiasEdit->Text = 0;
    VBiasEdit->Text = 0;
    EQEdit->Text = 0;
}
//---------------------------------------------------------------------------

