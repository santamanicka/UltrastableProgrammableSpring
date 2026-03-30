

//this gets the total size of the program memory from the compiler
#define PROGRAM_MEMORY_SIZE	getenv("PROGRAM_MEMORY")

#define FLASH_DATA_SIZE		9216
#define PROFILE_DATA_SIZE	8192
#define FLASH_DATA_END		PROGRAM_MEMORY_SIZE-1
#define FLASH_DATA_START	(PROGRAM_MEMORY_SIZE - FLASH_DATA_SIZE)
#define	FLASH_PROFILE_START	(PROGRAM_MEMORY_SIZE - PROFILE_DATA_SIZE)

#org FLASH_DATA_START, FLASH_DATA_END {}


//FLASH WRITE SIZE is 64 bytes



//some defines for the sizes of the dfifferent buffers
#define INT_16_POINTER_BYTES		128
#define INT_8_POINTER_BYTES			128
#define INT_16_VARIABLE_BYTES		64
#define INT_8_VARIABLE_BYTES		32


void ProcessDownloadedActuatorPacket();
void UnpackActuaotrConfiguration();
void ProcessCompleteDownloadedProfile(int8 ProfileToUse); //Saves downloaded buffers then loads variables into RAM
void SaveAllBuffersToFlash(int8 ProfileToUse); //Saves the buffers to flash
void CopyCompleteProfileToBuffers(int8 ProfileToUse); //Copies Profiles from flash to the buffers and variables from RAM to buffers
void UnpackFlashProfileToRAM(int8 ProfileToUse);		//Copies all variables to RAM ready for operation
void CopyProfileXToProfileY(int8 From, int8 To);
void CopyActuatorSettingsToBuffers();
void UnpackSettingsBufferToRAM();
void CopyRAMProfileDataToBuffers(int8 ProfileToUse);
void ExtractDataFromRAMBuffers(int8 ProfileToUse);
void SaveActuatorSettingBuffersToFlash();
void ReadActuatorSettingsToBuffers();
void SaveProfileTablesFromBufferToFlash(int8 FlashProfile );
void SaveRAMVariablesFromBufferToFlash(int8 FlashProfile );
void ReadProfileTablesFromFlashToBuffers(int8 FlashProfile);
void ReadRAMVariablesFromFlashToBuffers(int8 FlashProfile);


void UnpackPointers16(int8 ProfileToUse);
void UnpackPointers8(int8 ProfileToUse);

void SetProfileLoadedFlag(int8 ProfileToUse);
int1 CheckProfileIsInFlash(int8 ProfileToUse);


//Some Flash and Serial config functions

void ProcessDownloadedActuatorPacket()
{
	SaveActuatorSettingBuffersToFlash();
	UnpackSettingsBufferToRAM();
}
void UnpackActuaotrConfiguration()
{
	ReadActuatorSettingsToBuffers();
	UnpackSettingsBufferToRAM();
}

void ProcessCompleteDownloadedProfile(int8 ProfileToUse)
{
	//This unpacks the pointers from the serial buffers
	//then copies all the buffered data to flash
	//then it unpacks the buffers to RAM
	UnpackPointers16(ProfileToUse);
	UnpackPointers8(ProfileToUse);
	SaveAllBuffersToFlash(ProfileToUse);
	ExtractDataFromRAMBuffers(ProfileToUse);
}

void SaveAllBuffersToFlash(int8 ProfileToUse)
{
	//contains all the functions to save a profile to FLASH from the buffer
	//This works with the temp profile buffers only - NOT with the actual profiles in RAM
	//The look up tables are only stored in flash

	SaveProfileTablesFromBufferToFlash( ProfileToUse );
	SaveRAMVariablesFromBufferToFlash( ProfileToUse );
	SetProfileLoadedFlag(ProfileToUse);
}

void CopyCompleteProfileToBuffers(int8 ProfileToUse)
{
	//copies the complete selected profile group to the buffers
	ReadProfileTablesFromFlashToBuffers( ProfileToUse );
	ReadRAMVariablesFromFlashToBuffers( ProfileToUse );

}

void UnpackFlashProfileToRAM(int8 ProfileToUse)
{
	//This unpacks all the RAM data for a profile from flash
	//Use during startup to set the system up
	ReadRAMVariablesFromFlashToBuffers( ProfileToUse );
	ExtractDataFromRAMBuffers( ProfileToUse );

}

void CopyProfileXToProfileY(int8 From, int8 To)
{
	//copies the selected profile
	//this extracts the data from FLASH into the buffers, then re-saves it to the specified FLASH Location
	//it then unpacks the RAM Buffers into the target profile RAM
	CopyCompleteProfileToBuffers(From);
	SaveAllBuffersToFlash(To);
	ExtractDataFromRAMBuffers( To );
}

void CopyActuatorSettingsToBuffers()
{
	//copies all the actuator settings to the buffers
	ActuatorFlashSettings[_RS232NodeNumber] = RS232NodeNumber;
	ActuatorFlashSettings[_CANNodeNumber] 	= CANNodeNumber;
	ActuatorFlashSettings[_StartingProfile] = StartingProfile;
	ActuatorFlashSettings[_StartingMode] 	= StartingMode;
}

void UnpackSettingsBufferToRAM()
{
	//unpacks all the actuator settings in the buffers to RAM
	RS232NodeNumber = ActuatorFlashSettings[_RS232NodeNumber];
	CANNodeNumber = ActuatorFlashSettings[_CANNodeNumber];
	StartingProfile = ActuatorFlashSettings[_StartingProfile];
	StartingMode = ActuatorFlashSettings[_StartingMode];
	
}


void CopyRAMProfileDataToBuffers(int8 ProfileToUse)
{
	//copy all the profile variables into their arrays
	//int8 Variables #############################################################
	FlashTemp8[ _AltPro1 ]			= AltPro1[ProfileToUse];
	FlashTemp8[ _AltPro2 ]			= AltPro2[ProfileToUse];
	FlashTemp8[ _AltPro3 ]			= AltPro3[ProfileToUse];
	FlashTemp8[ _AltPro4 ]			= AltPro4[ProfileToUse];

	FlashTemp8[ _ADOut1Scaling ]	= ADOut1Scaling[ProfileToUse];
	FlashTemp8[ _ADOut2Scaling ]	= ADOut2Scaling[ProfileToUse];

	FlashTemp8[ _StepSize ]			= StepSize[ProfileToUse];
	FlashTemp8[ _SkipRate ]			= SkipRate[ProfileToUse];
	FlashTemp8[ _SummedProfile ]	= SummedProfile[ProfileToUse];
	
	FlashTemp8[ _RS232OutTargetNodeA ]	= RS232OutTargetNodeA[ProfileToUse];
	FlashTemp8[ _RS232OutTargetNodeB ]	= RS232OutTargetNodeB[ProfileToUse];
	FlashTemp8[ _CANOutTargetNodeA ]	= CANOutTargetNodeA[ProfileToUse];
	FlashTemp8[ _CANOutTargetNodeB ]	= CANOutTargetNodeB[ProfileToUse];
	
	FlashTemp8[ _RS232CommRateGroupA ]	= RS232CommRateGroupA[ProfileToUse];
	FlashTemp8[ _RS232CommRateGroupB ]	= RS232CommRateGroupB[ProfileToUse];
	FlashTemp8[ _CANCommRateGroupA ]	= CANCommRateGroupA[ProfileToUse];
	FlashTemp8[ _CANCommRateGroupB ]	= CANCommRateGroupB[ProfileToUse];
	
	FlashTemp8[ _RS232RequestReplyA ]	= RS232RequestReplyA[ProfileToUse];
	FlashTemp8[ _RS232RequestReplyB ]	= RS232RequestReplyB[ProfileToUse];

	//Int8 Pointers #############################################################
	FlashTemp8ptr[ _AltPro1_ptr ]		= AltPro1_ptr[ProfileToUse];
	FlashTemp8ptr[ _AltPro2_ptr ]		= AltPro2_ptr[ProfileToUse];
	FlashTemp8ptr[ _AltPro3_ptr ]		= AltPro3_ptr[ProfileToUse];
	FlashTemp8ptr[ _AltPro4_ptr ]		= AltPro4_ptr[ProfileToUse];

	FlashTemp8ptr[ _IncrimentProfile_ptr ]		= IncrimentProfile_ptr[ProfileToUse];
	FlashTemp8ptr[ _DeIncrimentProfile_ptr ]	= DeIncrimentProfile_ptr[ProfileToUse];

	FlashTemp8ptr[ _PT1Enabled_ptr ]	= PT1Enabled_ptr[ProfileToUse];
	FlashTemp8ptr[ _NT1Enabled_ptr ]	= NT1Enabled_ptr[ProfileToUse];

	FlashTemp8ptr[ _PT2Enabled_ptr ]	= PT2Enabled_ptr[ProfileToUse];
	FlashTemp8ptr[ _NT2Enabled_ptr ]	= NT2Enabled_ptr[ProfileToUse];

	FlashTemp8ptr[ _PT3Enabled_ptr ]	= PT3Enabled_ptr[ProfileToUse];
	FlashTemp8ptr[ _NT3Enabled_ptr ]	= NT3Enabled_ptr[ProfileToUse];

	FlashTemp8ptr[ _PT4Enabled_ptr ]	= PT4Enabled_ptr[ProfileToUse];
	FlashTemp8ptr[ _NT4Enabled_ptr ]	= NT4Enabled_ptr[ProfileToUse];

	FlashTemp8ptr[ _ExOut1_ptr ]		= ExOut1_ptr[ProfileToUse];
	FlashTemp8ptr[ _ExOut2_ptr ]		= ExOut2_ptr[ProfileToUse];

	FlashTemp8ptr[ _SummedFlag1_ptr ]	= SummedFlag1_ptr[ProfileToUse];
	FlashTemp8ptr[ _SummedFlag2_ptr ]	= SummedFlag2_ptr[ProfileToUse];
	FlashTemp8ptr[ _SummedFlag3_ptr ]	= SummedFlag3_ptr[ProfileToUse];
	FlashTemp8ptr[ _SummedFlag4_ptr ]	= SummedFlag4_ptr[ProfileToUse];

	FlashTemp8ptr[ _RS232FlagsOut1_ptr ]	= RS232FlagsOut1_ptr[ProfileToUse];
	FlashTemp8ptr[ _RS232FlagsOut2_ptr ]	= RS232FlagsOut2_ptr[ProfileToUse];
	FlashTemp8ptr[ _RS232FlagsOut3_ptr ]	= RS232FlagsOut3_ptr[ProfileToUse];
	FlashTemp8ptr[ _RS232FlagsOut4_ptr ]	= RS232FlagsOut4_ptr[ProfileToUse];
	FlashTemp8ptr[ _RS232FlagsOut5_ptr ]	= RS232FlagsOut5_ptr[ProfileToUse];
	FlashTemp8ptr[ _RS232FlagsOut6_ptr ]	= RS232FlagsOut6_ptr[ProfileToUse];
	FlashTemp8ptr[ _RS232FlagsOut7_ptr ]	= RS232FlagsOut7_ptr[ProfileToUse];
	FlashTemp8ptr[ _RS232FlagsOut8_ptr ]	= RS232FlagsOut8_ptr[ProfileToUse];


	FlashTemp8ptr[ _CANFlagsOut1_ptr ] = CANFlagsOut1_ptr[ProfileToUse];
	FlashTemp8ptr[ _CANFlagsOut2_ptr ] = CANFlagsOut2_ptr[ProfileToUse];
	FlashTemp8ptr[ _CANFlagsOut3_ptr ] = CANFlagsOut3_ptr[ProfileToUse];
	FlashTemp8ptr[ _CANFlagsOut4_ptr ] = CANFlagsOut4_ptr[ProfileToUse];

	FlashTemp8ptr[ _MotorEnable_ptr ]			= MotorEnable_ptr[ProfileToUse];
	FlashTemp8ptr[ _ForceControlEnable_ptr ]	= ForceControlEnable_ptr[ProfileToUse];
	
	FlashTemp8ptr[ _SerialOutEnableA_ptr ] = SerialOutEnableA_ptr[ProfileToUse];
	FlashTemp8ptr[ _SerialOutEnableB_ptr ] = SerialOutEnableB_ptr[ProfileToUse];
	FlashTemp8ptr[ _CANOutEnableA_ptr ] = CANOutEnableA_ptr[ProfileToUse];
	FlashTemp8ptr[ _CANOutEnableB_ptr ] = CANOutEnableB_ptr[ProfileToUse];

	

	//int16 variables #############################################################
	FlashTemp16[_PT1Default] 		= PT1Default[ProfileToUse];
	FlashTemp16[_NT1Default] 		= NT1Default[ProfileToUse];
	FlashTemp16[_PT2Default] 		= PT2Default[ProfileToUse];
	FlashTemp16[_NT2Default] 		= NT2Default[ProfileToUse];
	FlashTemp16[_PT3Default] 		= PT3Default[ProfileToUse];
	FlashTemp16[_NT3Default] 		= NT3Default[ProfileToUse];
	FlashTemp16[_PT4Default] 		= PT4Default[ProfileToUse];
	FlashTemp16[_NT4Default] 		= NT4Default[ProfileToUse];
	FlashTemp16[_DefaultHBias]		= DefaultHBias[ProfileToUse];
	FlashTemp16[_DefaultVBias]		= DefaultVBias[ProfileToUse];
	FlashTemp16[_DefaultHScale] 	= DefaultHScale[ProfileToUse];
	FlashTemp16[_DefaultVScale] 	= DefaultVScale[ProfileToUse];
	FlashTemp16[_EQAngle] 			= EQAngle[ProfileToUse];
	FlashTemp16[_DefaultUniformDamping] = DefaultUniformDamping[ProfileToUse];
	FlashTemp16[_OSC1Out] 			= OSC1Out[ProfileToUse];
	FlashTemp16[_Iterator] 			= Iterator[ProfileToUse];
	FlashTemp16[_OSC1Min] 			= OSC1Min[ProfileToUse];
	FlashTemp16[_OSC1Max] 			= OSC1Max[ProfileToUse];

	//now the pointers #############################################################
	FlashTemp16ptr[ _Threshold1Input_ptr ]		= Threshold1Input_ptr[ProfileToUse];
	FlashTemp16ptr[ _Threshold2Input_ptr ]		= Threshold2Input_ptr[ProfileToUse];
	FlashTemp16ptr[ _Threshold3Input_ptr ]		= Threshold3Input_ptr[ProfileToUse];
	FlashTemp16ptr[ _Threshold4Input_ptr ]		= Threshold4Input_ptr[ProfileToUse];
	FlashTemp16ptr[ _PT1Value_ptr ]				= PT1Value_ptr[ProfileToUse];
	FlashTemp16ptr[ _NT1Value_ptr ]				= NT1Value_ptr[ProfileToUse];
	FlashTemp16ptr[ _PT2Value_ptr ]				= PT2Value_ptr[ProfileToUse];
	FlashTemp16ptr[ _NT2Value_ptr ]				= NT2Value_ptr[ProfileToUse];
	FlashTemp16ptr[ _PT3Value_ptr ]				= PT3Value_ptr[ProfileToUse];
	FlashTemp16ptr[ _NT3Value_ptr ]				= NT3Value_ptr[ProfileToUse];
	FlashTemp16ptr[ _PT4Value_ptr ]				= PT4Value_ptr[ProfileToUse];
	FlashTemp16ptr[ _NT4Value_ptr ]				= NT4Value_ptr[ProfileToUse];

	FlashTemp16ptr[ _HBias_ptr ]				= HBias_ptr[ProfileToUse];
	FlashTemp16ptr[ _VBias_ptr ]				= VBias_ptr[ProfileToUse];
	FlashTemp16ptr[ _HScale_ptr ]				= HScale_ptr[ProfileToUse];
	FlashTemp16ptr[ _VScale_ptr ]				= VScale_ptr[ProfileToUse];

	FlashTemp16ptr[ _UniformDamping_ptr ]		= UniformDamping_ptr[ProfileToUse];
	FlashTemp16ptr[ _ADOut1_ptr ]				= ADOut1_ptr[ProfileToUse];
	FlashTemp16ptr[ _ADOut2_ptr ]				= ADOut2_ptr[ProfileToUse];

	FlashTemp16ptr[ _RS232Out1_ptr ]			= RS232Out1_ptr[ProfileToUse];
	FlashTemp16ptr[ _RS232Out2_ptr ]			= RS232Out2_ptr[ProfileToUse];
	FlashTemp16ptr[ _RS232Out3_ptr ]			= RS232Out3_ptr[ProfileToUse];
	FlashTemp16ptr[ _RS232Out4_ptr ]			= RS232Out4_ptr[ProfileToUse];
	FlashTemp16ptr[ _RS232Out5_ptr ]			= RS232Out5_ptr[ProfileToUse];
	FlashTemp16ptr[ _RS232Out6_ptr ]			= RS232Out6_ptr[ProfileToUse];
	FlashTemp16ptr[ _RS232Out7_ptr ]			= RS232Out7_ptr[ProfileToUse];
	FlashTemp16ptr[ _RS232Out8_ptr ]			= RS232Out8_ptr[ProfileToUse];
	
	FlashTemp16ptr[ _CANVarOut1_ptr ]			= CANVarOut1_ptr[ProfileToUse];
	FlashTemp16ptr[ _CANVarOut2_ptr ]			= CANVarOut2_ptr[ProfileToUse];
	FlashTemp16ptr[ _CANVarOut3_ptr ]			= CANVarOut3_ptr[ProfileToUse];
	FlashTemp16ptr[ _CANVarOut4_ptr ]			= CANVarOut4_ptr[ProfileToUse];
}


//==============================================================================

void ExtractDataFromRAMBuffers(int8 ProfileToUse)
{
	//copy the array contents back to the profile variables
	//int8 Variables #############################################################
	AltPro1[ProfileToUse] = FlashTemp8[ _AltPro1 ];
	AltPro2[ProfileToUse] = FlashTemp8[ _AltPro2 ];
	AltPro3[ProfileToUse] = FlashTemp8[ _AltPro3 ];
	AltPro4[ProfileToUse] = FlashTemp8[ _AltPro4 ];

	ADOut1Scaling[ProfileToUse] = FlashTemp8[ _ADOut1Scaling ];
	ADOut2Scaling[ProfileToUse] = FlashTemp8[ _ADOut2Scaling ];

	StepSize[ProfileToUse] = FlashTemp8[ _StepSize ];
	SkipRate[ProfileToUse] = FlashTemp8[ _SkipRate ];

	SummedProfile[ProfileToUse] = FlashTemp8[ _SummedProfile ];

	RS232OutTargetNodeA[ProfileToUse] = FlashTemp8[ _RS232OutTargetNodeA ];
	RS232OutTargetNodeB[ProfileToUse] = FlashTemp8[ _RS232OutTargetNodeB ];
	CANOutTargetNodeA[ProfileToUse] = FlashTemp8[ _CANOutTargetNodeA ];
	CANOutTargetNodeB[ProfileToUse] = FlashTemp8[ _CANOutTargetNodeB ];
	
	RS232CommRateGroupA[ProfileToUse] = FlashTemp8[ _RS232CommRateGroupA ];
	RS232CommRateGroupB[ProfileToUse] = FlashTemp8[ _RS232CommRateGroupB ];
	CANCommRateGroupA[ProfileToUse] = FlashTemp8[ _CANCommRateGroupA ];
	CANCommRateGroupB[ProfileToUse] = FlashTemp8[ _CANCommRateGroupB ];
	
	RS232RequestReplyA[ProfileToUse] = FlashTemp8[ _RS232RequestReplyA ];
	RS232RequestReplyB[ProfileToUse] = FlashTemp8[ _RS232RequestReplyB ];
	
	//Int8 Pointers #############################################################
	AltPro1_ptr[ProfileToUse] = FlashTemp8ptr[ _AltPro1_ptr ];
	AltPro2_ptr[ProfileToUse] = FlashTemp8ptr[ _AltPro2_ptr ];
	AltPro3_ptr[ProfileToUse] = FlashTemp8ptr[ _AltPro3_ptr ];
	AltPro4_ptr[ProfileToUse] = FlashTemp8ptr[ _AltPro4_ptr ];

	IncrimentProfile_ptr[ProfileToUse] = FlashTemp8ptr[ _IncrimentProfile_ptr ];
	DeIncrimentProfile_ptr[ProfileToUse] = FlashTemp8ptr[ _DeIncrimentProfile_ptr ];

	PT1Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _PT1Enabled_ptr ];
	NT1Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _NT1Enabled_ptr ];

	PT2Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _PT2Enabled_ptr ];
	NT2Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _NT2Enabled_ptr ];

	PT3Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _PT3Enabled_ptr ];
	NT3Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _NT3Enabled_ptr ];

	PT4Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _PT4Enabled_ptr ];
	NT4Enabled_ptr[ProfileToUse] = FlashTemp8ptr[ _NT4Enabled_ptr ];

	ExOut1_ptr[ProfileToUse] = FlashTemp8ptr[ _ExOut1_ptr ];
	ExOut2_ptr[ProfileToUse] = FlashTemp8ptr[ _ExOut2_ptr ];

	SummedFlag1_ptr[ProfileToUse] = FlashTemp8ptr[ _SummedFlag1_ptr ];
	SummedFlag2_ptr[ProfileToUse] = FlashTemp8ptr[ _SummedFlag2_ptr ];
	SummedFlag3_ptr[ProfileToUse] = FlashTemp8ptr[ _SummedFlag3_ptr ];
	SummedFlag4_ptr[ProfileToUse] = FlashTemp8ptr[ _SummedFlag4_ptr ];

	RS232FlagsOut1_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut1_ptr ];
	RS232FlagsOut2_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut2_ptr ];
	RS232FlagsOut3_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut3_ptr ];
	RS232FlagsOut4_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut4_ptr ];
	RS232FlagsOut5_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut5_ptr ];
	RS232FlagsOut6_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut6_ptr ];
	RS232FlagsOut7_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut7_ptr ];
	RS232FlagsOut8_ptr[ProfileToUse] = FlashTemp8ptr[ _RS232FlagsOut8_ptr ];

	CANFlagsOut1_ptr[ProfileToUse] = FlashTemp8ptr[ _CANFlagsOut1_ptr ];
	CANFlagsOut2_ptr[ProfileToUse] = FlashTemp8ptr[ _CANFlagsOut2_ptr ];
	CANFlagsOut3_ptr[ProfileToUse] = FlashTemp8ptr[ _CANFlagsOut3_ptr ];
	CANFlagsOut4_ptr[ProfileToUse] = FlashTemp8ptr[ _CANFlagsOut4_ptr ];

	MotorEnable_ptr[ProfileToUse] = FlashTemp8ptr[ _MotorEnable_ptr ];
	ForceControlEnable_ptr[ProfileToUse] = FlashTemp8ptr[ _ForceControlEnable_ptr ];
	
	SerialOutEnableA_ptr[ProfileToUse] = FlashTemp8ptr[ _SerialOutEnableA_ptr ];
	SerialOutEnableB_ptr[ProfileToUse] = FlashTemp8ptr[ _SerialOutEnableB_ptr ];
	CANOutEnableA_ptr[ProfileToUse] = FlashTemp8ptr[ _CANOutEnableA_ptr ];
	CANOutEnableB_ptr[ProfileToUse] = FlashTemp8ptr[ _CANOutEnableB_ptr ];
	
	
	//int16 variables #############################################################
	PT1Default[ProfileToUse] = FlashTemp16[_PT1Default];
	NT1Default[ProfileToUse] = FlashTemp16[_NT1Default];
	PT2Default[ProfileToUse] = FlashTemp16[_PT2Default];
	NT2Default[ProfileToUse] = FlashTemp16[_NT2Default];
	PT3Default[ProfileToUse] = FlashTemp16[_PT3Default];
	NT3Default[ProfileToUse] = FlashTemp16[_NT3Default];
	PT4Default[ProfileToUse] = FlashTemp16[_PT4Default];
	NT4Default[ProfileToUse] = FlashTemp16[_NT4Default];
	DefaultHBias[ProfileToUse] = FlashTemp16[_DefaultHBias];
	DefaultVBias[ProfileToUse] = FlashTemp16[_DefaultVBias];
	DefaultHScale[ProfileToUse] = FlashTemp16[_DefaultHScale];
	DefaultVScale[ProfileToUse] = FlashTemp16[_DefaultVScale];
	EQAngle[ProfileToUse] = FlashTemp16[_EQAngle];
	DefaultUniformDamping[ProfileToUse] = FlashTemp16[_DefaultUniformDamping];
	OSC1Out[ProfileToUse] = FlashTemp16[_OSC1Out];
	Iterator[ProfileToUse] = FlashTemp16[_Iterator];
	OSC1Min[ProfileToUse] = FlashTemp16[_OSC1Min];
	OSC1Max[ProfileToUse] = FlashTemp16[_OSC1Max];

	//now the pointers #############################################################
	Threshold1Input_ptr[ProfileToUse] = FlashTemp16ptr[ _Threshold1Input_ptr ];
	Threshold2Input_ptr[ProfileToUse] = FlashTemp16ptr[ _Threshold2Input_ptr ];
	Threshold3Input_ptr[ProfileToUse] = FlashTemp16ptr[ _Threshold3Input_ptr ];
	Threshold4Input_ptr[ProfileToUse] = FlashTemp16ptr[ _Threshold4Input_ptr ];
	PT1Value_ptr[ProfileToUse] = FlashTemp16ptr[ _PT1Value_ptr ];
	NT1Value_ptr[ProfileToUse] = FlashTemp16ptr[ _NT1Value_ptr ];
	PT2Value_ptr[ProfileToUse] = FlashTemp16ptr[ _PT2Value_ptr ];
	NT2Value_ptr[ProfileToUse] = FlashTemp16ptr[ _NT2Value_ptr ];
	PT3Value_ptr[ProfileToUse] = FlashTemp16ptr[ _PT3Value_ptr ];
	NT3Value_ptr[ProfileToUse] = FlashTemp16ptr[ _NT3Value_ptr ];
	PT4Value_ptr[ProfileToUse] = FlashTemp16ptr[ _PT4Value_ptr ];
	NT4Value_ptr[ProfileToUse] = FlashTemp16ptr[ _NT4Value_ptr ];

	HBias_ptr[ProfileToUse] = FlashTemp16ptr[ _HBias_ptr ];
	VBias_ptr[ProfileToUse] = FlashTemp16ptr[ _VBias_ptr ];
	HScale_ptr[ProfileToUse] = FlashTemp16ptr[ _HScale_ptr ];
	VScale_ptr[ProfileToUse] = FlashTemp16ptr[ _VScale_ptr ];

	UniformDamping_ptr[ProfileToUse] = FlashTemp16ptr[ _UniformDamping_ptr ];
	ADOut1_ptr[ProfileToUse] = FlashTemp16ptr[ _ADOut1_ptr ];
	ADOut2_ptr[ProfileToUse] = FlashTemp16ptr[ _ADOut2_ptr ];

	RS232Out1_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out1_ptr ];
	RS232Out2_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out2_ptr ];
	RS232Out3_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out3_ptr ];
	RS232Out4_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out4_ptr ];
	RS232Out5_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out5_ptr ];
	RS232Out6_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out6_ptr ];
	RS232Out7_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out7_ptr ];
	RS232Out8_ptr[ProfileToUse] = FlashTemp16ptr[ _RS232Out8_ptr ];
	
	CANVarOut1_ptr[ProfileToUse] = FlashTemp16ptr[ _CANVarOut1_ptr ];
	CANVarOut2_ptr[ProfileToUse] = FlashTemp16ptr[ _CANVarOut2_ptr ];
	CANVarOut3_ptr[ProfileToUse] = FlashTemp16ptr[ _CANVarOut3_ptr ];
	CANVarOut4_ptr[ProfileToUse] = FlashTemp16ptr[ _CANVarOut4_ptr ];
	
	

}

//==============================================================================
void SaveActuatorSettingBuffersToFlash()
{

	write_program_memory( FLASH_DATA_START, ActuatorFlashSettings, 32 );
}

//==============================================================================
void ReadActuatorSettingsToBuffers()
{

	read_program_memory( FLASH_DATA_START, ActuatorFlashSettings, 32 );
}

//==============================================================================
void SaveProfileTablesFromBufferToFlash(int8 FlashProfile )
{
	//save the contents of the profile Array buffers to FLASH
	int16 StartAddress;
	StartAddress = FlashProfileStart[FlashProfile];

	disable_interrupts(GLOBAL);


	write_program_memory( StartAddress, &TempForceTable[0], 128 );
	StartAddress += 128;

	write_program_memory( StartAddress, &TempPDampTable[0], 64 );
	StartAddress += 64;

	write_program_memory( StartAddress, &TempNDampTable[0], 64 );

	enable_interrupts(GLOBAL);
}

//==============================================================================

void SaveRAMVariablesFromBufferToFlash(int8 FlashProfile )
{

	//save the contents of the Variable Buffers to FLASH
	int16 StartAddress;
	StartAddress = FlashProfileStart[FlashProfile];

	disable_interrupts(GLOBAL);

	StartAddress += 256;

	write_program_memory( StartAddress, FlashTemp8, INT_8_VARIABLE_BYTES );
	StartAddress += INT_8_VARIABLE_BYTES;

	//The int8 pointers use 16 bits in memory!
	write_program_memory( StartAddress, FlashTemp8ptr, INT_8_POINTER_BYTES );
	StartAddress += INT_8_POINTER_BYTES;

	write_program_memory( StartAddress, FlashTemp16, INT_16_VARIABLE_BYTES );
	StartAddress += INT_16_VARIABLE_BYTES;

	write_program_memory( StartAddress, FlashTemp16ptr, INT_16_POINTER_BYTES );
	enable_interrupts(GLOBAL);
}

//==============================================================================
void ReadProfileTablesFromFlashToBuffers(int8 FlashProfile)
{
	//Copy the selected profile arrays from flash to the buffers
	int16 StartAddress;
	StartAddress = FlashProfileStart[FlashProfile];

	disable_interrupts(GLOBAL);

	//These first three are only needed if you want to transfer the profile over serial bus or to a different profile in FLASH
	read_program_memory( StartAddress, &TempForceTable[0], 128 );
	StartAddress += 128;
	//printf("Block 5\n");

	read_program_memory( StartAddress,  &TempPDampTable[0], 64 );
	StartAddress += 64;
	//printf("Block 6\n");

	read_program_memory( StartAddress, &TempNDampTable[0], 64 );
	//printf("Block 7\n");

	enable_interrupts(GLOBAL);
}

//==============================================================================
void ReadRAMVariablesFromFlashToBuffers(int8 FlashProfile)
{
	//Copy the Variables for the selected profile from flash to the buffers
	int16 StartAddress;
	StartAddress = FlashProfileStart[FlashProfile];

	disable_interrupts(GLOBAL);

	StartAddress += 256;
	// INT_16_POINTER_BYTES		128
	// INT_8_POINTER_BYTES		128
	// INT_16_VARIABLE_BYTES	64
	// INT_8_VARIABLE_BYTES		32
	//These are the variables that need to be copied into RAM

	read_program_memory( StartAddress, FlashTemp8, INT_8_VARIABLE_BYTES );
	StartAddress += INT_8_VARIABLE_BYTES;
	//printf("Block 1\n");

	//The int8 pointers use 16 bits in memory!
	read_program_memory( StartAddress, FlashTemp8ptr, INT_8_POINTER_BYTES );
	StartAddress += INT_8_POINTER_BYTES;
	//printf("Block 2\n");

	read_program_memory( StartAddress, FlashTemp16, INT_16_VARIABLE_BYTES );
	StartAddress += INT_16_VARIABLE_BYTES;
	//printf("Block 3\n");

	read_program_memory( StartAddress, FlashTemp16ptr, INT_16_POINTER_BYTES );
	//printf("Block 4\n");
	enable_interrupts(GLOBAL);
}


//==============================================================================
void UnpackPointers16(int8 ProfileToUse)
{
	//unpacks the int16 pointers
	//int8 PointerList16[64];
	//FlashTemp16ptr[64];
	/*
	work through the list of pointers and copy them to the flash temp array
	This uses the int8 enumerated values from the serial port to decide which
	int16 variable the nth element of the temp pointer array should point to
	*/
	int8 n;

	for(n = 0; n < 64; n++)
	{
		switch(PointerList16[n])
		{
		case _PT1Default:
			FlashTemp16ptr[n] = &PT1Default[ProfileToUse];
			break;

		case _NT1Default:
			FlashTemp16ptr[n] = &NT1Default[ProfileToUse];
			break;

		case _PT2Default:
			FlashTemp16ptr[n] = &PT2Default[ProfileToUse];
			break;

		case _NT2Default:
			FlashTemp16ptr[n] = &NT2Default[ProfileToUse];
			break;

		case _PT3Default:
			FlashTemp16ptr[n] = &PT3Default[ProfileToUse];
			break;

		case _NT3Default:
			FlashTemp16ptr[n] = &NT3Default[ProfileToUse];
			break;

		case _PT4Default:
			FlashTemp16ptr[n] = &PT4Default[ProfileToUse];
			break;

		case _NT4Default:
			FlashTemp16ptr[n] = &NT4Default[ProfileToUse];
			break;

		case _DefaultHBias:
			FlashTemp16ptr[n] = &DefaultHBias[ProfileToUse];
			break;

		case _DefaultVBias:
			FlashTemp16ptr[n] = &DefaultVBias[ProfileToUse];
			break;

		case _DefaultHScale:
			FlashTemp16ptr[n] = &DefaultHScale[ProfileToUse];
			break;

		case _DefaultVScale:
			FlashTemp16ptr[n] = &DefaultVScale[ProfileToUse];
			break;

		case _EQAngle:
			FlashTemp16ptr[n] = &EQAngle[ProfileToUse];
			break;

		case _DefaultUniformDamping:
			FlashTemp16ptr[n] = &DefaultUniformDamping[ProfileToUse];
			break;

		case _OSC1Out:
			FlashTemp16ptr[n] = &OSC1Out[ProfileToUse];
			break;

		case _Iterator:
			FlashTemp16ptr[n] = &Iterator[ProfileToUse];
			break;

		case _OSC1Min:
			FlashTemp16ptr[n] = &OSC1Min[ProfileToUse];
			break;

		case _OSC1Max:
			FlashTemp16ptr[n] = &OSC1Max[ProfileToUse];
			break;

		case _RS232In1:
			FlashTemp16ptr[n] = &RS232In[0];
			break;

		case _RS232In2:
			FlashTemp16ptr[n] = &RS232In[1];
			break;

		case _RS232In3:
			FlashTemp16ptr[n] = &RS232In[2];
			break;

		case _RS232In4:
			FlashTemp16ptr[n] = &RS232In[3];
			break;

		case _RS232In5:
			FlashTemp16ptr[n] = &RS232In[4];
			break;

		case _RS232In6:
			FlashTemp16ptr[n] = &RS232In[5];
			break;

		case _RS232In7:
			FlashTemp16ptr[n] = &RS232In[6];
			break;

		case _RS232In8:
			FlashTemp16ptr[n] = &RS232In[7];
			break;

		case _CANVarIn1:
			FlashTemp16ptr[n] = &CANVarIn[0];
			break;

		case _CANVarIn2:
			FlashTemp16ptr[n] = &CANVarIn[1];
			break;

		case _CANVarIn3:
			FlashTemp16ptr[n] = &CANVarIn[2];
			break;

		case _CANVarIn4:
			FlashTemp16ptr[n] = &CANVarIn[3];
			break;
			
			
		case _GlobalVariable1_0:
			FlashTemp16ptr[n] = &GlobalVariable1[0];
			break;
		case _GlobalVariable1_1:
			FlashTemp16ptr[n] = &GlobalVariable1[1];
			break;
		case _GlobalVariable1_2:
			FlashTemp16ptr[n] = &GlobalVariable1[2];
			break;
		case _GlobalVariable1_3:
			FlashTemp16ptr[n] = &GlobalVariable1[3];
			break;
		case _GlobalVariable1_4:
			FlashTemp16ptr[n] = &GlobalVariable1[4];
			break;
		case _GlobalVariable1_5:
			FlashTemp16ptr[n] = &GlobalVariable1[5];
			break;
		case _GlobalVariable1_6:
			FlashTemp16ptr[n] = &GlobalVariable1[6];
			break;
		case _GlobalVariable1_7:
			FlashTemp16ptr[n] = &GlobalVariable1[7];
			break;
		
		
		case _GlobalVariable2_0:
			FlashTemp16ptr[n] = &GlobalVariable2[0];
			break;
		case _GlobalVariable2_1:
			FlashTemp16ptr[n] = &GlobalVariable2[1];
			break;
		case _GlobalVariable2_2:
			FlashTemp16ptr[n] = &GlobalVariable2[2];
			break;
		case _GlobalVariable2_3:
			FlashTemp16ptr[n] = &GlobalVariable2[3];
			break;
		case _GlobalVariable2_4:
			FlashTemp16ptr[n] = &GlobalVariable2[4];
			break;
		case _GlobalVariable2_5:
			FlashTemp16ptr[n] = &GlobalVariable2[5];
			break;
		case _GlobalVariable2_6:
			FlashTemp16ptr[n] = &GlobalVariable2[6];
			break;
		case _GlobalVariable2_7:
			FlashTemp16ptr[n] = &GlobalVariable2[7];
			break;
			
			
		case _Angle:
			FlashTemp16ptr[n] = &Angle;
			break;
		
		case _NOTAngle:
			FlashTemp16ptr[n] = &NOTAngle;
			break;
			
		case _ModifiedAngle:
			//need to check to see if the profile summation is enabled
			if(FlashTemp8[ _SummedProfile ] == 1 && (ProfileToUse & 0b00000001) == 1)
			{
					//Odd number
					FlashTemp16ptr[n] = &ModifiedAngle_B;
			}
			else FlashTemp16ptr[n] = &ModifiedAngle;
			break;
		
		case _NOTModifiedAngle:
			//need to check to see if the profile summation is enabled
			if(FlashTemp8[ _SummedProfile ] == 1 && (ProfileToUse & 0b00000001) == 1)
			{
					//Odd number
					FlashTemp16ptr[n] = &NOTModifiedAngle_B;
			}
			else FlashTemp16ptr[n] = &NOTModifiedAngle;
			break;

		case _AngleVelocity:
			FlashTemp16ptr[n] = &AngleVelocity;
			break;
			
		case _NOTAngleVelocity:
			FlashTemp16ptr[n] = &NOTAngleVelocity;
			break;

		case _AngleAcceleration:
			FlashTemp16ptr[n] = &AngleAcceleration;
			break;

		case _NOTAngleAcceleration:
			FlashTemp16ptr[n] = &NOTAngleAcceleration;
			break;
			
		case _FTarget:
			FlashTemp16ptr[n] = &FTarget;
			break;
			
		case _MeasuredForce:
			FlashTemp16ptr[n] = &MeasuredForce;
			break;

		case _ADIn1:
			FlashTemp16ptr[n] = &ADIn1;
			break;

		case _NOTADIn1:
			FlashTemp16ptr[n] = &NOTADIn1;
			break;

		case _ADIn2:
			FlashTemp16ptr[n] = &ADIn2;
			break;

		case _NOTADIn2:
			FlashTemp16ptr[n] = &NOTADIn2;
			break;

		case _GlobalDefaultZeroModulator:
			FlashTemp16ptr[n] = &GlobalDefaultZeroModulator;
			break;

		default:
			FlashTemp16ptr[n] = &GlobalDefaultZeroModulator;
		}
	}

}

//==============================================================================
void UnpackPointers8(int8 ProfileToUse)
{

	//unpacks the int8 pointers
	//int8 PointerList8[64];
	//FlashTemp8ptr[64];

	//work through the list of pointers and copy them to the flash temp array

	int8 n;

	for(n = 0; n < 64; n++)
	{
		switch(PointerList8[n])
		{
		case _AltPro1:
			FlashTemp8ptr[n] = &AltPro1[ProfileToUse];
			break;

		case _AltPro2:
			FlashTemp8ptr[n] = &AltPro2[ProfileToUse];
			break;

		case _AltPro3:
			FlashTemp8ptr[n] = &AltPro3[ProfileToUse];
			break;

		case _AltPro4:
			FlashTemp8ptr[n] = &AltPro4[ProfileToUse];
			break;

		

		case _ADOut1Scaling:
			FlashTemp8ptr[n] = &ADOut1Scaling[ProfileToUse];
			break;

		case _ADOut2Scaling:
			FlashTemp8ptr[n] = &ADOut2Scaling[ProfileToUse];
			break;

		case _StepSize:
			FlashTemp8ptr[n] = &StepSize[ProfileToUse];
			break;

		case _SkipRate:
			FlashTemp8ptr[n] = &SkipRate[ProfileToUse];
			break;

		case _SummedProfile:
			FlashTemp8ptr[n] = &SummedProfile[ProfileToUse];
			break;
			
			
			

		case _RS232OutTargetNodeA:
			FlashTemp8ptr[n] = &RS232OutTargetNodeA[ProfileToUse];
			break;
			
		case _RS232OutTargetNodeB:
			FlashTemp8ptr[n] = &RS232OutTargetNodeB[ProfileToUse];
			break;	
			
		case _CANOutTargetNodeA:
			FlashTemp8ptr[n] = &CANOutTargetNodeA[ProfileToUse];
			break;
			
		case _CANOutTargetNodeB:
			FlashTemp8ptr[n] = &CANOutTargetNodeB[ProfileToUse];
			break;
			
			
		case _RS232CommRateGroupA:
			FlashTemp8ptr[n] = &RS232CommRateGroupA[ProfileToUse];
			break;
			
		case _RS232CommRateGroupB:
			FlashTemp8ptr[n] = &RS232CommRateGroupB[ProfileToUse];
			break;	
			
		case _CANCommRateGroupA:
			FlashTemp8ptr[n] = &CANCommRateGroupA[ProfileToUse];
			break;
			
		case _CANCommRateGroupB:
			FlashTemp8ptr[n] = &CANCommRateGroupB[ProfileToUse];
			break;


		
		case _RS232FlagsIn1:
			FlashTemp8ptr[n] = &RS232FlagsIn[0];
			break;

		case _RS232FlagsIn2:
			FlashTemp8ptr[n] = &RS232FlagsIn[1];
			break;

		case _RS232FlagsIn3:
			FlashTemp8ptr[n] = &RS232FlagsIn[2];
			break;

		case _RS232FlagsIn4:
			FlashTemp8ptr[n] = &RS232FlagsIn[3];
			break;

		case _RS232FlagsIn5:
			FlashTemp8ptr[n] = &RS232FlagsIn[4];
			break;

		case _RS232FlagsIn6:
			FlashTemp8ptr[n] = &RS232FlagsIn[5];
			break;

		case _RS232FlagsIn7:
			FlashTemp8ptr[n] = &RS232FlagsIn[6];
			break;

		case _RS232FlagsIn8:
			FlashTemp8ptr[n] = &RS232FlagsIn[7];
			break;
			
			
			
		case _CANFlagIn1:
			FlashTemp8ptr[n] = &CANFlagIn[0];
			break;
			
		case _CANFlagIn2:
			FlashTemp8ptr[n] = &CANFlagIn[1];
			break;
			
		case _CANFlagIn3:
			FlashTemp8ptr[n] = &CANFlagIn[2];
			break;
			
		case _CANFlagIn4:
			FlashTemp8ptr[n] = &CANFlagIn[3];
			break;
			
	
	
		case _GlobalFlag1_0:
			FlashTemp8ptr[n] = &GlobalFlag1[0];
			break;
			
		case _GlobalFlag1_1:
			FlashTemp8ptr[n] = &GlobalFlag1[1];
			break;
			
		case _GlobalFlag1_2:
			FlashTemp8ptr[n] = &GlobalFlag1[2];
			break;
			
		case _GlobalFlag1_3:
			FlashTemp8ptr[n] = &GlobalFlag1[3];
			break;
		
		case _GlobalFlag1_4:
			FlashTemp8ptr[n] = &GlobalFlag1[4];
			break;
			
		case _GlobalFlag1_5:
			FlashTemp8ptr[n] = &GlobalFlag1[5];
			break;
			
		case _GlobalFlag1_6:
			FlashTemp8ptr[n] = &GlobalFlag1[6];
			break;
			
		case _GlobalFlag1_7:
			FlashTemp8ptr[n] = &GlobalFlag1[7];
			break;
			
		case _GlobalFlag2_0:
			FlashTemp8ptr[n] = &GlobalFlag2[0];
			break;
			
		case _GlobalFlag2_1:
			FlashTemp8ptr[n] = &GlobalFlag2[1];
			break;
			
		case _GlobalFlag2_2:
			FlashTemp8ptr[n] = &GlobalFlag2[2];
			break;
			
		case _GlobalFlag2_3:
			FlashTemp8ptr[n] = &GlobalFlag2[3];
			break;
		
		case _GlobalFlag2_4:
			FlashTemp8ptr[n] = &GlobalFlag2[4];
			break;
			
		case _GlobalFlag2_5:
			FlashTemp8ptr[n] = &GlobalFlag2[5];
			break;
			
		case _GlobalFlag2_6:
			FlashTemp8ptr[n] = &GlobalFlag2[6];
			break;
			
		case _GlobalFlag2_7:
			FlashTemp8ptr[n] = &GlobalFlag2[7];
			break;
			
			
			
			

		case _PT1State:
			FlashTemp8ptr[n] = &PT1State[ProfileToUse];
			break;

		case _NT1State:
			FlashTemp8ptr[n] = &NT1State[ProfileToUse];
			break;
			
		case _PTAndNT1State:
			FlashTemp8ptr[n] = &PTAndNT1State[ProfileToUse];
			break;
			

		case _PT2State:
			FlashTemp8ptr[n] = &PT2State[ProfileToUse];
			break;

		case _NT2State:
			FlashTemp8ptr[n] = &NT2State[ProfileToUse];
			break;
			
		case _PTAndNT2State:
			FlashTemp8ptr[n] = &PTAndNT2State[ProfileToUse];
			break;
			

		case _PT3State:
			FlashTemp8ptr[n] = &PT3State[ProfileToUse];
			break;

		case _NT3State:
			FlashTemp8ptr[n] = &NT3State[ProfileToUse];
			break;
			
		case _PTAndNT3State:
			FlashTemp8ptr[n] = &PTAndNT3State[ProfileToUse];
			break;
			

		case _PT4State:
			FlashTemp8ptr[n] = &PT4State[ProfileToUse];
			break;

		case _NT4State:
			FlashTemp8ptr[n] = &NT4State[ProfileToUse];
			break;
			
		case _PTAndNT4State:
			FlashTemp8ptr[n] = &PTAndNT4State[ProfileToUse];
			break;
			

		case _SummedFlag:
			FlashTemp8ptr[n] = &SummedFlag[ProfileToUse];
			break;
		
		case _NOTSummedFlag:
			FlashTemp8ptr[n] = &NOTSummedFlag[ProfileToUse];
			break;
			
		case _GlobalThresholdEnabled:
			FlashTemp8ptr[n] = &GlobalThresholdEnabled;
			break;

		case _GlobalThresholdDisabled:
			FlashTemp8ptr[n] = &GlobalThresholdDisabled;
			break;

		case _ExIn1Flag:
			FlashTemp8ptr[n] = &ExIn1Flag;
			break;

		case _NotExIn1Flag:
			FlashTemp8ptr[n] = &NotExIn1Flag;
			break;

		case _ExIn2Flag:
			FlashTemp8ptr[n] = &ExIn2Flag;
			break;

		case _NotExIn2Flag:
			FlashTemp8ptr[n] = &NotExIn2Flag;
			break;

		case _LimitIn1Flag:
			FlashTemp8ptr[n] = &LimitIn1Flag;
			break;

		case _LimitIn2Flag:
			FlashTemp8ptr[n] = &LimitIn2Flag;
			break;

		case _GlobalDefaultFalse:
			FlashTemp8ptr[n] = &GlobalDefaultFalse;
			break;
			
		case _GlobalDefaultTrue:
			FlashTemp8ptr[n] = &GlobalDefaultTrue;
			break;
			
			
		default:
			FlashTemp8ptr[n] = &GlobalDefaultFalse;
		}
	}

}

void SetProfileLoadedFlag(int8 ProfileToUse)
{
	//sets the final two bytes in the flash area to confirm that the profile is in memory
	write_program_eeprom((FlashProfileStart[ProfileToUse]+1022), 1024);
	
}
int1 CheckProfileIsInFlash(int8 ProfileToUse)
{
	//checks to see if the profile is in flash
	int16 Val = 0;
	Val = read_program_eeprom(FlashProfileStart[ProfileToUse]+1022);
	if(Val == 1024) return 1;
	return 0;
	
}
