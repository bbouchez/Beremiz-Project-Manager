/////////////////////////////////////////////////////////////////////////////
// Name:        SupervisorComm.h
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

#ifndef __SUPERVISORCOMM_H__
#define __SUPERVISORCOMM_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "network.h"


class CSupervisorCommunicator
{
public:
	CSupervisorCommunicator ();
	~CSupervisorCommunicator ();

	//! Report if constructor have been able to create the socket properly
	bool CommSocketOK (void);

	//! Check if Supervisor receives and process messages from Manager
	int TestSupervisorConnection (wxString& TargetIP);

	//! Sends a Start command to target
	//! \return positive value = error
	int StartPLC (wxString& RemoteTarget);
	//! Sends a Stop command to target
	//! \return positive value = error
	int StopPLC (wxString& RemoteTarget);
	//! Starts compilation on target
	int StartCompilation (wxString& RemoteTarget);
	//! Configure supervisor to enable/disable automatic PLC startup
	int SetAutomaticPLCStart (wxString& RemoteTarget, bool ShallStart);
	//! Gets compiler messages sent from remote compiler
	int GetCompilerMessages (char* LogBuffer);

private:
	TSOCKTYPE SupervisorSocket;
};

#endif
