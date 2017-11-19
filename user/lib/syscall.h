///////////////////////////////////////////////////////////////////////////////////////////////////
/* Header for the System Call interfaces
	syscall.h

	This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
	International License. To view a copy of this license, visit
	http://creativecommons.org/licenses/by-nc-nd/4.0/
	or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

	Also see http://www.bluekernel.com.au

	copyright Paul Cuttler 2017
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SYSCALL_H
#define __SYSCALL_H

#include "../../kernel/policy/types.h"
#include "../../kernel/policy/kernel.h"
#include "../../kernel/mechanism/pc/resources_pc.h"

pID_t Send(pID_t receiver_pID, u32_t *sender_msgB, u32_t length, u32_t timeout);
pID_t Receive(pID_t sender_pID, u32_t *receiver_msgB, u32_t length, u32_t timeout);

pID_t Sleep(pID_t sender_pID, u32_t *receiver_msgB, u32_t length, u32_t timeout);
// this maps straight on to Receive function.

pID_t Timer(u32_t timeout);
// this maps on to Receive function.

int   Schedule(void);
pID_t AddProcess(u32_t priority, pID_t parent_pID, u32_t first_instruction,
				 u32_t user_stack_addr, u32_t kernel_stack_addr,
				 pID_t excepter_pID, pID_t pager_pID);
i32_t RemoveProcess(pID_t pID);
u32_t GetProcess(pID_t pID, u32_t *properties);
int   SetProcess(pID_t pID, int property, u32_t value);

int   AddResource(pID_t pID, u32_t resource_type, u32_t index, u32_t value);
int   RemoveResource(u32_t resource_type, i32_t index);
int   Read8(u32_t portID, void *data);
int   Write8(u32_t portID, u8_t data);
int   Read16(u32_t portID, void *data);
int   Write16(u32_t portID, u16_t data);
int   Read32(u32_t portID, void *data);
int   Write32(u32_t portID, u32_t data);

i32_t AddPage(pID_t pID, u32_t virtual_address, u32_t permissions);
i32_t MapPage(pID_t src_pID, u32_t src_virtual_address,
			  pID_t dst_pID, u32_t dst_virtual_address, u32_t permissions);
i32_t GrantPage(pID_t src_pID, u32_t src_virtual_address,
				pID_t dst_pID, u32_t dst_virtual_address,
				u32_t permissions);
i32_t UnmapPage(pID_t pID, u32_t virtual_address);

#endif

/* END OF FILE */
