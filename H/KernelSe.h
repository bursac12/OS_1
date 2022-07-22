#ifndef _kernelsem_h_ 
#define _kernelsem_h_ 

#include "Semaphor.h"
class Lista;
class ListaSl;
class PCB;




class KernelSem
{
public:


	Lista* blocked;
	static ListaSl* allBlocked;

	KernelSem(Semaphore* mySem, int initValue = 1);
	~KernelSem();

	int wait(Time maxTimeToWait);
	void signal();
	int value() { return val; }
	int incval() { val+=1; return val; }
	int decval() { val-=1; return val; }




protected:
	
	void block(Time maxTimeToWait);
	void deblock();
	void SetBlockedState(Time maxTimeToWait);
	void SetDeblockedState(PCB* p);
private:

	int val;
	Semaphore* mySem;
};




#endif
