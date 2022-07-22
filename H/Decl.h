#ifndef _decl_h_
#define _decl_h_


#define CREATED 0
#define READY 1
#define BLOCKED 2
#define DONE 3

typedef void interrupt(*interPtr)(...);

#define lock() { asm pushf; asm cli; }
#define unlock() { asm popf; }

class PCB;
class Lista;
class Idle;

class Decl
{
public:

	static int posId;

	static PCB* running;
	static PCB* starting;
	static Idle* idle;

	static int zahtevana_promena_konteksta;
	static int proteklo_vreme;

	static interPtr oldTimer;

	static Lista* allPcbs;

};




#endif
