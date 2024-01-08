/////////////////////////////////////////////////////////////////////////////
// Name:        SupervisorComm.cpp
// Purpose:     Beremiz Project Manager supervisor communication
// Author:      Benoit BOUCHEZ
// Created:     12/05/2022
/////////////////////////////////////////////////////////////////////////////

/*
* MIT License
*
* Copyright(c) 2022 - 2024 Benoit BOUCHEZ
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

/*
Beremiz Project Manager requires a supervisor to run on the target. The supervisor is in charge
of communicating with the project manager.
It provides the following function :
- start/stop PLC program
- PLC program compilation if compilation in case cross compilation is not used
- access to PLC variables for debugging
- PLC source files transfer
*/

#include "SupervisorComm.h"
#include <string.h>
#include <stdio.h>
#include "SystemSleep.h"
#ifdef __TARGET_LINUX__
#include <arpa/inet.h>
#endif // __TARGET_LINUX__
#include "BeremizProjectManager_SDK_Defs.h"

#define SUPERVISOR_UDP_PORT		61170

CSupervisorCommunicator::CSupervisorCommunicator ()
{
	SupervisorSocket=INVALID_SOCKET;

	// Try to create socket for communication with supervisor
	CreateUDPSocket (&SupervisorSocket, 0, false);
}  // CSupervisorCommunicator::CSupervisorCommunicator
// -----------------------------------------------------

CSupervisorCommunicator::~CSupervisorCommunicator ()
{
	if (SupervisorSocket!=INVALID_SOCKET)
	{
		CloseSocket (&SupervisorSocket);
	}
}  // CSupervisorCommunicator::~CSupervisorCommunicator
// -----------------------------------------------------

bool CSupervisorCommunicator::CommSocketOK (void)
{
	if (SupervisorSocket==INVALID_SOCKET) return false;
	return true;
}  // CSupervisorCommunicator::CommSocketOK
// -----------------------------------------------------

int CSupervisorCommunicator::TestSupervisorConnection (wxString& RemoteTarget)
{
	sockaddr_in AdrEmit;
	char MsgBuffer[]="PING";
	int Sent;
	unsigned int IP;
	sockaddr from;
#if defined (__TARGET_WIN__)
	int fromlen;
#endif
#if defined (__TARGET_LINUX__)
    socklen_t fromlen;
#endif
	bool ReplyReceived;
	int TryCount;
	int Len;
	char Buffer[1500];

	IP = inet_addr (RemoteTarget.mb_str());

	memset (&AdrEmit, 0, sizeof(sockaddr_in));
	AdrEmit.sin_family=AF_INET;
	AdrEmit.sin_port=htons(SUPERVISOR_UDP_PORT);
	AdrEmit.sin_addr.s_addr=IP;

	Sent=sendto(SupervisorSocket, &MsgBuffer[0], 4, 0, (const sockaddr*)&AdrEmit, sizeof(sockaddr_in));
	if (Sent!=4) return -1;

	// Check reply from Supervisor
	fromlen=sizeof(from);
	TryCount = 100;
	ReplyReceived = false;
	do
	{
		if (DataAvail (SupervisorSocket, 0))
		{
			Len=recvfrom(SupervisorSocket, Buffer, sizeof(Buffer), 0, &from, &fromlen);
			if (Len>0)
			{
				if (memcmp(Buffer, "OK", 2)==0)
				{
					ReplyReceived=true;
				}
			}
		}
		else
		{
			SystemSleepMillis (10);
			TryCount--;
		}
	} while ((TryCount>0)&&(ReplyReceived==false));

	if (ReplyReceived==false) return -2;

	return 0;
}  // CSupervisorCommunicator::TestSupervisorConnection
// -----------------------------------------------------

int CSupervisorCommunicator::StartPLC (wxString& RemoteTarget)
{
	unsigned int IP;
	sockaddr_in AdrEmit;
	char MsgBuffer[]="START_PLC";
	int Sent;
	sockaddr from;
	int Len;
	char Buffer[1500];
#if defined (__TARGET_WIN__)
	int fromlen;
#endif
#if defined (__TARGET_LINUX__)
    socklen_t fromlen;
#endif
	bool ReplyReceived;
	int TryCount;
	bool PLCStartedReply;
	bool PLCAlreadyRunningReply;
	bool ThreadErrorReply;

	IP=inet_addr(RemoteTarget.mb_str());

	memset (&AdrEmit, 0, sizeof(sockaddr_in));
	AdrEmit.sin_family=AF_INET;
	AdrEmit.sin_port=htons(SUPERVISOR_UDP_PORT);
	AdrEmit.sin_addr.s_addr=IP;

	Sent=sendto(SupervisorSocket, &MsgBuffer[0], 9, 0, (const sockaddr*)&AdrEmit, sizeof(sockaddr_in));
	if (Sent!=9) return 1;

	// Wait now until the PLC answers it has started or times out
	fromlen=sizeof(from);
	TryCount = 100;
	ReplyReceived = false;
	PLCStartedReply = false;
	PLCAlreadyRunningReply = false;
	ThreadErrorReply = false;
	do
	{
		if (DataAvail (SupervisorSocket, 0))
		{
			Len=recvfrom(SupervisorSocket, Buffer, sizeof(Buffer), 0, &from, &fromlen);
			if (Len>0)
			{
				if (memcmp(Buffer, "PLC_STARTED", 11)==0)
				{
					PLCStartedReply = true;
					ReplyReceived=true;
				}
				else if (memcmp(Buffer, "PLC_RUNNING", 11)==0)
				{
					PLCAlreadyRunningReply=true;
					ReplyReceived=true;
				}
				else if (memcmp (Buffer, "THREAD_ERROR", 12)==0)
				{
					ThreadErrorReply=true;
					ReplyReceived=true;
				}
			}
		}
		else
		{
			SystemSleepMillis (10);
			TryCount--;
		}
	} while ((TryCount>0)&&(ReplyReceived==false));

	if (ReplyReceived==false) return 2;
	if (PLCAlreadyRunningReply) return 3;
	if (ThreadErrorReply) return 4;
	if (PLCStartedReply) return 0;

	return 5;  // Other replies from Supervisor
}  // CSupervisorCommunicator::StartPLC
// -----------------------------------------------------

int CSupervisorCommunicator::StopPLC (wxString& RemoteTarget)
{
	unsigned int IP;
	sockaddr_in AdrEmit;
	char MsgBuffer[]="STOP_PLC";
	int Sent;
	sockaddr from;
	int Len;
	char Buffer[1500];
#if defined (__TARGET_WIN__)
	int fromlen;
#endif
#if defined (__TARGET_LINUX__)
    socklen_t fromlen;
#endif
	bool ReplyReceived;
	bool PLCStopReply;
	bool PLCNotRunningReply;
	int TryCount;

	IP=inet_addr(RemoteTarget.mb_str());

	memset (&AdrEmit, 0, sizeof(sockaddr_in));
	AdrEmit.sin_family=AF_INET;
	AdrEmit.sin_port=htons(SUPERVISOR_UDP_PORT);
	AdrEmit.sin_addr.s_addr=IP;

	Sent=sendto(SupervisorSocket, &MsgBuffer[0], 8, 0, (const sockaddr*)&AdrEmit, sizeof(sockaddr_in));
	if (Sent!=8) return 1;

	// Wait now until the PLC answers it has stopped or times out
	fromlen=sizeof(from);
	TryCount = 400;		// We must give more time to StopPLC as threads must be stopped on target (takes to 2 seconds minimum)
	ReplyReceived = false;
	PLCStopReply = false;
	PLCNotRunningReply = false;
	do
	{
		if (DataAvail (SupervisorSocket, 0))
		{
			Len=recvfrom(SupervisorSocket, Buffer, sizeof(Buffer), 0, &from, &fromlen);
			if (Len>0)
			{
				if (memcmp(Buffer, "PLC_STOPPED", 11)==0)
				{
					PLCStopReply = true;
					ReplyReceived = true;
				}
				else if (memcmp(Buffer, "PLC_NOT_RUNNING", 15)==0)
				{
					PLCNotRunningReply = true;
					ReplyReceived = true;
				}
			}
		}
		else
		{
			SystemSleepMillis (10);
			TryCount--;
		}
	} while ((TryCount>0)&&(ReplyReceived==false));

	if (ReplyReceived==false) return 2;
	if (PLCStopReply) return 0;
	if (PLCNotRunningReply) return 3;

	return 4;  // Other replies from Supervisor
}  // CSupervisorCommunicator::StopPLC
// -----------------------------------------------------

int CSupervisorCommunicator::StartCompilation (wxString& RemoteTarget)
{
	unsigned int IP;
	int Sent;
	sockaddr_in AdrEmit;
	char CmdBuffer[1024];
	int TryCount;
#if defined (__TARGET_WIN__)
	int fromlen;
#endif
#if defined (__TARGET_LINUX__)
    socklen_t fromlen;
#endif
	sockaddr from;
	bool ReplyReceived;
	bool CompilationStartReply;
	bool CompilationFaultReply;
	int Len;
	char Buffer[1500];

	//Send compilation command to the Supervisor
	IP=inet_addr(RemoteTarget.mb_str());

	memset (&AdrEmit, 0, sizeof(sockaddr_in));
	AdrEmit.sin_family=AF_INET;
	AdrEmit.sin_port=htons(SUPERVISOR_UDP_PORT);
	AdrEmit.sin_addr.s_addr=IP;

	strcpy (CmdBuffer, "COMPILE_PLC");
	Sent=sendto(SupervisorSocket, &CmdBuffer[0], 11, 0, (const sockaddr*)&AdrEmit, sizeof(sockaddr_in));
	if (Sent!=11) return ERR_TARGET_COMMUNICATION_ERROR;

	// Wait until we receive COMPILATION_START from supervisor
	fromlen=sizeof(from);
	TryCount = 200;
	ReplyReceived = false;
	CompilationStartReply = false;
	CompilationFaultReply = false;
	do
	{
		if (DataAvail (SupervisorSocket, 0))
		{
			Len=recvfrom(SupervisorSocket, Buffer, sizeof(Buffer), 0, &from, &fromlen);
			if (Len>0)
			{
				if (memcmp(Buffer, "COMPILATION_START", 17)==0)
				{
					CompilationStartReply = true;
					ReplyReceived = true;
				}
				else if (memcmp(Buffer, "COMPILATION_FAULT", 17)==0)
				{
					CompilationFaultReply = true;
					ReplyReceived = true;
				}
			}
		}
		else
		{
			SystemSleepMillis (10);
			TryCount--;
		}
	} while ((TryCount>0)&&(ReplyReceived==false));

	if (ReplyReceived==false) return ERR_TARGET_COMMUNICATION_TIMEDOUT;
	if (CompilationStartReply) return TARGET_PLUGIN_NO_ERROR;
	if (CompilationFaultReply) return ERR_TARGET_COMPILER_FAULT;

	return ERR_TARGET_GENERIC_ERROR;  // Other errors
}  // CSupervisorCommunicator::StartCompilation
// -----------------------------------------------------

int CSupervisorCommunicator::GetCompilerMessages (char* LogBuffer)
{
	int Len;
	char Buffer[1500];
#if defined (__TARGET_WIN__)
	int fromlen;
#endif
#if defined (__TARGET_LINUX__)
    socklen_t fromlen;
#endif
	sockaddr from;

	if (DataAvail (SupervisorSocket, 0)==false) return 0;

	fromlen=sizeof(from);
	Len=recvfrom(SupervisorSocket, Buffer, sizeof(Buffer), 0, &from, &fromlen);
	if (Len>0)
	{
		if (memcmp(Buffer, "COMPILATION_END", 15)==0)
			return -1;   // Compilation finished
		else  // Compilation log received : copy the content in the buffer
		{
			strcpy (LogBuffer, Buffer);
			return strlen (Buffer);
		}
	}

	return 0;  // No compiler message received
}  // CSupervisorCommunicator::GetCompilerMessages
// -----------------------------------------------------

int CSupervisorCommunicator::SetAutomaticPLCStart (wxString& RemoteTarget, bool ShallStart)
{
	unsigned int IP;
	sockaddr_in AdrEmit;
	char CmdBuffer[256];
	int Sent;

	IP=inet_addr(RemoteTarget.mb_str());

	memset (&AdrEmit, 0, sizeof(sockaddr_in));
	AdrEmit.sin_family=AF_INET;
	AdrEmit.sin_port=htons(SUPERVISOR_UDP_PORT);
	AdrEmit.sin_addr.s_addr=IP;

	if (ShallStart)
	{
		strcpy (CmdBuffer, "AUTOSTART_ON");
		Sent=sendto(SupervisorSocket, &CmdBuffer[0], 12, 0, (const sockaddr*)&AdrEmit, sizeof(sockaddr_in));
		if (Sent!=12) return ERR_TARGET_COMMUNICATION_ERROR;
	}
	else
	{
		strcpy (CmdBuffer, "AUTOSTART_OFF");
		Sent=sendto(SupervisorSocket, &CmdBuffer[0], 13, 0, (const sockaddr*)&AdrEmit, sizeof(sockaddr_in));
		if (Sent!=13) return ERR_TARGET_COMMUNICATION_ERROR;
	}

	return TARGET_PLUGIN_NO_ERROR;
}  // CSupervisorCommunicator::SetAutomaticPLCStart
// -----------------------------------------------------
