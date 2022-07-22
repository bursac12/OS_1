#include "Decl.h"
#include "Thread.h"
#include "Lista.h"


interPtr Decl::oldTimer = 0;
int Decl::zahtevana_promena_konteksta = 0;
int Decl::proteklo_vreme = 0;
PCB* Decl::running = 0;
PCB* Decl::starting = 0;
ID Decl::posId = 0;
Lista* Decl::allPcbs = new Lista();
Idle* Decl::idle = 0;
