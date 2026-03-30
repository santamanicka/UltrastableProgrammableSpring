//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ModulatorsEditUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TModulatorsEditForm *ModulatorsEditForm;
//---------------------------------------------------------------------------
__fastcall TModulatorsEditForm::TModulatorsEditForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupScaleAndBiasTab->Execute();
    SetupOscillatorTab->Execute();
    SetupRandomisersTab->Execute();
    SetupParametersTab->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TModulatorsEditForm::SetupScaleAndBiasTabExecute(TObject *Sender)
{
	//setup the form

    AnsiString Title;
    Title = "Scale and Bias for Profile Group ";
    Title += ProfileEditForm->CurrentEditingProfile;
    ScaleAndBiasTitle->Caption = Title;

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
void __fastcall TModulatorsEditForm::SaveAndCloseExecute(TObject *Sender)
{
	//
    SaveScaleAndBiasTab->Execute();
    SaveOscillatorTab->Execute();
    SaveRandomisersTab->Execute();
    SaveParametersTab->Execute();
    ModulatorsEditForm->Close();

}
//---------------------------------------------------------------------------


void __fastcall TModulatorsEditForm::SaveScaleAndBiasTabExecute(
      TObject *Sender)
{
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

void __fastcall TModulatorsEditForm::CancelAndCloseExecute(TObject *Sender)
{
	ModulatorsEditForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SetDefaultsExecute(TObject *Sender)
{
	switch( PageControl1->ActivePageIndex )
    {
    case 0:
    	SetDefaultScaleAndBiasTab->Execute();
        break;
    case 1:
        SetDefaultOscillatorTab->Execute();
        break;
    case 2:
        SetDefaultRandomisersTab->Execute();
        break;
    case 3:
        SetDefaultParametersTab->Execute();        
    default:
    	break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SetDefaultScaleAndBiasTabExecute(
      TObject *Sender)
{
	//
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

void __fastcall TModulatorsEditForm::SetDefaultOscillatorTabExecute(
      TObject *Sender)
{
	//
    StepEdit->Text 		= 16;
    PrescaleEdit->Text 	= 1;
    MaxEdit->Text		= 1024;
    MinEdit->Text		= -1024;
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SaveOscillatorTabExecute(
      TObject *Sender)
{
	ProfileEditForm->TempI8Var[ _StepSize ] = StepEdit->Text.ToInt();
    ProfileEditForm->TempI8Var[ _SkipRate ] = PrescaleEdit->Text.ToInt();

    ProfileEditForm->TempSI16Var[ _OSC1Max ] = MaxEdit->Text.ToInt();
    ProfileEditForm->TempSI16Var[ _OSC1Min ] = MinEdit->Text.ToInt();
    ProfileEditForm->TempSI16Var[ _Iterator ] = ProfileEditForm->TempI8Var[ _StepSize ];
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SetupOscillatorTabExecute(
      TObject *Sender)
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
    Title = "Oscillator for Profile Group ";
    Title +=  ProfileEditForm->CurrentEditingProfile;
    OscillatorTitle->Caption = Title;
    StepEdit->Text 		= ProfileEditForm->TempI8Var[ _StepSize ];
    PrescaleEdit->Text 	= ProfileEditForm->TempI8Var[ _SkipRate ];

    MaxEdit->Text		= ProfileEditForm->TempSI16Var[ _OSC1Max ];
    MinEdit->Text		= ProfileEditForm->TempSI16Var[ _OSC1Min ];
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SetupRandomisersTabExecute(
      TObject *Sender)
{
    //
    int ListIndex = 0;
    AnsiString Title;
    Title = "Randomisers for Profile Group ";
    Title += ProfileEditForm->CurrentEditingProfile;
    RandomisersTitle->Caption = Title;

    double TempVal;
    int TempInt;
    ForceRandomiserTriggerList->Items = ProfileEditForm->VariableList8;
    PDampRandomiserTriggerList->Items = ProfileEditForm->VariableList8;
    NDampRandomiserTriggerList->Items = ProfileEditForm->VariableList8;
    MutationBiasSourceBox->Items = ProfileEditForm->VariableList16;

    ListIndex =  ProfileEditForm->TempI8Ptr[_MutateForceFlag_ptr];
    ForceRandomiserTriggerList->ItemIndex = ListIndex;
    ListIndex =  ProfileEditForm->TempI8Ptr[_MutatePDampingFlag_ptr];
    PDampRandomiserTriggerList->ItemIndex = ListIndex;
    ListIndex =  ProfileEditForm->TempI8Ptr[_MutateNDampingFlag_ptr];
    NDampRandomiserTriggerList->ItemIndex = ListIndex;

    ListIndex = ProfileEditForm->TempSI16Ptr[_ProfileMutateBias_ptr];
    MutationBiasSourceBox->ItemIndex = ListIndex;

    RangeEdit->Text = ProfileEditForm->TempSI16Var[ _ProfileMutateRandomRange ];
    MaxValEdit->Text = ProfileEditForm->TempSI16Var[ _ProfileMutateUpperLimit ];
    MinValEdit->Text = ProfileEditForm->TempSI16Var[ _ProfileMutateLowerLimit ];

    DefaultMutateBiasBox->Text = ProfileEditForm->TempSI16Var[ _ProfileMutateDefaultBias ];

    TempVal = (double)ProfileEditForm->TempSI16Var[ _ProfileMutateRangeScale ];
    TempVal/=100;
    BiasScaleEdit->Text = TempVal;
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SetDefaultRandomisersTabExecute(
      TObject *Sender)
{
    //
    ForceRandomiserTriggerList->ItemIndex = _GlobalDefaultFalse;
    PDampRandomiserTriggerList->ItemIndex = _GlobalDefaultFalse;
    NDampRandomiserTriggerList->ItemIndex = _GlobalDefaultFalse;
    MutationBiasSourceBox->ItemIndex = _ProfileMutateDefaultBias;

    RangeEdit->Text = 50;
    MaxValEdit->Text = 100;
    MinValEdit->Text = -100;

    DefaultMutateBiasBox->Text = 0;

    BiasScaleEdit->Text = 1.0;
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SaveRandomisersTabExecute(
      TObject *Sender)
{
    //
    double TempVal;
    ProfileEditForm->TempI8Ptr[_MutateForceFlag_ptr]  = ForceRandomiserTriggerList->ItemIndex;
    ProfileEditForm->TempI8Ptr[_MutatePDampingFlag_ptr]  = PDampRandomiserTriggerList->ItemIndex;
    ProfileEditForm->TempI8Ptr[_MutateNDampingFlag_ptr]  = NDampRandomiserTriggerList->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_ProfileMutateBias_ptr] =  MutationBiasSourceBox->ItemIndex;

    ProfileEditForm->TempSI16Var[ _ProfileMutateRandomRange ] =  RangeEdit->Text.ToIntDef(50);
    ProfileEditForm->TempSI16Var[ _ProfileMutateUpperLimit ] =  MaxValEdit->Text.ToIntDef(100);
    ProfileEditForm->TempSI16Var[ _ProfileMutateLowerLimit ] =  MinValEdit->Text.ToIntDef(-100);

    ProfileEditForm->TempSI16Var[ _ProfileMutateDefaultBias ] = DefaultMutateBiasBox->Text.ToIntDef(0);
    TempVal =  BiasScaleEdit->Text.ToDouble();
    TempVal *= 100;
    ProfileEditForm->TempSI16Var[ _ProfileMutateRangeScale ] = (int)TempVal;
}
//---------------------------------------------------------------------------



void __fastcall TModulatorsEditForm::SaveParametersTabExecute(
      TObject *Sender)
{
     ProfileEditForm->TempI8Var[ _AnalyzePolygonSide ] = PolygonSidesEdit->Text.ToIntDef(20);
     ProfileEditForm->TempI8Var[ _AnalyzeTVZfactor ] = TVZRadiusEdit->Text.ToIntDef(2);
     ProfileEditForm->TempSI16Var[ _AnalyzeTVZdropBy ] = TVZDropByEdit->Text.ToIntDef(6);
     ProfileEditForm->TempI8Var[ _AnalyzeViabilityAngle ] = ViabilityAngle->Text.ToIntDef(30);
     ProfileEditForm->TempI8Var[ _AnalyzeEvalTime ] = EvalTimeEdit->Text.ToIntDef(30);
     ProfileEditForm->TempI8Var[ _AnalyzeViabilityVelocity ] = ViabilityVelocity->Text.ToIntDef(30);
     ProfileEditForm->TempI8Var[ _AnalyzeMutationRange ] = MutationRangeEdit->Text.ToIntDef(80);
     ProfileEditForm->TempI8Var[ _AnalyzeDampingMutation ] = dampingMutationEdit->Text.ToIntDef(20);
     ProfileEditForm->TempI8Var[ _AnalyzeSamples ] = AnalysisSamplesEdit->Text.ToIntDef(50);
}
//---------------------------------------------------------------------------

void __fastcall TModulatorsEditForm::SetupParametersTabExecute(
      TObject *Sender)
{
     PolygonSidesEdit->Text = ProfileEditForm->TempI8Var[ _AnalyzePolygonSide ];
     TVZRadiusEdit->Text = ProfileEditForm->TempI8Var[ _AnalyzeTVZfactor ];
     TVZDropByEdit->Text = ProfileEditForm->TempSI16Var[ _AnalyzeTVZdropBy ];
     ViabilityAngle->Text = ProfileEditForm->TempI8Var[ _AnalyzeViabilityAngle ];
     EvalTimeEdit->Text = ProfileEditForm->TempI8Var[ _AnalyzeEvalTime ];
     ViabilityVelocity->Text = ProfileEditForm->TempI8Var[ _AnalyzeViabilityVelocity ];
     MutationRangeEdit->Text = ProfileEditForm->TempI8Var[ _AnalyzeMutationRange ];
     dampingMutationEdit->Text = ProfileEditForm->TempI8Var[ _AnalyzeDampingMutation ];
     AnalysisSamplesEdit->Text = ProfileEditForm->TempI8Var[ _AnalyzeSamples ];
}
//---------------------------------------------------------------------------


void __fastcall TModulatorsEditForm::SetDefaultParametersTabExecute(
      TObject *Sender)
{
     PolygonSidesEdit->Text = 20;
     TVZRadiusEdit->Text = 2;
     TVZDropByEdit->Text = 6;
     ViabilityAngle->Text = 30;
     EvalTimeEdit->Text = 30;
     ViabilityVelocity->Text = 30;
     MutationRangeEdit->Text = 80;
     dampingMutationEdit->Text = 20;
     AnalysisSamplesEdit->Text = 50;
}
//---------------------------------------------------------------------------

