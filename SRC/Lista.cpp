#include "Lista.h"
#include "PCB.h"

void Lista::put(PCB* pcb)
{
	Elem* novi = new Elem(pcb);
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

PCB* Lista::getFirst()
{
	if (head == 0)
		return 0;

	PCB* pcb = head->pcb;
	Elem* pom = head;

	head = head->next;
	if (head == 0)
		tail = 0;

	delete pom;
	return pcb;
}

PCB* Lista::findById(int id)
{
	PCB* pcb = 0;
	for (Elem* tek = head; tek; tek = tek->next)
	{
		if ( id == tek->pcb->getId())
		{
			pcb = tek->pcb;
			break;
		}
	}
	return pcb;
}

void Lista::remove(PCB* p)
{
	Elem* tek = head, *pret=0,*stari=0;

	while (tek)
		if (tek->pcb->getId() != p->getId()){
		pret = tek;
		tek = tek->next;
		}
		else
		{
			stari = tek;
			tek = tek->next;
			if (!pret) head = tek;
			else pret->next = tek;
			delete stari;
			break;
		}
}
