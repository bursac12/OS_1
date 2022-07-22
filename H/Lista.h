#ifndef lista_h
#define lista_h

class PCB;

class Lista
{
	struct Elem
	{
		PCB* pcb;
		Elem* next;
		Elem(PCB* p){ pcb = p; next = 0;}
	};

	Elem* head;
	Elem* tail;

public:

	Lista()	{head = 0; tail = 0;}

	~Lista()
	{
		Elem *tek=head,*stari;
		while (tek)
		{
			stari= tek;
			tek=tek->next;
			delete stari;
		}
		head=tail=0;
	}

	void put(PCB* pcb);
	PCB* getFirst();
	PCB* findById(int id);
	void remove(PCB* pcb);
};

#endif
