#include "../lib/blowfish.h"
#include "../lib/error.h"
#include "../lib/ansi.h"

int main(int argc, char *argv[])
{
	setbit(status, ANSI);

	assert(argc >= 2, "too few arguments");
	alert(status, argv[1]);

	return 0;
}
