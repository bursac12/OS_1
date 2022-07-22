#ifndef pcb_h
#define pcb_h

#include "Thread.h"

class Semaphore;
class ListaSl;
class Lista;
class KernelSem;
class Context;


extern void tick();

class PCB{
public:
	Time timeSlice;
	Context* context;
	unsigned char state;
    unsigned int timeToSleep;
    char* naz;
    int isSignaled;
	KernelSem* blockedOn;
	Semaphore* semWaitToComplete;


	PCB(StackSize stackSize, Time timeSlice, Thread* myThread);
	~PCB();


	static void wrapper();
	static void interrupt newTimer(...);


	void setcapt(char *c);
	char* getcapt();
	Thread* getMyThread();
	int getId();

	friend class Thread;
	
private:
	Thread* myThread;
	ID id;
	char *capt;
};

#endif

