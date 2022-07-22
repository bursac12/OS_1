#include "ListaSl.h"
#include "PCB.h"

void ListaSl::put(Time t, PCB* pcb){

	Elem* novi = new Elem(t, pcb);

	if (head == 0){ head = novi; tail = novi; }
	else
		if (head->time > t) {
				head->time -= novi->time;
				novi->next = head;
				head = novi;
			}
		else
		{		for (Elem *tek = head; tek != 0; tek = tek->next){
					if (tek->next == 0){
						tek->next = novi;
						novi->time = novi->time - tek->time;
						tail = novi;
						return;
					}

					if (novi->time - tek->time <= tek->next->time){
						novi->next = tek->next;
						novi->time = novi->time - tek->time;
						novi->next->time -= novi->time;
						tek->next = novi;
						return;
					}
					if (novi->time - tek->time > tek->next->time){
						novi->time -= tek->time;
					}
				}
		}
};

PCB* ListaSl::get(){
	if (head == 0) return 0;

	Elem* pom = head;
	PCB* pcb = head->pcb;

	head->next->time += head->time;
	head = head->next;

	if (head == 0) tail = 0;

	delete pom;
	return pcb;
};

void ListaSl::remove(PCB* p)
{
	Elem* pom = head;

		if (pom == head && pom->pcb == p)
		{
			head->next->time += head->time;
			head = head->next;
			delete pom;
			return;
		}

		while (pom)
		{
			if (pom->next == tail)
			{
				if (pom->next->pcb == p)
				{
					delete tail;
					tail = pom;
					tail->next = 0;

					return;
				}
			}
			if (pom->next->pcb == p && pom->next->next != 0)
			{
				Elem* pom1 = pom->next;
				pom->next->next->time += pom1->time;
				pom->next = pom->next->next;
				delete pom1;

				return;
			}
			pom = pom->next;
		}
}
