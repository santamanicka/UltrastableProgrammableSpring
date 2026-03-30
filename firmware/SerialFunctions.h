//#include "D:\PIC_C_Projects\PROGRAMMABLE SPRING\NewAngleControl\ProfileFunctions.h"

int8 ParseSerialBuffer();
int8 ProcessPacket();
int1 FilterPacket();
int8 ProcessProfilePacket(int8 BufferStartIndex);
int8 ProcessControlPacket(int8 BufferStartIndex);

void SendRS232Preamble();

void SendErrorMessage(int8 ErrorNo);
void SendConfirmMessage(int8 MsgNo, int8 ProfileNo);

signed int16 ConvertToSInt16(int16 Value);
int16 ConvertToUInt16(signed int16 Value);

void RS232TransmitBlockA();
void RS232AutoReplyBlockA();
void RS232TransmitBlockB();
void RS232AutoReplyBlockB();

void PrintProfile(int8 ProfileToUse);

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int8 ParseSerialBuffer()
{
	//work your way through the serial buffer until you reach the most rescent byte
	//if you have a complete profile config packet then execute the processprofilepacket function
	//otherwise just return
	
	int8 IsOK = 0;
	//use BufferInOutDifference to count up when bytes come in and back down again when the buffer is read
	//if this is zero then there are no new bytes to process
	if(BufferInOutDifference == 0)
	{
		if(BufferReadIndex != NextIn)
		{
			BufferReadIndex = NextIn;
			#IFDEF PARSER_DEBUG
			printf("\nIndexing Error in parser - IO Diff is 0 but ReadIndex is not at NextIn\n");
			printf("ReadIndex = %u NextIn = %u\n", BufferReadIndex, NextIn);
			#ENDIF
		}
		return 0;

	}

	//if the filter has been passed then decide what to do with the packet
	if(PreambleOK == 1)
	{
		#IFDEF PARSER_DEBUG
		printf("\nSending to packet processor\n");
		#ENDIF
		 IsOK = ProcessPacket();
		 if(IsOK == 2 || IsOK == 0)
		 {
		 	PreambleOK = 0; //reset the packet filter if data complete or error detected
		 	PacketTimeout = 0; //reset the timer
		 }
	}
	//if isok > 1 then an error occurred so reset the whole thing
	//if IsOK == 1 then the packet is still being recieved
	//if IsOK == 0 then the whole packet has been recieved and processed so reset the whole thing and do something with the data

	//if preamble not passed  or has been reset then pass to the packet filter
	if(BufferInOutDifference != 0 && PreambleOK == 0)
	{
		#IFDEF PARSER_DEBUG
		printf("\nApplying to Packet Filter\n");
		#ENDIF
		PreambleOK = FilterPacket();
		IsOK = PreambleOK;
		if(PreambleOK == 1) enable_interrupts(int_timer1);//set the timer going

	}

	//this returns
	return IsOK;

}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int8 ProcessPacket()
{
	int8 isok = 0;
	//this processes the packet once the preamble and commands have been accepted
	//you are recieving a data packet so process it according to the command

	//first check the number of bytes waiting to be processed against the packet size
	//if there are still bytes due in then do nothing

	#IFDEF PACKET_PROCESSOR_DEBUG
	printf("\nIn packet processor function\nIO Diff = %u\n",BufferInOutDifference);
	#ENDIF
	if(BufferInOutDifference < PacketSize)
	{

		isok = 1;
		PacketTimeout++;
		if(PacketTimeout > 128||SerialTimerTimeout == 1)
		{
			isok = 0;
			SerialTimerTimeout = 0;
			set_timer1(0);
			#IFDEF PACKET_PROCESSOR_DEBUG
			printf("\nPacket Timeout\n");
			#ENDIF
			disable_interrupts(int_timer1);
		//if you have been here to many times or the timer has overflowed then the packet times out and resets
		//printf("\nBufferIO Diff < PacketSize\n");
		}
	}

	else if(Command1 > 64 && Command1 < 91) // Command1 is a capital letter
	{
		set_timer1(0);
		disable_interrupts(int_timer1);
		//this is a control packet
		#IFDEF PACKET_PROCESSOR_DEBUG
		printf("\nControl packet recieved\n");
		#ENDIF
		isok = ProcessControlPacket(DataStartIndex);
	}
	else if(Command1 > 47 && Command1 < 58) //Command1 is between '0' and '9'
	{
		set_timer1(0);
		disable_interrupts(int_timer1);

		//this is a profile config packet so send to the handler
		#IFDEF PACKET_PROCESSOR_DEBUG
		printf("\nProfile packet recieved\n");
		#ENDIF
		isok = ProcessProfilePacket(DataStartIndex);
	}

	return isok;

	//if you are recieving a profile config packet then pass to the handler function which will return if it is not complete

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
int1 FilterPacket()
{
	//this works through the buffer and returns when it runs out of bytes or when it
	//succeeds in filtering the preamble
	int1 packetAccepted = 0;
	int8 CurrentByte;
	static int8 AcceptanceFlag = 0;

	while(BufferInOutDifference > 0)
	{
		CurrentByte = InBuffer[BufferReadIndex];
		#IFDEF PACKET_FILTER_DEBUG
		Printf("\nFilter %u byte %u char ", AcceptanceFlag, CurrentByte);
		putc(CurrentByte);
		#ENDIF
		switch (AcceptanceFlag)
		{
		case 0:
			if(CurrentByte == Preamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
			break;
		case 1:
			if(CurrentByte == Preamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
			break;
		case 2:
			if(CurrentByte == Preamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
			break;
		case 3:
			if(CurrentByte == Preamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
			break;
		case 4: //check aagainst the node number - or to see if it is a broadcast
			if(CurrentByte == RS232NodeNumber || CurrentByte == 0)
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
			break;
		case 5://check to see if this is a valid command (A keyboard character UPPER or Lower case)
			if(CurrentByte > 47 && CurrentByte < 123)
			{
				AcceptanceFlag++;
				Command1 = CurrentByte;
			}
			else AcceptanceFlag = 0;
			break;
		case 6://check to see if this is a valid command (A keyboard character UPPER or Lower case)
			if(CurrentByte > 47 && CurrentByte < 123)
			{
				AcceptanceFlag++;
				Command2 = CurrentByte;
			}
			else AcceptanceFlag = 0;
			break;
		case 7://This should be a packet length - if zero then this is just a command with no data
				//if greater than 128 then it is an invalid packet - the largest packet is 128 bytes
			if(CurrentByte < 129)
			{
				AcceptanceFlag = 0;
				PacketSize = CurrentByte;

				PacketAccepted = 1;
			}
			else AcceptanceFlag = 0;
			break;
		default:
				#IFDEF PACKET_FILTER_DEBUG
				Printf("\nDefault Filter %u byte %u char ", AcceptanceFlag, CurrentByte);
				putc(CurrentByte);
				#ENDIF
		  		AcceptanceFlag = 0;
		  	break;
		}
		//each time you pass a byte through the case checker de-incriment the buffer in out diff counter
		//and incriment the buffer read index - checking the limits

		BufferInOutDifference--;
		BufferReadIndex++;
		#IFDEF PACKET_FILTER_DEBUG
		printf("\nIO diff in pkt check %u Read Index %u\n", BufferInOutDifference, BufferReadIndex);
		#ENDIF
		if(BufferReadIndex >= BUFFERSIZE) BufferReadIndex = 0;

		//if at any point the packet gets accepted then return
		if(PacketAccepted == 1)
		{
			//The buffer read index has been incrimented to look at the NEXT byte
			//which will be the first byte of the data in the packet
			DataStartIndex = BufferReadIndex;
			#IFDEF PACKET_FILTER_DEBUG
			printf("\nPacket Filter passed\n");
			#ENDIF
			return packetAccepted;
		}

	}
	//if you get to here then you have reached the end of the buffer and there are no more pending bytes
	//and the packet filter has not been passed
	return packetAccepted;

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

int8 ProcessProfilePacket(int8 BufferStartIndex)
{
	/*
	assuming that a packet has passed the packet filter then this function will sort through
	the incoming databuffer and assign the variables to their appropriate slots.

	The incoming data is first placed in the temp variable arrays and only transferred to flash and then RAM
	afterwards.

	This function is only called when the full packet has been recieved

	return values are
	2 for an error (Reset the serial system)
	0 for no error - packet processed OK
	*/
	static int16 IndexPos = 0;
	int16 Result = 0;
	int8 n;
	int8 DataBlock, Targetprofile;
	DataBlock = Command2 - 48;
	Targetprofile = Command1 - 48;
	if(TargetProfile >= FLASH_PROFILES) SendErrorMessage(1);
	#ifdef PACKET_UNPACKER_DEBUG
	printf("\nIn Processing profile packet function\n");
	printf("Cmd1 %u Cmd2 %u PkLen %u\n",Command1, Command2,PacketSize);


	#endif


	if(Mode != 0)
	{
		return 2;
	}
	switch (DataBlock)
	{
	case 0:
		//Datablock0 is the force profile - incoming as int16's
		//every second byte needs to be converted to an Sint16 and then scaled
		if(PacketSize != 128)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}//return an error if the packet length is wrong
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing data block %u for profile %u\n", DataBlock, Targetprofile);
		#endif
		for(n = 0; n < 64; n++)
		{
			if(IndexPos == BUFFERSIZE-1) Result = make16(InBuffer[IndexPos], InBuffer[0]);
			else Result = make16(InBuffer[IndexPos], InBuffer[IndexPos+1]);
			TempForceTable[n] = ConvertToSInt16(Result);
			#ifdef PACKET_UNPACKER_DEBUG
			//printf("%ld ", TempForceTable[n]);
			#endif
			IndexPos+=2;
			BufferInOutDifference-=2;
			if(IndexPos > BUFFERSIZE) IndexPos = 1;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		//set a flag to indicate that this element of the profile has been recieved OK
		bit_set(ProfileDownloadedLoadedFlags, 0);
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 1:
		//Datablock1 is the PDamp profile - incoming as uint8's
		if(PacketSize != 64)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing data block %u for profile %u\n", DataBlock, Targetprofile);
		#endif
		for(n = 0; n < 64; n++)
		{
			//Sint8Result = (signed int8)InBuffer[IndexPos];
			TempPDampTable[n] = (signed int8)InBuffer[IndexPos];
			#ifdef PACKET_UNPACKER_DEBUG
			//printf("%d ", TempPDampTable[n]);
			#endif
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		bit_set(ProfileDownloadedLoadedFlags, 1);
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 2:
		//Datablock2 is the NDamp profile - incoming as uint8's
		if(PacketSize != 64)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing data block %u for profile %u\n", DataBlock, Targetprofile);
		#endif
		for(n = 0; n < 64; n++)
		{
			//Sint8Result = (signed int8)InBuffer[IndexPos];
			TempNDampTable[n] = (signed int8)InBuffer[IndexPos];
			#ifdef PACKET_UNPACKER_DEBUG
			//printf("%d ", TempNDampTable[n]);
			#endif
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		bit_set(ProfileDownloadedLoadedFlags, 2);
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 3:
		//Datablock3 are the SInt16 Variables
		if(PacketSize != 64)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing data block %u for profile %u\n", DataBlock, Targetprofile);
		#endif
		for(n = 0; n < 32; n++)
		{
			if(IndexPos == BUFFERSIZE-1) Result = make16(InBuffer[IndexPos], InBuffer[0]);
			else Result = make16(InBuffer[IndexPos], InBuffer[IndexPos+1]);
			FlashTemp16[n] = ConvertToSInt16(Result);
			#ifdef PACKET_UNPACKER_DEBUG
			//printf("%ld ", FlashTemp16[n]);
			#endif
			IndexPos+=2;
			BufferInOutDifference-=2;
			if(IndexPos > BUFFERSIZE) IndexPos = 1;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		bit_set(ProfileDownloadedLoadedFlags, 3);
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 4:
		//Datablock4  are int8 variables - incoming as uint8's
		if(PacketSize != 32)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif;
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing data block %u for profile %u\n", DataBlock, Targetprofile);
		#endif
		for(n = 0; n < 32; n++)
		{
			FlashTemp8[n] = InBuffer[IndexPos];
			#ifdef PACKET_UNPACKER_DEBUG
			//printf("%u ",FlashTemp8[n]);
			#endif
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		bit_set(ProfileDownloadedLoadedFlags, 4);
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 5:
	//Datablock5 are int16 pointer assignments - incoming as uint8's
		if(PacketSize != 64)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing data block %u for profile %u\n", DataBlock, Targetprofile);
		#endif
		for(n = 0; n < 64; n++)
		{
			PointerList16[n] = InBuffer[IndexPos];
			#ifdef PACKET_UNPACKER_DEBUG
			//printf("%u ",PointerList16[n]);
			#endif
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		bit_set(ProfileDownloadedLoadedFlags, 5);
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 6:
		//Datablock6  are int8 pointer assignments - incoming as uint8's
		if(PacketSize != 64)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing data block %u for profile %u\n", DataBlock, Targetprofile);
		#endif
		for(n = 0; n < 64; n++)
		{
			PointerList8[n] = InBuffer[IndexPos];
			#ifdef PACKET_UNPACKER_DEBUG
			//printf("%u ",PointerList8[n]);
			#endif
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		bit_set(ProfileDownloadedLoadedFlags, 6);
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 7://this is the last data packet
		//this processes all the collected data and saves the finished profile
		//this should be just the command '(TargetProfile)' and '7' with a packet size of 1 and dummy data
		//if this is called without receiving all the relevant data then it will
		//write whatever is in the buffers to RAM but not to flash!!!

		IndexPos = BufferStartIndex;

		//remove the dummydata
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		if(ProfileDownloadedLoadedFlags != 127)
		{
			SendErrorMessage(2);
			printf("\nERROR - Profile Download incomplete Flag Value = %u\n", ProfileDownloadedLoadedFlags);
			return 2;
		}
		ProfileDownloadedLoadedFlags = 0;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing Downloaded Profile %u\n", Targetprofile);
		#endif
		ProcessCompleteDownloadedProfile(Targetprofile);
		SendConfirmMessage(0, Targetprofile);
		break;
	case 8://this is an actuator settings packet (Applies to ALL profile groups)
		if(PacketSize != 32)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif;
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing Actuator Config Block %u\n", DataBlock);
		#endif
		for(n = 0; n < 32; n++)
		{
			ActuatorFlashSettings[n] = InBuffer[IndexPos];
			#ifdef PACKET_UNPACKER_DEBUG
				//printf("%u ",ActuatorFlashSettings[n]);
			#endif
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		#ifdef PACKET_UNPACKER_DEBUG
			printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		ProcessDownloadedActuatorPacket();
		SendConfirmMessage(2, Targetprofile);
		break;
	default:
		return 2; //return an error
		break;
	}
	BufferReadIndex = IndexPos;
	return 0;

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

int8 ProcessControlPacket(int8 BufferStartIndex)
{
	//process a control packet - these only ever apply to the current profile
	/*
	return values are
	2 for an error (Reset the serial system)
	0 for no error - packet processed OK

	Command1  determines which command to execute ( Which switch statement to use)
	Command2 determines if any data is to be returned

	Command1 List:
	'A' - incoming data goes into serial variable input block A (First 4 words)
	'B' - Incoming data goes into serial variable input block B (Last four words)
	'C' - Used for serial flag inputs (not implemented yet)
	*/
	static int16 IndexPos = 0;
	int8 n;
	int16 Result = 0;
	int8 TargetProfile = 0;
	int8 XProfile, YProfile;

	//test

	 int16 DualDampVal;
	 int8 TDampV1, TDampV2;
	 signed int16 SiInt16Test;
	switch (Command1)
	{
	case 'A'://Command 'A' means put incoming data into Serial Input block A
		if(PacketSize != 15)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing Serial input variable block A\n");
		#endif
		//First unpack the 16bit variables
		for(n = 0; n < 4; n++)
		{
			if(IndexPos == BUFFERSIZE-1) Result = make16(InBuffer[IndexPos], InBuffer[0]);
			else Result = make16(InBuffer[IndexPos], InBuffer[IndexPos+1]);
			RS232In[n] = ConvertToSInt16(Result);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("%ld ", RS232In[n]);
			#endif
			IndexPos+=2;
			BufferInOutDifference-=2;
			if(IndexPos > BUFFERSIZE) IndexPos = 1;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		//Now unpack the 8bit Flags
		for(n = 0; n < 4; n++)
		{
			RS232FlagsIn[n]  = InBuffer[IndexPos];
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0; 
		}
		//Now get the from node, mode and working profile
		/*
		RS232FromNode = 0;
		RS232FromMode = 0;
		RS232FromProfile = 0;
		*/
		RS232FromNodeA = InBuffer[IndexPos];
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		
		RS232FromModeA = InBuffer[IndexPos];
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		
		RS232FromProfileA = InBuffer[IndexPos];
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		
		if(Command2 == 'A') RS232AutoReplyBlockA();
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 'B'://Command 'B' means put incoming data into Serial Input block B
		if(PacketSize != 15)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		IndexPos = BufferStartIndex;
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nProcessing Serial input variable block B\n");
		#endif
		for(n = 4; n < 8; n++)
		{
			if(IndexPos == BUFFERSIZE-1) Result = make16(InBuffer[IndexPos], InBuffer[0]);
			else Result = make16(InBuffer[IndexPos], InBuffer[IndexPos+1]);
			RS232In[n] = ConvertToSInt16(Result);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("%ld ", RS232In[n]);
			#endif
			IndexPos+=2;
			BufferInOutDifference-=2;
			if(IndexPos > BUFFERSIZE) IndexPos = 1;
			if(IndexPos == BUFFERSIZE) IndexPos = 0;
		}
		for(n = 4; n < 8; n++)
		{
			RS232FlagsIn[n]  = InBuffer[IndexPos];
			IndexPos++;
			BufferInOutDifference--;
			if(IndexPos == BUFFERSIZE) IndexPos = 0; 
		}
		//Now get the from node, mode and working profile
		/*
		RS232FromNode = 0;
		RS232FromMode = 0;
		RS232FromProfile = 0;
		*/
		RS232FromNodeB = InBuffer[IndexPos];
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		
		RS232FromModeB = InBuffer[IndexPos];
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		
		RS232FromProfileB = InBuffer[IndexPos];
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		
		if(Command2 == 'A') RS232AutoReplyBlockB();
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nBuffer IO = %u\n", BufferInOutDifference);
		#endif
		break;
	case 'P':
		if(PacketSize != 1)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		//Print the profile (Command2 is the profile to print
		IndexPos = BufferStartIndex;
		//remove the dummydata
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		TargetProfile = Command2 - 48;
		if(TargetProfile >= FLASH_PROFILES)
		{
			SendErrorMessage(1);
			return 2;
		}
		PrintProfile(TargetProfile);
		break;
	case 'S':
		if(PacketSize != 1)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		//Save Profile X to profile Y (Command 2 is X and Data 1 is Y)
		IndexPos = BufferStartIndex;


		XProfile = Command2 - 48;
		YProfile = InBuffer[IndexPos] - 48;

		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;
		if(XProfile >= FLASH_PROFILES || YProfile >= FLASH_PROFILES)
		{
			SendErrorMessage(1);
			return 2;
		}

		//save the profile from the buffers to flash
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nSaving Profile %u to Profile %u\n", XProfile, YProfile);
		#endif
		CopyProfileXToProfileY(XProfile, YProfile);
		break;
	case 'J':
		if(PacketSize != 1)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		//Jump to profile in command2
		IndexPos = BufferStartIndex;
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;

		TargetProfile = Command2;

		if(TargetProfile >= FLASH_PROFILES)
		{
			SendErrorMessage(1);
			return 2;
		}
		CurrentProfile = TargetProfile;
		//Prepare profile forsaving
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nCurrent active profile is now %u\n", CurrentProfile);
		#endif
		break;
	
	case 'X':
		if(PacketSize != 1)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		//Start stop command
		IndexPos = BufferStartIndex;
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;

		if(Command2 == 'A')
		{
			//Start actuator
			ResumeActuator();
			//StartMotor

			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nStart Command recieved ");
			printf("Mode = %u\n", Mode);
			#endif
		}
		else if(Command2 == 'B')
		{
			//Stop Actuator
			HaltActuator();
			//StopMotor
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nStop Command recieved ");
			printf("Mode = %u\n", Mode);
			#endif
		}
		else if(Command2 == 'X')
		{
			//Restart
			HaltActuator();
			
			//StopMotor
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nRestart Command recieved ");
			printf("Mode = %u\n", Mode);
			#endif
			reset_cpu();
		}

		break;
	case 'N':
		if(PacketSize != 1)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		//Return your node details
		IndexPos = BufferStartIndex;
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;

		TargetProfile = Command2;

		if(TargetProfile >= FLASH_PROFILES)
		{
			SendErrorMessage(1);
			return 2;
		}
		CurrentProfile = TargetProfile;
		//Prepare profile forsaving
		#ifdef PACKET_UNPACKER_DEBUG
		printf("\nCurrent active profile is now %u\n", CurrentProfile);
		#endif
		break;
	case 'T':
		if(PacketSize != 1)
		{
			SendErrorMessage(0);
			#ifdef PACKET_UNPACKER_DEBUG
			printf("\nWrong Packet Size == %u\n", packetSize);
			#endif
			return 2; //return an error if the packet length is wrong
		}
		//General test packet
		IndexPos = BufferStartIndex;
		IndexPos++;
		BufferInOutDifference--;
		if(IndexPos == BUFFERSIZE) IndexPos = 0;

		TargetProfile = Command2 - 48;

		if(TargetProfile >= FLASH_PROFILES)
		{
			SendErrorMessage(1);
			return 2;
		}


   		SiInt16Test = read_program_eeprom(FlashProfileStart[TargetProfile]);
   		printf("\nFirst profile value is %ld\n", SiInt16Test);

   		DualDampVal = read_program_eeprom(FlashProfileStart[TargetProfile]+128);
   		TDampV1 = make8(DualDampVal, 0);
   		TDampV2 = make8(DualDampVal, 1);
   		printf("1st DampValues are %d  %d\n", TDampV1, TDampV2);

   		DualDampVal = read_program_eeprom(FlashProfileStart[TargetProfile]+192);
   		TDampV1 = make8(DualDampVal, 0);	//first byte
   		TDampV2 = make8(DualDampVal, 1);	//second byte
   		printf("2nd DampValues are %d  %d\n", TDampV1, TDampV2);

		break;
	default:
		SendErrorMessage(2);
		return 2; //return an error
		break;
	}
	BufferReadIndex = IndexPos;
	return 0;



}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void SendRS232Preamble()
{
	//transmits the preamble prior to sending a data packet
	//int8 Preamble[5] = "PGS#";
	//int8 ActuatorNode = 49; //ascii '1'
	putc(Preamble[0]);
	putc(Preamble[1]);
	putc(Preamble[2]);
	putc(Preamble[3]);
	putc(RS232NodeNumber);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void SendErrorMessage(int8 ErrorNo)
{
	//send a message preceeded by a preamble over the serial bus
	switch (ErrorNo)
	{
	case 0:
		//A packet Size mismatch Error
		SendRS232Preamble();

		putc('E');
		delay_us(10);
		putc(ErrorNo);
		delay_us(10);
		//Now put the packet length
		putc(31);
		printf("ERROR - Wrong Packet Length %3u",ErrorNo);
		break;

	case 1:
		//A profile out of bounds error
		SendRS232Preamble();
		putc('E');
		delay_us(10);
		putc(ErrorNo);
		delay_us(10);
		//Now put the packet length
		putc(28);

		printf("ERROR - Profile To Large %3u",ErrorNo);
		break;
	default:
		SendRS232Preamble();
		putc('E');
		delay_us(10);
		putc(ErrorNo);
		delay_us(10);
		//Now put the packet length
		putc(11);

		printf("ERROR - %3u",ErrorNo);
		break;
	}

}

void SendConfirmMessage(int8 MsgNo, int8 ProfileNo)
{
	//sends a confirmation message
	switch (MsgNo)
	{
	case 0:
		//A download OK Message for Profile ProfileNo
		SendRS232Preamble();

		putc('V');
		delay_us(10);
		putc(MsgNo);
		delay_us(10);
		//Now put the packet length
		putc(14);
		printf("Pro DL OK! %3u",ProfileNo);
		break;

	case 1:
		//General OK message . . .
		SendRS232Preamble();
		putc('V');
		delay_us(10);
		putc(MsgNo);
		delay_us(10);
		//Now put the packet length
		putc(12);

		printf("Job Done %3u",MsgNo);
		break;
	case 2:
		//An actuator config download OK message
		SendRS232Preamble();
		putc('V');
		delay_us(10);
		putc(MsgNo);
		delay_us(10);
		//Now put the packet length
		putc(10);

		printf("Act DL OK!");
		break;
	default:
		SendRS232Preamble();
		putc('V');
		delay_us(10);
		putc(MsgNo);
		delay_us(10);
		//Now put the packet length
		putc(8);

		printf("OK - %3u",MsgNo);
		break;
	}
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

signed int16 ConvertToSInt16(int16 Value)
{
	//convert a full range int16 to a signed int16 variable
	// UINT16MAX	65535
	// UINT16ZERO 	32767
	signed int16 Result;

	if(Value < UINT16ZERO)
	{
		Result = -32767 + ( (signed int16)Value );
	}
	else
	{
		Result = (signed int16)(Value - UINT16ZERO);
	}
	return Result;

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

int16 ConvertToUInt16(signed int16 Value)
{
	//convert a full range Signed int16 to a unsigned int16 variable
	// UINT16MAX	65535
	// UINT16ZERO 	32767
	int16 Result;

	if(Value < 0)
	{
		Result = UINT16ZERO - (int16)abs(Value);
	}
	else
	{
		Result = UINT16ZERO + (int16)abs(Value);
	}
	return Result;

}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void RS232TransmitBlockA()
{
	//transmits block A of the current profiles output data array
	//CurrentProfile
	int16 UTempData;
	//printf("\nSending Block A\n");

	putc(Preamble[0]);
	putc(Preamble[1]);
	putc(Preamble[2]);
	putc(Preamble[3]);
	putc(RS232OutTargetNodeA[CurrentProfile]);
	//now send the commands you have just recieved replacing command2 with the current profile
	//this needs work so you get a better command structure
	//- and so you can configure two actuators to pass data to each other over the serial port
	putc('A');

	if(RS232RequestReplyA[CurrentProfile] > 0) putc('A');
	else putc('X');
	delay_us(5);
	//Now put the packet length
	putc(15);
	//Convert the Sint16 to a uint16
	UTempData = ConvertToUInt16(*RS232Out1_ptr[CurrentProfile]);
	//send the upper then the lower bytes
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out2_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out3_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out4_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	//Now the flags
	putc( *RS232FlagsOut1_ptr[CurrentProfile] );
	putc( *RS232FlagsOut2_ptr[CurrentProfile] );
	putc( *RS232FlagsOut3_ptr[CurrentProfile] );
	putc( *RS232FlagsOut4_ptr[CurrentProfile] );
	
	putc( RS232NodeNumber );
	putc( Mode );
	putc( CurrentProfile );

}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void RS232AutoReplyBlockA()
{
	//Replies to a request for a packet to the requesting node - never requests a reply
	int16 UTempData;
	//printf("\nSending Block A\n");

	putc(Preamble[0]);
	putc(Preamble[1]);
	putc(Preamble[2]);
	putc(Preamble[3]);
	putc(RS232FromNodeA);
	putc('A');
	putc('X');
	delay_us(5);
	//Now put the packet length
	putc(15);
	//Convert the Sint16 to a uint16
	UTempData = ConvertToUInt16(*RS232Out1_ptr[CurrentProfile]);
	//send the upper then the lower bytes
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out2_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out3_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out4_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	//Now the flags
	putc( *RS232FlagsOut1_ptr[CurrentProfile] );
	putc( *RS232FlagsOut2_ptr[CurrentProfile] );
	putc( *RS232FlagsOut3_ptr[CurrentProfile] );
	putc( *RS232FlagsOut4_ptr[CurrentProfile] );
	
	putc( RS232NodeNumber );
	putc( Mode );
	putc( CurrentProfile );
	
}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void RS232TransmitBlockB()
{
	//transmits block A of the current profiles output data array
	//CurrentProfile
	int16 UTempData;
	//printf("\nSending Block B\n");


	putc(Preamble[0]);
	putc(Preamble[1]);
	putc(Preamble[2]);
	putc(Preamble[3]);
	putc(RS232OutTargetNodeB[CurrentProfile]);
	//now send the commands you have just recieved, replacing command2 with the current profile
	//this needs work so you get a better command structure
	//- and so you can configure two actuators to pass data to each other over the serial port
	putc('B');

	if(RS232RequestReplyB[CurrentProfile] > 0) putc('A');
	else putc('X');
	delay_us(5);
	//Now put the packet length
	putc(15);
	//Convert the Sint16 to a uint16
	UTempData = ConvertToUInt16(*RS232Out5_ptr[CurrentProfile]);
	//send the upper then the lower bytes
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out6_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out7_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out8_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );
	//Now the flags
	putc( *RS232FlagsOut5_ptr[CurrentProfile] );
	putc( *RS232FlagsOut6_ptr[CurrentProfile] );
	putc( *RS232FlagsOut7_ptr[CurrentProfile] );
	putc( *RS232FlagsOut8_ptr[CurrentProfile] );
	
	putc( RS232NodeNumber );
	putc( Mode );
	putc( CurrentProfile );

}


//==============================================================================================

void RS232AutoReplyBlockB()
{
	//Replies to a request for a packet to the requesting node - never requests a reply
	int16 UTempData;
	//printf("\nSending Block B\n");


	putc(Preamble[0]);
	putc(Preamble[1]);
	putc(Preamble[2]);
	putc(Preamble[3]);
	putc(RS232FromNodeB);
	putc('B');
	putc('X');
	delay_us(5);
	//Now put the packet length
	putc(15);
	//Convert the Sint16 to a uint16
	UTempData = ConvertToUInt16(*RS232Out5_ptr[CurrentProfile]);
	//send the upper then the lower bytes
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out6_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out7_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );

	UTempData = ConvertToUInt16(*RS232Out8_ptr[CurrentProfile]);
	putc( make8(UTempData, 1) );
	putc( make8(UTempData, 0) );
	//Now the flags
	putc( *RS232FlagsOut5_ptr[CurrentProfile] );
	putc( *RS232FlagsOut6_ptr[CurrentProfile] );
	putc( *RS232FlagsOut7_ptr[CurrentProfile] );
	putc( *RS232FlagsOut8_ptr[CurrentProfile] );
	
	putc( RS232NodeNumber );
	putc( Mode );
	putc( CurrentProfile );

}


//==============================================================================================
void PrintProfile(int8 ProfileToUse)
{

    int8 n;
    int16 Temp1;
    signed int8 ByteVal1, ByteVal2;
    int16 FlashAddress;
    if(ProfileToUse >= FLASH_PROFILES)
    {
    	SendErrorMessage(0);
    	printf("\nNo such profile error in Print Profile!\n");
    	return;
    }
    printf("\nPrinting Profile %u", ProfileToUse);
    printf("\nForceTable:\n");

    FlashAddress = FlashProfileStart[ ProfileToUse];
    for(n = 0; n < 64; n++)
    {

        printf("%ld ", read_program_eeprom( FlashAddress ) );
        FlashAddress+=2;
    }
    printf("\nPDTable:\n");


    for(n = 0; n < 32; n++)
    {
    		Temp1 = read_program_eeprom( FlashAddress );
    		ByteVal1 = make8(Temp1 ,0);
    		ByteVal2 = make8(Temp1 ,1);
        	printf("%d %d ",ByteVal1, ByteVal2);
        	FlashAddress+=2;
    }


    printf("\nNDTable:\n");
    for(n = 0; n < 32; n++)
    {
    		Temp1 = read_program_eeprom( FlashAddress );
    		ByteVal1 = make8(Temp1 ,0);
    		ByteVal2 = make8(Temp1 ,1);
        	printf("%d %d ",ByteVal1, ByteVal2);
        	FlashAddress+=2;
    }


    printf("\n\n");
   printf("HBias_ptr %ld ", *HBias_ptr[ProfileToUse] );
	printf("VBias_ptr %ld ", *VBias_ptr[ProfileToUse] );
	printf("HScale_ptr %ld ", *HScale_ptr[ProfileToUse] );
	printf("VScale_ptr %ld ", *VScale_ptr[ProfileToUse] );

	printf("DefaultHBias %ld ", DefaultHBias[ProfileToUse] );
	printf("DefaultVBias %ld ", DefaultVBias[ProfileToUse] );
	printf("DefaultHScale %ld ", DefaultHScale[ProfileToUse] );
	printf("DefaultVScale %ld ", DefaultVScale[ProfileToUse] );

	printf("\n\n");
	printf("EQAngle %ld ", EQAngle[ProfileToUse] );
   printf("DefaultUniformDamping %ld ", DefaultUniformDamping[ProfileToUse] );
   printf("UniformDamping_ptr %ld ", *UniformDamping_ptr[ProfileToUse] );


   printf("\n\n");
   printf("AltPro1_ptr %u ", *AltPro1_ptr[ProfileToUse] );
	printf("AltPro2_ptr %u ", *AltPro2_ptr[ProfileToUse] );
	printf("AltPro3_ptr %u ", *AltPro3_ptr[ProfileToUse] );
	printf("AltPro4_ptr %u ", *AltPro4_ptr[ProfileToUse] );
	printf("AltPro1 %u ", AltPro1[ProfileToUse] );
	printf("AltPro2 %u ", AltPro2[ProfileToUse] );
	printf("AltPro3 %u ", AltPro3[ProfileToUse] );
	printf("AltPro4 %u ", AltPro4[ProfileToUse] );
	printf("IncrimentProfile_ptr %u ", *IncrimentProfile_ptr[ProfileToUse] );
	printf("IncrimentProfile_ptr %u ", *IncrimentProfile_ptr[ProfileToUse] );

	printf("\nProfile %u Thresholds1:\n", ProfileToUse);
	printf("Threshold1Input_ptr %ld ", *Threshold1Input_ptr[ProfileToUse] );
	printf("PT1Value_ptr %ld ", *PT1Value_ptr[ProfileToUse] );
	printf("NT1Value_ptr %ld ", *NT1Value_ptr[ProfileToUse] );
	printf("PT1Default %ld ", PT1Default[ProfileToUse] );
	printf("NT1Default %ld ", NT1Default[ProfileToUse] );
	printf("PT1State %u ", PT1State[ProfileToUse] );
	printf("NT1State %u ", NT1State[ProfileToUse] );
	printf("PT1Enabled_ptr %u ", *PT1Enabled_ptr[ProfileToUse] );
	printf("NT1Enabled_ptr %u ", *NT1Enabled_ptr[ProfileToUse] );

	printf("\nProfile %u Thresholds2:\n", ProfileToUse);
	printf("Threshold2Input_ptr %ld ", *Threshold2Input_ptr[ProfileToUse] );
	printf("PT2Value_ptr %ld ", *PT2Value_ptr[ProfileToUse] );
	printf("NT2Value_ptr %ld ", *NT2Value_ptr[ProfileToUse] );
	printf("PT2Default %ld ", PT2Default[ProfileToUse] );
	printf("NT2Default %ld ", NT2Default[ProfileToUse] );
	printf("PT2State %u ", PT2State[ProfileToUse] );
	printf("NT2State %u ", NT2State[ProfileToUse] );
	printf("PT2Enabled_ptr %u ", *PT2Enabled_ptr[ProfileToUse] );
	printf("NT2Enabled_ptr %u ", *NT2Enabled_ptr[ProfileToUse] );

	printf("\nProfile %u Thresholds3:\n", ProfileToUse);
	printf("Threshold3Input_ptr %ld ", *Threshold3Input_ptr[ProfileToUse] );
	printf("PT3Value_ptr %ld ", *PT3Value_ptr[ProfileToUse] );
	printf("NT3Value_ptr %ld ", *NT3Value_ptr[ProfileToUse] );
	printf("PT3Default %ld ", PT3Default[ProfileToUse] );
	printf("NT3Default %ld ", NT3Default[ProfileToUse] );
	printf("PT3State %u ", PT3State[ProfileToUse] );
	printf("NT3State %u ", NT3State[ProfileToUse] );
	printf("PT3Enabled_ptr %u ", *PT3Enabled_ptr[ProfileToUse] );
	printf("NT3Enabled_ptr %u ", *NT3Enabled_ptr[ProfileToUse] );

	printf("\nProfile %u Thresholds4:\n", ProfileToUse);
	printf("Threshold4Input_ptr %ld ", *Threshold4Input_ptr[ProfileToUse] );
	printf("PT4Value_ptr %ld ", *PT4Value_ptr[ProfileToUse] );
	printf("NT4Value_ptr %ld ", *NT4Value_ptr[ProfileToUse] );
	printf("PT4Default %ld ", PT4Default[ProfileToUse] );
	printf("NT4Default %ld ", NT4Default[ProfileToUse] );
	printf("PT4State %u ", PT4State[ProfileToUse] );
	printf("NT4State %u ", NT4State[ProfileToUse] );
	printf("PT4Enabled_ptr %u ", *PT4Enabled_ptr[ProfileToUse] );
	printf("NT4Enabled_ptr %u ", *NT4Enabled_ptr[ProfileToUse] );

	printf("\n\n");
	printf("OSC1Out %ld ", OSC1Out[ProfileToUse] );
	printf("StepSize %u ", StepSize[ProfileToUse] );
	printf("Iterator %u ", Iterator[ProfileToUse] );
	printf("OSC1Min %ld ", OSC1Min[ProfileToUse] );
	printf("OSC1Max %ld ", OSC1Max[ProfileToUse] );
	printf("SkipRate %u ", SkipRate[ProfileToUse] );
	printf("\n\n");
	printf("ADOut1_ptr %ld ", *ADOut1_ptr[ProfileToUse] );
	printf("ADOut2_ptr %ld ", *ADOut2_ptr[ProfileToUse] );
	printf("ADOut1Scaling %u ", ADOut1Scaling[ProfileToUse] );
	printf("ADOut2Scaling %u ", ADOut2Scaling[ProfileToUse] );
	printf("\n\n");
	printf("SummedFlag %u ", SummedFlag[ProfileToUse] );
	printf("SummedFlag1_ptr %u ", *SummedFlag1_ptr[ProfileToUse] );
	printf("SummedFlag2_ptr %u ", *SummedFlag2_ptr[ProfileToUse] );
	printf("SummedFlag3_ptr %u ", *SummedFlag3_ptr[ProfileToUse] );
	printf("SummedFlag4_ptr %u ", *SummedFlag4_ptr[ProfileToUse] );

	printf("\n\n\n============================================\n\n\n");


}


