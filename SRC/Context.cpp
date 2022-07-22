#include "context.h"
#include "PCB.h"
#include <dos.h>


Context::Context(StackSize stackSize)
{
	this->stackSize=stackSize;
}

Context::~Context()
{
	delete [] stack;
}

void Context::create_stack()
{
	stack = new unsigned[stackSize];
	stack[stackSize - 1] = 0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 2] = FP_SEG(PCB::wrapper);
	stack[stackSize - 3] = FP_OFF(PCB::wrapper);
	this->ss = FP_SEG(&stack[stackSize - 12]);
	this->sp = FP_OFF(&stack[stackSize - 12]);
	this->bp = FP_OFF(&stack[stackSize - 12]);
#endif
}
