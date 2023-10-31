#include "../lib/includes.h"
#include "../lib/ansi.h"
#include "../lib/error.h"
#include "../lib/util.h"

int main(int argc, char *argv[])
{
	setbit(status, ANSI);

	if(argc < 2 || !*argv[1]) error(ARG);
	else alert(status, argv[1]);

	return 0;
}
