#ifndef hide__error__h
#define hide__error__h

#include "includes.h"
#include "ansi.h"
#include "util.h"

// This static object will hold all of the
// active modes within the program, with 8
// booleans (bits) to be raised or lowered
static flag_t status = 0;

// This function is not meant to be called directly, unless you
// want to provide a file and line number directly instead of
// nifty GCC extensions.
[[ __noreturn__ ]] void _error(char *file, int line, const char *mes, flag_t *status)
{
        if(test(*status, ANSI))	fprintf(stderr, "%s(%s:%d)%s %s\n", RED, file, line, RESET, mes);
        else                    fprintf(stderr, "(%s:%d) %s\n", file, line, mes);
	exit(EXIT_FAILURE);
}

// Rather I prefer you call this, unless you can't.
#define _Error(x)	_error(__FILE__, __LINE__, x, &status)
#define _Alert(x, ...)  fprintf(stderr, "%s%s%s\n", red_if_color(x), __VA_ARGS__, reset_if_color(x))

// My own assert function, because assert.h was too much for me
#define _Assert(x, y)	if(!(x)) { _Error(y); }

#endif
