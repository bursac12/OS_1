#include "KernelEv.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "Decl.h"
#include "IVTEntry.h"
#include "ListaEv.h"

KernelEv::KernelEv(Event* myEvent, unsigned char ivtNo)
{
	this->val = 0;
	this->sum=0;
	this->ivtNo = ivtNo;
	this->myEvent=myEvent;
	this->cap="usao sam sada";
	owner = Decl::running;
	if (IVTEntry::entries[ivtNo])
		IVTEntry::entries[ivtNo]->events->put(this);
}



KernelEv::~KernelEv()
{
	
}

void KernelEv::wait()
{
	if (owner != Decl::running)
		return;

	lock();
	if (--val < 0)
		block();
	unlock();
}

void KernelEv::signal()
{
	lock();
	if (val++ < 0)
		deblock();
	unlock();
}

void KernelEv::block()
{
	owner->state = BLOCKED;
	dispatch();
}

void KernelEv::deblock()
{
	owner->state = READY;
	Scheduler::put(owner);
}

void KernelEv::setsum(double s)
{
	sum=s;
}

double KernelEv::getsum()
{
	return sum;
}

unsigned char* KernelEv::getcap()
{
	return cap;
}
