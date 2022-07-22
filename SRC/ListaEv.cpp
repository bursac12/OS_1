#include "ListaEv.h"

ListaEv::~ListaEv(){
	Elem *tek=head,*stari;
		while (tek) {
			stari= tek;
			tek=tek->next;
			delete stari;
		}
		head=tail=0;

}

void ListaEv::put(KernelEv* e)
{
	Elem* novi = new Elem(e);
	if (head == 0)
	{ 
		head = tail = novi;
	}
	else 
	{ 
		tail->next = novi;
		tail = novi;
	}
}

KernelEv* ListaEv::get()
{
	if (head == 0) return 0;

	Elem* pom = head;
	KernelEv* e = head->event;


	head = head->next;
	if (head == 0)	tail = 0;

	delete pom;
	return e;
}
