#include "Loader.h"
#include <dos.h>
#include "Idle.h"
#include "PCB.h"
#include "Decl.h"

void Loader::load()
{
#ifndef BCC_BLOCK_IGNORE
		Decl::oldTimer = getvect(8);
		setvect(8, PCB::newTimer);
#endif

		Decl::idle = new Idle();
		Decl::running = new PCB(0, 0, 0);
}

void Loader::unload()
{
#ifndef BCC_BLOCK_IGNORE
		setvect(8, Decl::oldTimer);
#endif
}

