#ifndef _idle_h_
#define _idle_h_

#include "Thread.h"

class Idle : public Thread
{
	private:
	int id;
public:
	Idle();
	void run();
	PCB* getPcb();



};


#endif




