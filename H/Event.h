#ifndef _event_h_
#define _event_h_

#include "IVTEntry.h"

typedef unsigned char IVTNo;
class KernelEv;

class Event
{
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();

protected:
	friend class KernelEv;
	void signal();

private:
	KernelEv* myImpl;

};



#define PREPAREENTRY(ivtno, routineflag)\
	void interrupt newRoutine##ivtno(...);\
	IVTEntry ivtentry##ivtno(ivtno, newRoutine##ivtno);\
	void interrupt newRoutine##ivtno(...)\
	{\
	ivtentry##ivtno.signalAll();\
	if(routineflag)\
	ivtentry##ivtno.oldRoutine();\
	}


#endif

