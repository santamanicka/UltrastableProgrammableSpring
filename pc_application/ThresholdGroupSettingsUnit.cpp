//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
#include "ThresholdGroupSettingsUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TThresholdGroupSettingsForm *ThresholdGroupSettingsForm;
//---------------------------------------------------------------------------
__fastcall TThresholdGroupSettingsForm::TThresholdGroupSettingsForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SetupFormExecute(
      TObject *Sender)
{


	SetupTab1->Execute();
	SetupTab2->Execute();
    SetupTab3->Execute();
    SetupTab4->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SaveAndExitExecute(
      TObject *Sender)
{
	//
    SaveTab1->Execute();
    SaveTab2->Execute();
    SaveTab3->Execute();
    SaveTab4->Execute();
    ThresholdGroupSettingsForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::CancelAndExitExecute(
      TObject *Sender)
{
	//
    ThresholdGroupSettingsForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SetupTab1Execute(TObject *Sender)
{
	//
    AnsiString Title = "Threshold Group 1 for Profile Group ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Tab1Title->Caption = Title;

    PT1SourceList1->Items = ProfileEditForm->VariableList16;
    PT1SourceList1->ItemIndex = ProfileEditForm->TempSI16Ptr[_Threshold1Input_ptr];

    PT1LevelList1->Items = ProfileEditForm->VariableList16;
    PT1LevelList1->ItemIndex = ProfileEditForm->TempSI16Ptr[_PT1Value_ptr];

    PT1EnableList1->Items = ProfileEditForm->VariableList8;
    PT1EnableList1->ItemIndex = ProfileEditForm->TempI8Ptr[_PT1Enabled_ptr];


    NT1LevelList1->Items = ProfileEditForm->VariableList16;
    NT1LevelList1->ItemIndex = ProfileEditForm->TempSI16Ptr[_NT1Value_ptr];

    NT1EnableList1->Items = ProfileEditForm->VariableList8;
    NT1EnableList1->ItemIndex = ProfileEditForm->TempI8Ptr[_NT1Enabled_ptr];


    PT1DefaultEdit1->Text = ProfileEditForm->TempSI16Var[_PT1Default];
    NT1DefaultEdit1->Text = ProfileEditForm->TempSI16Var[_NT1Default];
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SetupTab2Execute(
      TObject *Sender)
{
    //
    AnsiString Title = "Threshold Group 2 for Profile Group ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Tab2Title->Caption = Title;

    PT1SourceList2->Items = ProfileEditForm->VariableList16;
    PT1SourceList2->ItemIndex = ProfileEditForm->TempSI16Ptr[_Threshold2Input_ptr];

    PT1LevelList2->Items = ProfileEditForm->VariableList16;
    PT1LevelList2->ItemIndex = ProfileEditForm->TempSI16Ptr[_PT2Value_ptr];

    PT1EnableList2->Items = ProfileEditForm->VariableList8;
    PT1EnableList2->ItemIndex = ProfileEditForm->TempI8Ptr[_PT2Enabled_ptr];


    NT1LevelList2->Items = ProfileEditForm->VariableList16;
    NT1LevelList2->ItemIndex = ProfileEditForm->TempSI16Ptr[_NT2Value_ptr];

    NT1EnableList2->Items = ProfileEditForm->VariableList8;
    NT1EnableList2->ItemIndex = ProfileEditForm->TempI8Ptr[_NT2Enabled_ptr];


    PT1DefaultEdit2->Text = ProfileEditForm->TempSI16Var[_PT2Default];
    NT1DefaultEdit2->Text = ProfileEditForm->TempSI16Var[_NT2Default];
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SetupTab3Execute(
      TObject *Sender)
{
    //
    AnsiString Title = "Threshold Group 3 for Profile Group ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Tab3Title->Caption = Title;

    PT1SourceList3->Items = ProfileEditForm->VariableList16;
    PT1SourceList3->ItemIndex = ProfileEditForm->TempSI16Ptr[_Threshold3Input_ptr];

    PT1LevelList3->Items = ProfileEditForm->VariableList16;
    PT1LevelList3->ItemIndex = ProfileEditForm->TempSI16Ptr[_PT3Value_ptr];

    PT1EnableList3->Items = ProfileEditForm->VariableList8;
    PT1EnableList3->ItemIndex = ProfileEditForm->TempI8Ptr[_PT3Enabled_ptr];


    NT1LevelList3->Items = ProfileEditForm->VariableList16;
    NT1LevelList3->ItemIndex = ProfileEditForm->TempSI16Ptr[_NT3Value_ptr];

    NT1EnableList3->Items = ProfileEditForm->VariableList8;
    NT1EnableList3->ItemIndex = ProfileEditForm->TempI8Ptr[_NT3Enabled_ptr];


    PT1DefaultEdit3->Text = ProfileEditForm->TempSI16Var[_PT3Default];
    NT1DefaultEdit3->Text = ProfileEditForm->TempSI16Var[_NT3Default];
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SetupTab4Execute(
      TObject *Sender)
{
	//
    AnsiString Title = "Threshold Group 4 for Profile Group ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Tab4Title->Caption = Title;

    PT1SourceList4->Items = ProfileEditForm->VariableList16;
    PT1SourceList4->ItemIndex = ProfileEditForm->TempSI16Ptr[_Threshold4Input_ptr];

    PT1LevelList4->Items = ProfileEditForm->VariableList16;
    PT1LevelList4->ItemIndex = ProfileEditForm->TempSI16Ptr[_PT4Value_ptr];

    PT1EnableList4->Items = ProfileEditForm->VariableList8;
    PT1EnableList4->ItemIndex = ProfileEditForm->TempI8Ptr[_PT4Enabled_ptr];


    NT1LevelList4->Items = ProfileEditForm->VariableList16;
    NT1LevelList4->ItemIndex = ProfileEditForm->TempSI16Ptr[_NT4Value_ptr];

    NT1EnableList4->Items = ProfileEditForm->VariableList8;
    NT1EnableList4->ItemIndex = ProfileEditForm->TempI8Ptr[_NT4Enabled_ptr];


    PT1DefaultEdit4->Text = ProfileEditForm->TempSI16Var[_PT4Default];
    NT1DefaultEdit4->Text = ProfileEditForm->TempSI16Var[_NT4Default];
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SetDefaultsExecute(
      TObject *Sender)
{
	//select the appropriate tab
    switch(PageControl1->ActivePageIndex)
    {
    case 0:
        DefaultTab1->Execute();
    	break;
    case 1:
    	DefaultTab2->Execute();
    	break;
    case 2:
    	DefaultTab3->Execute();
    	break;
    case 3:
    	DefaultTab4->Execute();
    	break;
    default:
    	break;
    }

}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::DefaultTab1Execute(
      TObject *Sender)
{
    PT1SourceList1->ItemIndex = _GlobalDefaultZeroModulator;

    PT1LevelList1->ItemIndex = _PT1Default;

    PT1EnableList1->ItemIndex = _GlobalThresholdDisabled;

    PT1DefaultEdit1->Text = 512;

    NT1LevelList1->ItemIndex = _NT1Default;

    NT1EnableList1->ItemIndex = _GlobalThresholdDisabled;

    NT1DefaultEdit1->Text = -513;
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::DefaultTab2Execute(
      TObject *Sender)
{
	PT1SourceList2->ItemIndex = _GlobalDefaultZeroModulator;

    PT1LevelList2->ItemIndex = _PT2Default;

    PT1EnableList2->ItemIndex = _GlobalThresholdDisabled;

    PT1DefaultEdit2->Text = 512;

    NT1LevelList2->ItemIndex = _NT2Default;

    NT1EnableList2->ItemIndex = _GlobalThresholdDisabled;

    NT1DefaultEdit2->Text = -513;
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::DefaultTab3Execute(
      TObject *Sender)
{
	PT1SourceList3->ItemIndex = _GlobalDefaultZeroModulator;

    PT1LevelList3->ItemIndex = _PT3Default;

    PT1EnableList3->ItemIndex = _GlobalThresholdDisabled;

    PT1DefaultEdit3->Text = 512;

    NT1LevelList3->ItemIndex = _NT3Default;

    NT1EnableList3->ItemIndex = _GlobalThresholdDisabled;

    NT1DefaultEdit3->Text = -513;
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::DefaultTab4Execute(
      TObject *Sender)
{
	PT1SourceList4->ItemIndex = _GlobalDefaultZeroModulator;

    PT1LevelList4->ItemIndex = _PT4Default;

    PT1EnableList4->ItemIndex = _GlobalThresholdDisabled;

    PT1DefaultEdit4->Text = 512;

    NT1LevelList4->ItemIndex = _NT4Default;

    NT1EnableList4->ItemIndex = _GlobalThresholdDisabled;

    NT1DefaultEdit4->Text = -513;
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SaveTab1Execute(TObject *Sender)
{
	ProfileEditForm->TempSI16Var[_NT1Default] = NT1DefaultEdit1->Text.ToIntDef(-513);
    ProfileEditForm->TempSI16Var[_PT1Default] = PT1DefaultEdit1->Text.ToIntDef(512);

    
	ProfileEditForm->TempSI16Ptr[_Threshold1Input_ptr] = PT1SourceList1->ItemIndex;
    ProfileEditForm->TempSI16Ptr[_PT1Value_ptr] = PT1LevelList1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_PT1Enabled_ptr] = PT1EnableList1->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_NT1Value_ptr] = NT1LevelList1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_NT1Enabled_ptr] = NT1EnableList1->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SaveTab2Execute(TObject *Sender)
{
	ProfileEditForm->TempSI16Var[_NT2Default] = NT1DefaultEdit2->Text.ToIntDef(-513);
    ProfileEditForm->TempSI16Var[_PT2Default] = PT1DefaultEdit2->Text.ToIntDef(512);

    
	ProfileEditForm->TempSI16Ptr[_Threshold2Input_ptr] = PT1SourceList2->ItemIndex;
    ProfileEditForm->TempSI16Ptr[_PT2Value_ptr] = PT1LevelList2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_PT2Enabled_ptr] = PT1EnableList2->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_NT2Value_ptr] = NT1LevelList2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_NT2Enabled_ptr] = NT1EnableList2->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SaveTab3Execute(TObject *Sender)
{
	ProfileEditForm->TempSI16Var[_NT3Default] = NT1DefaultEdit3->Text.ToIntDef(-513);
    ProfileEditForm->TempSI16Var[_PT3Default] = PT1DefaultEdit3->Text.ToIntDef(512);

    
	ProfileEditForm->TempSI16Ptr[_Threshold3Input_ptr] = PT1SourceList3->ItemIndex;
    ProfileEditForm->TempSI16Ptr[_PT3Value_ptr] = PT1LevelList3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_PT3Enabled_ptr] = PT1EnableList3->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_NT3Value_ptr] = NT1LevelList3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_NT3Enabled_ptr] = NT1EnableList3->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupSettingsForm::SaveTab4Execute(TObject *Sender)
{
	ProfileEditForm->TempSI16Var[_NT4Default] = NT1DefaultEdit4->Text.ToIntDef(-513);
    ProfileEditForm->TempSI16Var[_PT4Default] = PT1DefaultEdit4->Text.ToIntDef(512);

    
	ProfileEditForm->TempSI16Ptr[_Threshold4Input_ptr] = PT1SourceList4->ItemIndex;
    ProfileEditForm->TempSI16Ptr[_PT4Value_ptr] = PT1LevelList4->ItemIndex;
    ProfileEditForm->TempI8Ptr[_PT4Enabled_ptr] = PT1EnableList4->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_NT4Value_ptr] = NT1LevelList4->ItemIndex;
    ProfileEditForm->TempI8Ptr[_NT4Enabled_ptr] = NT1EnableList4->ItemIndex;
}
//---------------------------------------------------------------------------
