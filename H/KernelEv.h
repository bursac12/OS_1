#ifndef _kernel_ev_
#define _kernel_ev_

class Event;
class PCB;

class KernelEv
{
protected:
	void block();
	void deblock();

public:
	KernelEv(Event* myEvent, unsigned char ivtNo);
	~KernelEv();

	void wait();
	void signal();

	void setsum(double s);
	double getsum();
	unsigned char* getcap();

private:
	Event* myEvent;
	unsigned char ivtNo;
	int val;
	PCB* owner;
	unsigned char* cap;
	double sum;
};

#endif

