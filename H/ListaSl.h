#ifndef ListaSl_h
#define ListaSl_h

class PCB;
typedef unsigned int Time;

class ListaSl{

public:
	struct Elem{
		Time time;
		PCB* pcb;
		Elem* next;
		Elem(Time t, PCB* pcb){ time = t; this->pcb = pcb; next = 0; }
	};

	Elem *head,*tail;

	
	ListaSl(){head=tail=0;}

	~ListaSl(){

		Elem *tek=head,*stari;
			while (tek) {
				stari= tek;
				tek=tek->next;
				delete stari;
			}
			head=tail=0;
	}

	void put(Time t, PCB* pcb);
	PCB* get();
	void remove(PCB* pcb);

};

#endif
