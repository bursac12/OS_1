#ifndef listaev_h
#define listaev_h

class KernelEv;

class ListaEv
{
public:
	struct Elem
	{
		KernelEv* event;
		Elem* next;
		Elem(KernelEv* e){ event = e; next = 0; }
	};

	Elem* head;
	Elem* tail;

	ListaEv()
	{
		head = 0;
		tail = 0;
	}

	~ListaEv();

	void put(KernelEv* e);
	KernelEv* get();
};

#endif
