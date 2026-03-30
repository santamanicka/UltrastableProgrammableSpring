//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SerialThreadUnit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SerialPortThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SerialPortThread::SerialPortThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	Priority = tpHighest;
}
//---------------------------------------------------------------------------
void SerialPortThread::SetName()
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = "SerialThread1";
	info.dwThreadID = -1;
	info.dwFlags = 0;

	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}
//---------------------------------------------------------------------------
void __fastcall SerialPortThread::Execute()
{
	SetName();
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------
