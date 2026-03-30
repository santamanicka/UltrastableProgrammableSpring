
 //a copy of all the defines from the microcontroller
 //these are a list of the various variables in the system
#define NUMBER_OF_PROFILE_GROUPS   8
#define TIMERSATURATION 32000
 
//===========================================================================


//===========================================================================
//int8 ptr --------------------------------------------------------------
//Defined values represent the position of the variable in an array
//Setting an int8 ptr, eg _AltPro1_ptr to '60' tells the system that _AltPro1_ptr should 'point to' the vazriable _PT1State
//The actuator will then evaluate _PT1State when checking to see if it should switch profiles.
//There are 64 variables available

//Pointers to conditionals to evaluate for a profile switch
#define    _AltPro1_ptr            0
#define    _AltPro2_ptr            1
#define    _AltPro3_ptr            2
#define    _AltPro4_ptr            3
//Pointers to conditional flags to determine if a profile should be incrimented or de-incrimented

#define    _IncrimentProfile_ptr   4
#define    _DeIncrimentProfile_ptr   5

//Thresholds
//pointers to the enable flags for these thresholds - these point to their default (fixed) values
#define    _PT1Enabled_ptr         6
#define    _NT1Enabled_ptr         7

#define    _PT2Enabled_ptr         8
#define    _NT2Enabled_ptr         9

#define    _PT3Enabled_ptr         10
#define    _NT3Enabled_ptr         11

#define    _PT4Enabled_ptr         12
#define    _NT4Enabled_ptr         13

//Pointers to the flag that sets the exout states - one set for each profile
#define    _ExOut1_ptr            14
#define    _ExOut2_ptr            15

//Summed flag allows you to set an ExOut from a variety of conditional triggers
//the summed flag is set high if any of the flags pointed to are high
#define    _SummedFlag1_ptr         16
#define    _SummedFlag2_ptr         17
#define    _SummedFlag3_ptr         18
#define    _SummedFlag4_ptr         19

#define    _RS232FlagsOut1_ptr         20
#define    _RS232FlagsOut2_ptr         21
#define    _RS232FlagsOut3_ptr         22
#define    _RS232FlagsOut4_ptr         23
#define    _RS232FlagsOut5_ptr         24
#define    _RS232FlagsOut6_ptr         25
#define    _RS232FlagsOut7_ptr         26
#define    _RS232FlagsOut8_ptr         27

#define      _CANFlagsOut1_ptr         28
#define      _CANFlagsOut2_ptr         29
#define      _CANFlagsOut3_ptr         30
#define      _CANFlagsOut4_ptr         31

#define      _MotorEnable_ptr         32
#define      _ForceControlEnable_ptr      33

//Pointers to enables for transmitting serial packets
#define    _SerialOutEnableA_ptr      34
#define    _SerialOutEnableB_ptr      35

#define      _CANOutEnableA_ptr         36 
#define      _CANOutEnableB_ptr         37

#define      _GlobalFlag1_ptr         38
#define      _GlobalFlag2_ptr         39

//pointer to the flags that determine if a profie is to be mutated and which part (Force, damping or both)
#define     _MutateForceFlag_ptr    40
#define     _MutatePDampingFlag_ptr   41
#define     _MutateNDampingFlag_ptr    42

//===========================================================================
//int8 Var --------------------------------------------------------------
//Defined values represent the position of the variable in an array
//setting an int8 var, eg AltPro4, to 3 sets the value of AltPro4 to 3.
//There are 32 variables available

//Alternative profiles to use if a switch is triggered
#define    _AltPro1            0
#define    _AltPro2            1
#define    _AltPro3            2
#define    _AltPro4            3

//Scale Values for the ADOut values
#define    _ADOut1Scaling         4
#define    _ADOut2Scaling         5

//Oscillator step size for iterating
#define    _StepSize            6

//A prescaler to allow the iteration rate for the oscillator to be less than that of the profile
#define    _SkipRate            7

//If this is true then the profile is summed with its neighbor
#define      _SummedProfile         8
//These are actuator node numbers for transmitting data - each profile group can transmit
//to two different nodes using tx group A or B
#define      _RS232OutTargetNodeA   9
#define      _RS232OutTargetNodeB   10

#define      _CANOutTargetNodeA      11
#define      _CANOutTargetNodeB      12

#define      _RS232CommRateGroupA      13                             
#define      _RS232CommRateGroupB   14
#define      _CANCommRateGroupA      15
#define      _CANCommRateGroupB      16

//Determines if a node will request a reply on transmission
#define      _RS232RequestReplyA      17
#define      _RS232RequestReplyB      18

//int8 variables that determine which port the A or B packet will transmit from
//0 = PRIMARY_STREAM, 1 = SECONDARY_STREAM
//This only applies when autosending data
//if the transmittion is in reply to a request then it will tx on the port it received from
#define     _RS232TransmitStreamA   19
#define     _RS232TransmitStreamB   20

#define     _AnalyzePolygonSide     21
#define     _AnalyzeTVZfactor       22
#define     _AnalyzeViabilityAngle  23
#define     _AnalyzeEvalTime        24
#define     _AnalyzeViabilityVelocity 25
#define     _AnalyzeMutationRange   26
#define     _AnalyzeDampingMutation 27
#define     _AnalyzeSamples         28

/* These are reserved for development -
they are all within the range of variables that can be downloaded into the buffer (i.e less than 32)

NOT IN USE                     29
NOT IN USE                     30
NOT IN USE                     31
*/
//All the following are run time variables-  not user settable
#define      _RS232FlagsIn1         32
#define      _RS232FlagsIn2         33
#define      _RS232FlagsIn3         34
#define      _RS232FlagsIn4         35
#define      _RS232FlagsIn5         36
#define      _RS232FlagsIn6         37
#define      _RS232FlagsIn7         38
#define      _RS232FlagsIn8         39

#define      _CANFlagIn1            40
#define      _CANFlagIn2            41
#define      _CANFlagIn3            42
#define      _CANFlagIn4            43


#define      _GlobalFlag1_0         44
#define      _GlobalFlag1_1         45
#define      _GlobalFlag1_2         46
#define      _GlobalFlag1_3         47
#define      _GlobalFlag1_4         48
#define      _GlobalFlag1_5         49
#define      _GlobalFlag1_6         50
#define      _GlobalFlag1_7         51

#define      _GlobalFlag2_0         52
#define      _GlobalFlag2_1         53
#define      _GlobalFlag2_2         54
#define      _GlobalFlag2_3         55
#define      _GlobalFlag2_4         56
#define      _GlobalFlag2_5         57
#define      _GlobalFlag2_6         58
#define      _GlobalFlag2_7         59
//Internal state variables - these cannot be directly set by the user
//Thresholds
//Output States of the thresholds (Active non zero)
#define    _PT1State            60
#define    _NT1State            61
#define      _PTAndNT1State         62

#define    _PT2State            63
#define    _NT2State            64
#define      _PTAndNT2State         65

#define    _PT3State            66
#define    _NT3State            67
#define      _PTAndNT3State         68

#define    _PT4State            69
#define    _NT4State            70
#define      _PTAndNT4State         71

//Summed flag allows you to set an ExOut from a variety of conditional triggers
//the summed flag is set high if any of the flags pointed to are high
#define    _SummedFlag            72
#define    _NotSummedFlag            73

#define      _GlobalThresholdEnabled      74 // always 1
#define      _GlobalThresholdDisabled   75 // always 0

#define      _ExIn1Flag               76                   
#define      _NotExIn1Flag            77
#define      _ExIn1LowToHigh          78
#define      _ExIn2Flag               79                   
#define      _NotExIn2Flag            80 
#define      _ExIn2LowToHigh          81


#define        _NotTimerOverflowFlag         82
#define        _TimerOverflowFlag            83

#define        _GlobalDefaultFalse            84 // always 0
#define        _GlobalDefaultTrue            85 // always 1
//===========================================================================
//SInt16 Ptr ------------------------------------------------------------
//There are 64 variables available
//Thresholds
//Threshold input variable pointer
#define    _Threshold1Input_ptr      0
#define    _Threshold2Input_ptr      1
#define    _Threshold3Input_ptr      2
#define    _Threshold4Input_ptr      3

//Pointers to thresholds values - by default these will point to their default values
#define    _PT1Value_ptr         4
#define    _NT1Value_ptr         5

#define    _PT2Value_ptr         6
#define    _NT2Value_ptr         7

#define    _PT3Value_ptr         8
#define    _NT3Value_ptr         9

#define    _PT4Value_ptr         10
#define    _NT4Value_ptr         11

//pointers to variables to set the scale and bias values
#define    _HBias_ptr            12
#define    _VBias_ptr            13
#define    _HScale_ptr            14
#define    _VScale_ptr            15

//Pointer to the uniform damping variable
#define    _UniformDamping_ptr      16

//Pointers to variables that set the ADOut values
#define    _ADOut1_ptr            17
#define    _ADOut2_ptr            18

//serial IO pointers

#define    _RS232Out1_ptr         19
#define    _RS232Out2_ptr         20
#define    _RS232Out3_ptr         21
#define    _RS232Out4_ptr         22
#define    _RS232Out5_ptr         23
#define    _RS232Out6_ptr         24
#define    _RS232Out7_ptr         25
#define    _RS232Out8_ptr         26

#define      _CANVarOut1_ptr          27
#define      _CANVarOut2_ptr         28
#define      _CANVarOut3_ptr         29
#define      _CANVarOut4_ptr         30

#define      _GlobalVariable1_ptr   31
#define      _GlobalVariable2_ptr   32

#define      _ProfileMutateBias_ptr 33
//#define      _OscModulatingInput1   27

//===========================================================================
//SInt16 Var ------------------------------------------------------------
//There are 32 variables available
//default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
#define    _PT1Default               0
#define    _NT1Default               1

#define    _PT2Default               2
#define    _NT2Default               3

#define    _PT3Default               4
#define    _NT3Default               5

#define    _PT4Default               6
#define    _NT4Default               7

//default values for Bias and scale values (horizontal and vertical)
#define    _DefaultHBias            8
#define    _DefaultVBias            9
#define    _DefaultHScale            10   //a fixed point multiplier
#define    _DefaultVScale            11   //a fixed point multiplier

//The horizontal equilibrium point around which scaling occurs
#define    _EQAngle               12

//a default value for uniform damping (A fixed point multiplier value)
#define    _DefaultUniformDamping      13

//The output from the oscillator
#define    _OSC1Out               14

//the iterator value for the oscillator (the actual value that is added to the output to update it)
#define    _Iterator               15
//the Minimum value that it can reach
#define    _OSC1Min               16
//the maximum value it can reach
#define    _OSC1Max               17

#define     _TimerThreshold            18

//These determine how a profile is altered by the mutate function
//the range sets the upper and lower limit for the random variable
//the bias is added to this before being added to the profile value
//the bias can be used with a zero range to shift all values up and down by the same amount
//the bias can also be mapped to another variable (EG a serial input)
#define     _ProfileMutateRandomRange  19
#define     _ProfileMutateDefaultBias  20
#define     _ProfileMutateRangeScale  21 //used to scale the random generator - so the range can be set by a variable
#define     _ProfileMutateUpperLimit   22 //sets the upper limit for the result of a mutation (to prevent variables going over system limits)
#define     _ProfileMutateLowerLimit   23 //sets the upper limit for the result of a mutation (to prevent variables going over system limits)

#define     _AnalyzeTVZdropBy     24

/*
NOT IN USE                        25
NOT IN USE                        26
NOT IN USE                        27
NOT IN USE                        28
NOT IN USE                        29
NOT IN USE                        30
NOT IN USE                        31
*/
//All of the following are set during run time
//rather than by the user during configuration
//Serial Inputs
#define      _RS232In1               32
#define      _RS232In2               33
#define      _RS232In3               34
#define      _RS232In4               35
#define      _RS232In5               36
#define      _RS232In6               37
#define      _RS232In7               38
#define      _RS232In8               39

#define      _CANVarIn1                40
#define      _CANVarIn2               41
#define      _CANVarIn3               42
#define      _CANVarIn4               43


#define    _GlobalVariable1_0         44 //Variable from profile 0
#define    _GlobalVariable1_1         45 
#define    _GlobalVariable1_2         46 
#define    _GlobalVariable1_3         47 
#define    _GlobalVariable1_4         48 
#define    _GlobalVariable1_5         49 
#define    _GlobalVariable1_6         50 
#define    _GlobalVariable1_7         51 

#define    _GlobalVariable2_0         52
#define    _GlobalVariable2_1         53
#define    _GlobalVariable2_2         54
#define    _GlobalVariable2_3         55
#define    _GlobalVariable2_4         56
#define    _GlobalVariable2_5         57
#define    _GlobalVariable2_6         58
#define    _GlobalVariable2_7         59


//The main system variables

#define      _Angle                  60
#define      _NOTAngle               61                  
#define    _ModifiedAngle            62
#define    _NOTModifiedAngle         63
#define      _AngleVelocity            64
#define      _NOTAngleVelocity         65
#define      _AngleAcceleration         66
#define    _NOTAngleAcceleration      67
#define      _FTarget               68
#define      _MeasuredForce            69
#define      _ADIn1                  70
#define      _NOTADIn1               71
#define      _ADIn2                  72
#define      _NOTADIn2               73
#define     _ProfileTimer               74
#define     _MotorCurrent              75
#define     _NOTMotorCurrent           76
#define     _GlobalDefaultZeroModulator 77


//------------------------

//Actuator Settings

#define      _RS232NodeNumber         0
#define      _CANNodeNumber            1 
#define      _StartingProfile         2
#define      _StartingMode            3


