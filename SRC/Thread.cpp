#include "Thread.h"
#include "pcb.h"
#include "SCHEDULE.H"
#include "Idle.h"
#include "Decl.h"
#include "Semaphor.h"
#include "ListaSl.h"
#include "Lista.h"
#include "Context.h"

Thread::Thread(StackSize stackSize, Time timeSlice)
{
	myPCB = new PCB(stackSize, timeSlice, this);
}

Thread::~Thread()
{
	waitToComplete();
	delete myPCB;
}

void Thread::start()
{
	myPCB->context->create_stack();
	myPCB->state = READY;

	if ( Decl::idle->getPcb() != myPCB )
	{
		Scheduler::put(myPCB);
	}
}

ID Thread::getId()
{
	return myPCB->getId();
}

ID Thread::getRunningId()
{
	return Decl::running->getId();
}

Thread* Thread::getThreadById(ID id)
{
	PCB* pcb = Decl::allPcbs->findById(id);
	return pcb != 0 ? pcb->getMyThread() : 0;
}

void dispatch()
{
	lock();
	Decl::zahtevana_promena_konteksta = 1;
	PCB::newTimer();
	unlock();
}


void Thread::waitToComplete()
{

	if (this->myPCB->state != DONE && this->myPCB->state != CREATED)
			if (this->myPCB != Decl::starting)
				if (this->myPCB->myThread != Decl::idle)
						this->myPCB->semWaitToComplete->wait(0);

}
