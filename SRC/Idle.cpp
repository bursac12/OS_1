#include "Idle.h"



Idle::Idle() : Thread(256, 2)
{
	start();
	id=this->getId();
}

PCB* Idle::getPcb()
{
	return myPCB;
}

void Idle::run()
{
	while (1){};
}
