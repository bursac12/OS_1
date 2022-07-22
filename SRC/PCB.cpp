#include "PCB.h"
#include <dos.h>
#include "Context.h"
#include "KernelSe.h"
#include "Semaphor.h"
#include "Decl.h"
#include "ListaSl.h"
#include "Lista.h"
#include "SCHEDULE.H"
#include "Idle.h"



PCB::PCB(StackSize stackSize, Time timeSlice, Thread* myThread)
{
	context= new Context(stackSize);
	id = ++Decl::posId;
	this->timeSlice = timeSlice;
	this->timeToSleep=0;
	state=CREATED;
	this->myThread = myThread;
	semWaitToComplete = new Semaphore(0);
	this->context->stack = 0;
	this->capt="STVORENO";
	Decl::allPcbs->put(this);
	isSignaled = 0;
	blockedOn = 0;
	naz="default";

}

PCB::~PCB()
{
	delete context;
	delete semWaitToComplete;
}


Thread* PCB::getMyThread()
{
	return myThread;
}


void PCB::setcapt(char *c)
{
	capt=c;
};

char* PCB::getcapt()
{
	return capt;
};




int PCB::getId(){ return id; }



void PCB::wrapper()
{
	Decl::running->myThread->run();

	lock();
	while (Decl::running->semWaitToComplete->val() < 0)
		Decl::running->semWaitToComplete->signal();

	Decl::running->state = DONE;
	dispatch();


}


void interrupt PCB::newTimer(...)
{
	if (Decl::zahtevana_promena_konteksta == 0)
	{

		Decl::proteklo_vreme++;
		Decl::oldTimer();
		tick();


		if (KernelSem::allBlocked->head != 0)
		{
			KernelSem::allBlocked->head->time--;
			while (KernelSem::allBlocked->head != 0 && KernelSem::allBlocked->head->time == 0)
			{
				PCB* pcb = KernelSem::allBlocked->get();
				pcb->state = READY;
				pcb->blockedOn->blocked->remove(pcb);
				pcb->blockedOn->incval();
				pcb->isSignaled = 0;
				Scheduler::put(pcb);
			}
		}
	}


	if (Decl::zahtevana_promena_konteksta == 1 || (Decl::running->timeSlice == Decl::proteklo_vreme && Decl::running->timeSlice > 0))
	{

#ifndef BCC_BLOCK_IGNORE
		Decl::running->context->bp = _BP;
		Decl::running->context->sp = _SP;
		Decl::running->context->ss = _SS;
#endif

		if (Decl::running->state == READY && Decl::running != Decl::idle->getPcb())
			Scheduler::put(Decl::running);


		Decl::running = Scheduler::get();

		if (Decl::running == 0)
		{
			Decl::running = Decl::idle->getPcb();
		}

#ifndef BCC_BLOCK_IGNORE
		_BP = Decl::running->context->bp;
		_SP = Decl::running->context->sp;
		_SS = Decl::running->context->ss;
#endif

		Decl::proteklo_vreme = 0;
		Decl::zahtevana_promena_konteksta = 0;
	}
}

