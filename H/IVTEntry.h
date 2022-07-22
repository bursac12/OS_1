
#ifndef _ivtentry_h_
#define _ivtentry_h_

#include "Decl.h"

class ListaEv;


class IVTEntry
{
public:
	unsigned char IvtNo;
	interPtr oldRoutine;


	IVTEntry(unsigned char IvtNo, interPtr newRoutine);
	~IVTEntry();

	static IVTEntry* entries[256];
	ListaEv* events;

	void signalAll();

	void setNaz(char* n);
	char* getNaz();

private:
	char* nazivr;


};

#endif


