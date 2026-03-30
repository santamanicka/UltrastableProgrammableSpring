
//Some temp arrays for buffering data for flash
//REMEMBER!!! int8 POINTERS are actually 16 bit values!!!!!
//Increase sizes for int16's to 48
//increase sizes for int8's to 64
int8 AcceptanceFlag = 0;
//------------------------------------------------
signed int16     FlashTemp16[32];        //64 bytes
signed int16*     FlashTemp16ptr[64];        //128 bytes
int8            FlashTemp8[32];            //32 bytes
int8*            FlashTemp8ptr[64];        //128 bytes

int8            PointerList8[64]; //64 bytes - for storing serial configuration data about the int8 pointers
int8            PointerList16[64]; //64 bytes - for storing serial configuration data about the int16 pointers

//TOTAL number of bytes for a profile when downloading = 64+128+32+128+64+64+128+64+64 = 736

signed int16 TempForceTable[64];//128 bytes
signed int8  TempPDampTable[64];//64 bytes
signed int8  TempNDampTable[64];//64 bytes
//Address Values for the start of each FLASH Profile

int16 FlashProfileStart[FLASH_PROFILES];

int8 ActuatorFlashSettings[32];
/*
How this OUGHT! to work - use write_programe_memory() starting with FT16 and writing 64 bytes
then with FT16ptr and 64 bytes
THEN call once with FT8 and 64 bytes and it should run all the way through to the end of FT8ptr.

*/

//Profiles
//signed int16     ForceTable[PROFILES][64];    //128 bytes
//signed int8     PDampTable[PROFILES][64];     //64 byte
//signed int8     NDampTable[PROFILES][64];     //64 bytes

//Pointers to conditional flags that determine if a profile switch should happen
//These are in order of priority
// - if the first is triggered then it is used, else the next is checked, then the next...
int8*     AltPro1_ptr[PROFILES];
int8*     AltPro2_ptr[PROFILES];
int8*     AltPro3_ptr[PROFILES];
int8*     AltPro4_ptr[PROFILES];

//Alternative profiles to use if a switch is triggered
int8     AltPro1[PROFILES];
int8     AltPro2[PROFILES];
int8     AltPro3[PROFILES];
int8     AltPro4[PROFILES];

//Pointers to conditional flags to determine if a profile should be incrimented or de-incrimented
int8*     IncrimentProfile_ptr[PROFILES];
int8*     DeIncrimentProfile_ptr[PROFILES];

//-------------------------------------
//THRESHOLD1
//Pointers to input variable for threshold checking - by default this will point to the global zero value
signed int16*     Threshold1Input_ptr[PROFILES];

//Pointers to thresholds values - by default these will point to their default values
signed int16*     PT1Value_ptr[PROFILES];
signed int16* NT1Value_ptr[PROFILES];

//default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
signed int16     PT1Default[PROFILES];
signed int16     NT1Default[PROFILES];

int8     PT1State[PROFILES];
int8     NT1State[PROFILES];
int8     PTAndNT1State[PROFILES];
//pointers to the enable flags for these thresholds - these point to their default (fixed) values
int8*     PT1Enabled_ptr[PROFILES];
int8*     NT1Enabled_ptr[PROFILES];

//-------------------------------------
//THRESHOLD2
//Pointers to input variable for threshold checking - by default this will point to the global zero value
signed int16*     Threshold2Input_ptr[PROFILES];

//Pointers to thresholds values - by default these will point to their default values
signed int16*     PT2Value_ptr[PROFILES];
signed int16* NT2Value_ptr[PROFILES];

//default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
signed int16     PT2Default[PROFILES];
signed int16     NT2Default[PROFILES];

int8     PT2State[PROFILES];
int8     NT2State[PROFILES];
int8     PTAndNT2State[PROFILES];
//pointers to the enable flags for these thresholds - these point to their default (fixed) values
int8*     PT2Enabled_ptr[PROFILES];
int8*     NT2Enabled_ptr[PROFILES];

//-------------------------------------
//THRESHOLD3
//Pointers to input variable for threshold checking - by default this will point to the global zero value
signed int16*     Threshold3Input_ptr[PROFILES];

//Pointers to thresholds values - by default these will point to their default values
signed int16*     PT3Value_ptr[PROFILES];
signed int16* NT3Value_ptr[PROFILES];

//default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
signed int16     PT3Default[PROFILES];
signed int16     NT3Default[PROFILES];

int8     PT3State[PROFILES];
int8     NT3State[PROFILES];
int8     PTAndNT3State[PROFILES];
//pointers to the enable flags for these thresholds - these point to their default (fixed) values
int8*     PT3Enabled_ptr[PROFILES];
int8*     NT3Enabled_ptr[PROFILES];

//-------------------------------------
//THRESHOLD4
//Pointers to input variable for threshold checking - by default this will point to the global zero value
signed int16*     Threshold4Input_ptr[PROFILES];

//Pointers to thresholds values - by default these will point to their default values
signed int16*     PT4Value_ptr[PROFILES];
signed int16* NT4Value_ptr[PROFILES];

//default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
signed int16     PT4Default[PROFILES];
signed int16     NT4Default[PROFILES];

int8     PT4State[PROFILES];
int8     NT4State[PROFILES];
int8     PTAndNT4State[PROFILES];
//pointers to the enable flags for these thresholds - these point to their default (fixed) values
int8*     PT4Enabled_ptr[PROFILES];
int8*     NT4Enabled_ptr[PROFILES];

//----------------------------------
//Global defaults for threshold enable flags
//Default enable flags for all thresholds - point to one or the other to fix a threshold on or off
int8     GlobalThresholdEnabled = 1;
int8     GlobalThresholdDisabled = 0;
//------------------------------


//pointers to variables to set the scale and bias values
signed int16* HBias_ptr[PROFILES];
signed int16* VBias_ptr[PROFILES];
signed int16* HScale_ptr[PROFILES];
signed int16* VScale_ptr[PROFILES];

//default values for Bias and scale values (horizontal and vertical)
signed int16 DefaultHBias[PROFILES];
signed int16 DefaultVBias[PROFILES];
signed int16 DefaultHScale[PROFILES];    //a fixed point multiplier
signed int16 DefaultVScale[PROFILES];    //a fixed point multiplier

//The horizontal equilibrium point around which scaling occurs
signed int16 EQAngle[PROFILES];
//The vertical equilibrium point around which scaling occurs
signed int16 VEQAngle[PROFILES];


//Pointer to the uniform damping variable
signed int16*     UniformDamping_ptr[PROFILES];
//a default value for uniform damping (A fixed point multiplier value)
signed int16     DefaultUniformDamping[PROFILES];

//Input flags for storing digital inputs (These are global values)
//each has a real and a not value which are always reversed (So you can trigger a change when an input goes low)
//also included are transition flags - if the input has gone from 0-1 in the last iteration then the flag is 1
int8 ExIn1Flag = 0;
int8 NotExIn1Flag = 1;
int8 ExIn1LowToHigh = 0;
int8 ExIn2Flag = 0;
int8 NotExIn2Flag = 1;
int8 ExIn2LowToHigh = 0;
int8 LimitIn1Flag = 0;
int8 LimitIn2Flag = 0;

//Pointers to the flag that sets the exout states - one set for each profile
int8* ExOut1_ptr[PROFILES];
int8* ExOut2_ptr[PROFILES];

//Summed flag allows you to set an ExOut from a variety of conditional triggers
//the summed flag is set high if any of the flags pointed to are high
int8 SummedFlag[PROFILES];
int8 NotSummedFlag[PROFILES];
int8* SummedFlag1_ptr[PROFILES];
int8* SummedFlag2_ptr[PROFILES];
int8* SummedFlag3_ptr[PROFILES];
int8* SummedFlag4_ptr[PROFILES];

//Pointers to variables that set the ADOut values
signed int16* ADOut1_ptr[PROFILES];
signed int16* ADOut2_ptr[PROFILES];
//Scale Values for the ADOut values
int8 ADOut1Scaling[PROFILES];
int8 ADOut2Scaling[PROFILES];
//Input variables for storing AnalogueInputs (Global)
int8 MotorFaultStatus = 0;
signed int16 MotorCurrent = 0;
signed int16 NOTMotorCurrent = 0;
signed int16 ADIn1 = 0;
signed int16 NOTADIn1 = 0;
signed int16 ADIn2 = 0;
signed int16 NOTADIn2 = 0;

signed int16 Angle = 0;
signed int16 NOTAngle = 0;
signed int16 AngleVelocity = 0;
signed int16 NOTAngleVelocity = 0;
signed int16 OldAngleVelocity = 0;
signed int16 AngleAcceleration = 0;
signed int16 NOTAngleAcceleration = 0;

//this is the angle after scaling and biasing
signed int16 ModifiedAngle = 0;
signed int16 NOTModifiedAngle = 0;

//this is the angle of the second profile during summed profile mode
signed int16 ModifiedAngle_B;
signed int16 NOTModifiedAngle_B;

//Profile start timer
signed int16 ProfileTimer = 0;
signed int16 TimerThreshold[PROFILES];
int8 NotTimerOverflowFlag = 1;
int8 TimerOverflowFlag = 0;

//randomiser variables
int8*          MutateForceFlag_ptr[PROFILES];
int8*          MutatePDampingFlag_ptr[PROFILES];
int8*          MutateNDampingFlag_ptr[PROFILES];
signed int16*  ProfileMutateBias_ptr[PROFILES];
signed int16   ProfileMutateRandomRange[PROFILES];
signed int16   ProfileMutateDefaultBias[PROFILES];
signed int16   ProfileMutateRangeScale[PROFILES]; //used to scale the random generator - so the range can be set by a variable
signed int16   ProfileMutateUpperLimit[PROFILES]; //sets the upper limit for the result of a mutation (to prevent variables going over system limits)
signed int16   ProfileMutateLowerLimit[PROFILES];
//Oscillator Variables (For each profile - another oscillator is available globally???)


//The output from the oscillator
signed int16 OSC1Out[PROFILES];
//The step size for iterating
int8 StepSize[PROFILES];
//the iterator value (the actual value that is added to the output to update it)
signed int16 Iterator[PROFILES];
//the Minimum value that it can reach
signed int16 OSC1Min[PROFILES];
//the maximum value it can reach
signed int16 OSC1Max[PROFILES];
//A prescaler to allow the iteration rate for the oscillator to be less than that of the profile
int8 SkipRate[PROFILES];

//Some extras to try out:
/*
//Amplifier component to scale variables
//the output of a multiplication system for scaling variables
signed int16 MulOut1[PROFILES];
//the default (Fixed) value to multiply by (This can be swapped for a variable)
signed int16 MulVal1[PROFILES];
//A pointer to the multiplication value (signed fixed point with two decimal places and saturation)
signed int16* MulVal1_ptr[PROFILES];
//A pointer to the input variable
signed int16* MulIn1_ptr[PROFILES];
//A saturation value to limit the final result
signed int16 MulSaturationValue1[PROFILES];

//Averager - produces the average of two inputs: Output = (Var1+Var2)/2

signed int16 AVGOut1[PROFILES];
signed int16* AVGVarAIn1_ptr[PROFILES];
signed int16* AVGVarBIn1_ptr[PROFILES];
signed int16 DefaultAVGVarIn1[PROFILES];
*/

//two global default variables 8/s16 bit for pointing to (these should always be zero valued)
static signed int16 GlobalDefaultZeroModulator = 0;
static int8 GlobalDefaultFalse = 0;
static int8 GlobalDefaultTrue = 1;
//int8 ForceInversion[PROFILES];



//These are used so you can make one profile take a variable from another profile
signed int16 GlobalVariable1[PROFILES];
signed int16* GlobalVariable1_ptr[PROFILES];
signed int16 GlobalVariable2[PROFILES];
signed int16* GlobalVariable2_ptr[PROFILES];

int8 GlobalFlag1[PROFILES];
int8* GlobalFlag1_ptr[PROFILES];
int8 GlobalFlag2[PROFILES];
int8* GlobalFlag2_ptr[PROFILES];

//if the profile is summed with its neighbor
int8 SummedProfile[PROFILES];

//Serial comm variables
int8 InBuffer[BUFFERSIZE];
int8 InBuffer2[BUFFERSIZE];
int8 NextIn = 0;
int8 NextIn2 = 0;
int8 PacketSize = 0;
int8 PacketSize2 = 0;
int8 BufferReadIndex = 0;
int8 BufferReadIndex2 = 0;
int8 BufferInOutDifference = 0;
int8 BufferInOutDifference2 = 0;
int8 DataStartIndex = 0;
int8 DataStartIndex2 = 0;
int8 Command1 = 0;
int8 Command1_2 = 0;
int8 Command2 = 0;
int8 Command2_2 = 0;
//int8 ProfileToUse;
int1 PreambleOK = 0;
int1 PreambleOK2 = 0;
int8 Preamble[5] = "PGS#";


int1 PassAlongCommands = 0;
//int8 ActuatorNode = 1; //ascii '1'
int8 RS232NodeNumber = 1;
int8 CANNodeNumber = 1;

int1 BufferOverflowError = 0;
int1 BufferOverflowError2 = 0;
int8 PacketTimeout = 0;
int8 PacketTimeout2 = 0;
int8 SerialTimerTimeout = 0;
int8 SerialTimerTimeout2 = 0;

int8 ProfileDownloadedLoadedFlags = 0;
int8 RS232FromNodeA = 0;
int8 RS232FromModeA = 0;
int8 RS232FromProfileA = 0;

int8 RS232FromNodeB = 0;
int8 RS232FromModeB = 0;
int8 RS232FromProfileB = 0;

int8 SerialTXTicksA = 0;
int8 SerialTXTicksB = 0;
//Serial Input Variables
signed int16     RS232In[8];

//Serial flag input variables
int8             RS232FlagsIn[8];


int8            RS232RequestReplyA[8];
int8            RS232RequestReplyB[8];

//Enables for serial transmission
int8*             SerialOutEnableA_ptr[PROFILES];
int8*             SerialOutEnableB_ptr[PROFILES];

//the target node for data transmissions plus a rate 
//it skips txing on each iteration until a counter reaches the rate value
int8            RS232OutTargetNodeA[PROFILES];
int8            RS232CommRateGroupA[PROFILES];

int8            RS232OutTargetNodeB[PROFILES];
int8            RS232CommRateGroupB[PROFILES];

//determines which serial port to use when auto tx-ing
int8            RS232TransmitStreamA[PROFILES];
int8            RS232TransmitStreamB[PROFILES];
//Serial Output Variables - eight variable pointers for each profile
// that can be pointed to whatever you want

signed int16* RS232Out1_ptr[PROFILES];
signed int16* RS232Out2_ptr[PROFILES];
signed int16* RS232Out3_ptr[PROFILES];
signed int16* RS232Out4_ptr[PROFILES];

signed int16* RS232Out5_ptr[PROFILES];
signed int16* RS232Out6_ptr[PROFILES];
signed int16* RS232Out7_ptr[PROFILES];
signed int16* RS232Out8_ptr[PROFILES];

//Serial output flags - one set for each profile
//These can be set to point to any system state flag
int8*         RS232FlagsOut1_ptr[PROFILES];
int8*         RS232FlagsOut2_ptr[PROFILES];
int8*         RS232FlagsOut3_ptr[PROFILES];
int8*         RS232FlagsOut4_ptr[PROFILES];
int8*         RS232FlagsOut5_ptr[PROFILES];
int8*         RS232FlagsOut6_ptr[PROFILES];
int8*         RS232FlagsOut7_ptr[PROFILES];
int8*         RS232FlagsOut8_ptr[PROFILES];

//Debug Message variables & other Santosh variables
char DebugMessage[50];
int16 DelayValue;


//CAN Bus inputs
int8 CANTXTicksA = 0;
int8 CANTXTicksB = 0;

signed int16 CANVarIn[4];
signed int16 CANFlagIn[4];

//Enable for automatic CAN transmission
int8*             CANOutEnableA_ptr[PROFILES];
int8*             CANOutEnableB_ptr[PROFILES];


int8            CANOutTargetNodeA[PROFILES];
int8            CANCommRateGroupA[PROFILES];

int8            CANOutTargetNodeB[PROFILES];
int8            CANCommRateGroupB[PROFILES];
//CAN Bus outputs
signed int16* CANVarOut1_ptr[PROFILES];
signed int16* CANVarOut2_ptr[PROFILES];
signed int16* CANVarOut3_ptr[PROFILES];
signed int16* CANVarOut4_ptr[PROFILES];

signed int8* CANFlagsOut1_ptr[PROFILES];
signed int8* CANFlagsOut2_ptr[PROFILES];
signed int8* CANFlagsOut3_ptr[PROFILES];
signed int8* CANFlagsOut4_ptr[PROFILES];
//General global variables
int8 Mode=0;
signed int16 FTarget=0;
signed int16 MeasuredForce=0;

int8* MotorEnable_ptr[PROFILES];
int8* ForceControlEnable_ptr[PROFILES];

int8 CurrentProfile=0;

int8 StartingProfile = 0;
int8 StartingMode = 0;
//a value for advancing the angle to compensate for velocity
//uses a fixed point value with 1DP (5 == 0.5)
signed int16 VelocityMultiplier = 1;

//Timer 2 variables
int16 interrupt_count=0;
int16 timer4_seconds=0;
int16 interruptsPerDelay=0;
int16 delayInterruptCnt=0;

//Profile evaluation variables
int8 evaluation_started=0;
int16 prof_success_seconds=0;
int16 evaluation_time=5;
signed int16 Angle_eval = 0;
signed int16 AngleVelocity_eval = 0;
int16 MutatedPnum = 0;
int16 RcvdMutatedPnum = 0;
char ProfRcvdAckMsg = 'N';
int8 resendcount = 0;
int8 emptyPktsSent = 0;
int8 CopyId = 0;
int8 RcvdCopyId = 0;
int16 traceIndex = 0;
//signed int16 angleTrace[50];
//signed int16 angleVelocityTrace[50];
int8 zeroFlag = 0;
int16 saveAccFlag = 0;
int8 allowActuation=0;
