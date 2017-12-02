///////////////////////////////////////////////////////////////////////////////////////////////////
/* System Call Interfaces
	syscall.c

	This provides convenient means of calling the kernel's system call interfaces.

	This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
	International License. To view a copy of this license, visit
	http://creativecommons.org/licenses/by-nc-nd/4.0/
	or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

	Also see http://www.bluekernel.com.au

	copyright Paul Cuttler 2017
 */
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "syscall.h"

pID_t Send(pID_t receiver_pID, u32_t *sender_msgB, u32_t length, u32_t timeout)
{
	/* function is started with:
	push   %ebp
	mov    %esp,%ebp */

	// push args before call gate, in reverse order
	// eg push [ebp+8] // for first arg, dest
	// push [ebp+12] // 2nd arg
	// push [ebp+16]
	asm (
		"push 20(%ebp)		\n\t"
		"push 16(%ebp)		\n\t"
		"push 12(%ebp)		\n\t"
		"push 8(%ebp)		\n\t"
		"lcall $0x28,$0	\n\t" // this is a proper call gate.
		"add $16, %esp\n\t"
		"mov %ebp,%esp		\n\t"
	);
	/*return value; The end of a function automatically generates the following:
	pop %ebp
	ret
	using: return 0; or so actually puts 0 in eax and overWrites value returned
	from system call.*/
}

pID_t Receive(pID_t sender_pID, u32_t *receiver_msgB, u32_t length, u32_t timeout)
{
	asm (
		"push 20(%ebp)		\n\t"
		"push 16(%ebp)		\n\t"
		"push 12(%ebp)		\n\t"
		"push 8(%ebp)		\n\t"
		"lcall $0x30,$0x0	\n\t"
		"add $16,%esp		\n\t"
		"mov %ebp,%esp		\n\t"
		);
}

pID_t Sleep(pID_t sender_pID, u32_t *receiver_msgB, u32_t length, u32_t timeout)
{
	return Receive(sender_pID, receiver_msgB, length, timeout);
}

pID_t Timer(u32_t timeout)
{
	u32_t buffer = 0;
	return Receive(CLOCK_INTERRUPT, &buffer, 0, timeout);
	// receive from clock with 0 length message and timeout.
}

int Schedule(void)
{
	asm (
		"lcall  $0x38,$0x0\n\t"
		"mov %ebp,%esp\n\t"
		);
}

pID_t AddProcess(u32_t priority, pID_t parent_pID, u32_t first_instruction,
				 u32_t user_stack_addr, u32_t kernel_stack_addr,
				 pID_t excepter_pID, pID_t pager_pID)
{
	asm(
		"push 32(%ebp)\n\t"
		"push 28(%ebp)\n\t"
		"push 24(%ebp)\n\t"
		"push 20(%ebp)\n\t"
		"push 16(%ebp)\n\t"
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall  $0x40,$0x0\n\t"
		"add $28, %esp\n\t"
		"mov %ebp,%esp\n\t"
		);
}

i32_t RemoveProcess(pID_t pID)
{
	asm(
		"push 8(%ebp)\n\t"
		"lcall  $0x48,$0x0\n\t"
		"add $4, %esp\n\t"
		"mov %ebp,%esp\n\t"
		);
}

u32_t GetProcess(pID_t pID, u32_t *properties)
{
	asm(
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall  $0x50,$0x0\n\t"
		"add $8, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

int SetProcess(pID_t pID, int property, u32_t value)
{
	asm(
		"push 16(%ebp)\n\t"
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall  $0x58,$0x0\n\t"
		"add $12, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

int AddResource(pID_t pID, u32_t resource_type, u32_t index, u32_t value)
{
	asm(
		"push 20(%ebp)\n\t"
		"push 16(%ebp)\n\t"
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall $0x60,$0x0\n\t"
		"add $16, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

int RemoveResource(u32_t resource_type, i32_t index)
{
	asm(
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall  $0x68,$0x0\n\t"
		"add $8, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

// Read/Write Port Functions - map to Send/Receive /////////////////////

int Read8(u32_t portID, void *data)
{
	return Receive(portID, data, DATA8, 0);
}

int Write8(u32_t portID, u8_t data)
{
	return Send(portID, (u32_t*)&data, DATA8, 0);
}

int Read16(u32_t portID, void *data)
{
	return Receive(portID, data, DATA16, 0);
}

int Write16(u32_t portID, u16_t data)
{
	return Send(portID, (u32_t*)&data, DATA16, 0);
}

int Read32(u32_t portID, void *data)
{
	return Receive(portID, data, DATA32, 0);
}

int Write32(u32_t portID, u32_t data)
{
	return Send(portID, &data, DATA32, 0);
}

// Memory Functions ////////////////////////////////////////////////////

i32_t AddPage(pID_t pID, u32_t virtual_address, u32_t permissions)
{
	asm(
		"push 16(%ebp)\n\t"
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall $0x70,$0x0\n\t"
		"add $12, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

i32_t MapPage(pID_t src_pID, u32_t src_virtual_address, pID_t dst_pID, u32_t dst_virtual_address,
			  u32_t permissions)
{
	asm(
		"push 24(%ebp)\n\t"
		"push 20(%ebp)\n\t"
		"push 16(%ebp)\n\t"
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall $0x78,$0x0\n\t"
		"add $20, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

i32_t GrantPage(pID_t src_pID, u32_t src_virtual_address, pID_t dst_pID, u32_t dst_virtual_address,
				u32_t permissions)
{
	asm(
		"push 24(%ebp)\n\t"
		"push 20(%ebp)\n\t"
		"push 16(%ebp)\n\t"
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall $0x80,$0x0\n\t"
		"add $20, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

i32_t UnmapPage(pID_t pID, u32_t virtual_address)
{
	asm(
		"push 12(%ebp)\n\t"
		"push 8(%ebp)\n\t"
		"lcall $0x88,$0x0\n\t"
		"add $8, %esp\n\t"
		"mov %ebp,%esp\n\t"
	);
}

/* END OF FILE */
