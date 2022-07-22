#ifndef _context_h_
#define _context_h_

#include "Thread.h"

class Context {

public:
		Context(StackSize stackSize);
		~Context();

		StackSize stackSize;
		unsigned* stack;
		void create_stack();

		unsigned sp;
		unsigned ss;
		unsigned bp;

};

#endif
