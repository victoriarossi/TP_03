///////////////////////////////////////////////////////////////////////////////////////////////////
/* System Call Extensions
	syscallext.c

	This file contains functions that package system calls into more convenient function names.

	This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
	International License. To view a copy of this license, visit
	http://creativecommons.org/licenses/by-nc-nd/4.0/
	or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

	Also see http://www.bluekernel.com.au

	copyright Paul Cuttler 2017
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "syscallext.h"

extern pID_t server_pID;
extern pID_t video_pID;

// The following functions map onto system calls, but send the requests via the coordinator.

pID_t GetCoordinator(void)
{
	u32_t properties[2];
	
	properties[0]	= K_COORD;
	i32_t result	= GetProcess(0, properties);
	
	if (result == OK)
		return properties[0];
	else
		return result;
}

int SetAsCoordinator(void)
{
	u32_t msg[SERVER_MSG_SIZE];
	
	msg[MSG_TYPE]		= MSG_SET;
	msg[MSG_USER_TYPE]	= MSG_SET_COORDINATOR;
	msg[5]				= USE_CURRENT_PROCESS;

	Send(server_pID, msg, SERVER_MSG_SIZE,0);
    Receive(server_pID, msg, SERVER_MSG_SIZE,0);
	
    return msg[0];
}

void GetSystemInfo(void)
{
	u32_t msg[SERVER_MSG_SIZE];

	msg[MSG_TYPE] = MSG_INFO;

	Send(server_pID, msg, SERVER_MSG_SIZE, 0);
    Receive(server_pID, msg, SERVER_MSG_SIZE,0);

	// the video_pID is a global variable.
	video_pID = msg[0];
}

int SetProcessRequest(pID_t pID, int property, u32_t value)
{
	u32_t msg[SERVER_MSG_SIZE];

	msg[MSG_TYPE]		= MSG_SET;
	msg[MSG_USER_TYPE]	= SET_PROCESS_SYSCALL;
	msg[2]				= pID;
	msg[3]				= property;
	msg[4]				= value;
	msg[5]				= 0;
	Send(server_pID, msg, SERVER_MSG_SIZE, 0);
    Receive(server_pID, msg, SERVER_MSG_SIZE, 0);
}

i32_t AddPageRequest(pID_t pID, u32_t virtual_address, u32_t permissions)
{
	u32_t msg[SERVER_MSG_SIZE];

	msg[0] = ADD_PAGE_SYSCALL;
	msg[1] = pID;
	msg[2] = virtual_address;
	msg[3] = permissions;
	
	Send(server_pID, msg, SERVER_MSG_SIZE, 0);
    Receive(server_pID, msg, SERVER_MSG_SIZE, 0);

	return msg[0];
}

i32_t MapPageRequest(pID_t src_pID, u32_t src_virtual_address,
					 pID_t dst_pID, u32_t dst_virtual_address, u32_t permissions)
{
	u32_t msg[SERVER_MSG_SIZE];

	msg[0] = MAP_PAGE_SYSCALL;
	msg[1] = src_pID;
	msg[2] = src_virtual_address;
	msg[3] = dst_pID;
	msg[4] = dst_virtual_address;
	msg[5] = permissions;

	Send(server_pID, msg, SERVER_MSG_SIZE, 0);
    Receive(server_pID, msg, SERVER_MSG_SIZE, 0);
	
	return msg[0];
}

i32_t GrantPageRequest(pID_t src_pID, u32_t src_virtual_address,
					   pID_t dst_pID, u32_t dst_virtual_address, u32_t permissions)
{
	u32_t msg[SERVER_MSG_SIZE];

	msg[0] = GRANT_PAGE_SYSCALL;
	msg[1] = src_pID;
	msg[2] = src_virtual_address;
	msg[3] = dst_pID;
	msg[4] = dst_virtual_address;
	msg[5] = permissions;

	Send(server_pID, msg, SERVER_MSG_SIZE, 0);
    Receive(server_pID, msg, SERVER_MSG_SIZE, 0);
	
	return msg[0];
}

i32_t UnmapPageRequest(pID_t pID, u32_t virtual_address)
{
	u32_t msg[SERVER_MSG_SIZE];

	msg[0] = UNMAP_PAGE_SYSCALL;
	msg[1] = pID;
	msg[2] = virtual_address;
	
	Send(server_pID, msg, SERVER_MSG_SIZE,0);
    Receive(server_pID, msg, SERVER_MSG_SIZE,0);
	
	return msg[0];
}

/* GetProcess variations. These all call GetProcess().*/

u32_t GetProcessProperty(pID_t pID, u32_t property)
{
	u32_t result;
	u32_t properties[2];
	
	properties[0] = property;
	
	if ((result = GetProcess(pID, properties)) < 0)
	{
		kprintf("Get error.");
		return result;
	}
	else
	{
		return properties[0];
	}
}

u32_t GetNumProcesses(void)
{
	return GetProcessProperty(0, K_NUM_PROCS);
}
	
i32_t GetCoord(void)
{
	return GetProcessProperty(0, K_COORD);
}
	
u32_t GetTime(void)
{
	return GetProcessProperty(0, K_TIME);
}

i32_t GetCurrentPid(void)
{
	return GetProcessProperty(USE_CURRENT_PROCESS, P_PID);
}
	
// The following GetProcess calls are pID-specific.
u32_t GetPrivilege(pID_t pID)
{
	return GetProcessProperty(pID, P_PRIVILEGE);
}

i32_t GetBasePage(pID_t pID)
{
	return GetProcessProperty(pID, P_BASEPAGE);
}

i32_t GetStatus(pID_t pID)
{
	return GetProcessProperty(pID, P_STATUS);
}

i32_t GetReason(pID_t pID)
{
	return GetProcessProperty(pID, P_REASON);
}

i32_t GetSize(pID_t pID)
{
	return GetProcessProperty(pID, P_SIZE);
}

i32_t GetTimeRunning(pID_t pID)
{
	return GetProcessProperty(pID, P_RUNNING_TIME);
}
	
i32_t GetStartTime(pID_t pID)
{
	return GetProcessProperty(pID, P_START_TIME);
}
	
i32_t GetCurrentPriority(pID_t pID)
{
	return GetProcessProperty(pID, P_CURR_PRI);
}
	
i32_t GetPriority(pID_t pID)
{
	return GetProcessProperty(USE_CURRENT_PROCESS, P_PRIORITY);
}
	
i32_t GetParentPid(i32_t pID)
{
	return GetProcessProperty(pID, P_PARENT);
}
	
i32_t GetUserStack(pID_t pID)
{
	return GetProcessProperty(pID, P_USTACK);
}
	
i32_t GetKernelStack(pID_t pID)
{
	return GetProcessProperty(pID, P_KSTACK);
}
	
i32_t GetMemoryRights(i32_t pID)
{
	return GetProcessProperty(pID, P_MEM_RIGHTS);
}
	
