#include "IVTEntry.h"
#include <dos.h>
#include "ListaEv.h"
#include "KernelEv.h"
#include "Thread.h"
#include "Decl.h"

IVTEntry* IVTEntry::entries[256];

IVTEntry::IVTEntry(unsigned char IvtNo, interPtr newRoutine)
{
	lock();


	this->IvtNo = IvtNo;
	events = new ListaEv();
	entries[IvtNo] = this;
	nazivr="def intr";
	oldRoutine=0;

#ifndef BCC_BLOCK_IGNORE
	this->oldRoutine = getvect(IvtNo);
	setvect(IvtNo, newRoutine);
#endif

	unlock();
}


IVTEntry::~IVTEntry()
{
	lock();

#ifndef BCC_BLOCK_IGNORE
	setvect(IvtNo, oldRoutine);
#endif

	delete events;
	entries[IvtNo] = 0;

	unlock();
}



void IVTEntry::setNaz(char* n)
{
	nazivr=n;
}

char* IVTEntry::getNaz()
{
	return nazivr;
}
void IVTEntry::signalAll()
{
	for (ListaEv::Elem* tek = events->head; tek != 0; tek = tek->next)
	{
		tek->event->signal();
	}
	dispatch();
}



