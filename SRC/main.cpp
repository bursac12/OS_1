#include "Loader.h"

extern int userMain(int argc, char* argv[]);

void main(int argc, char* argv[])
{
	Loader l;

	l.load();

	userMain(argc, argv);

	l.unload();
}

