#include "KernelSe.h"
#include "Lista.h"
#include "Thread.h"
#include "PCB.h"
#include "schedule.h"
#include "Decl.h"
#include "ListaSl.h"

ListaSl* KernelSem::allBlocked = new ListaSl();

KernelSem::KernelSem(Semaphore* mySem, int initValue)
{
	this->mySem = mySem;
	this->blocked = new Lista();
	this->val = initValue;

}

KernelSem::~KernelSem()
{
	delete blocked;
}

int KernelSem::wait(Time maxTimeToWait)
{
	lock();
	if (--val < 0)
		block(maxTimeToWait);
	unlock();
	return Decl::running->isSignaled;
}

void KernelSem::signal()
{
	lock();
	if (val++ < 0)
		deblock();
	unlock();
}

void KernelSem::block(Time maxTimeToWait)
{

	Decl::running->isSignaled = 0;

	blocked->put(Decl::running);

	SetBlockedState(maxTimeToWait);
	Decl::running->state = BLOCKED;

	dispatch();

}

void KernelSem::deblock()
{
	PCB* p = blocked->getFirst();

	SetDeblockedState(p);

	KernelSem::allBlocked->remove(p);

	Scheduler::put(p);
}

void KernelSem::SetBlockedState(Time maxTimeToWait)
{
	if (maxTimeToWait > 0)
		{
			Decl::running->blockedOn = this;
			KernelSem::allBlocked->put(maxTimeToWait, Decl::running);
		}
}

void KernelSem::SetDeblockedState(PCB* p)
{
		p->blockedOn = 0;
		p->isSignaled = 1;
		p->state = READY;
}

