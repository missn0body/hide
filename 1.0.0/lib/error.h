#ifndef hide__error__h
#define hide__error__h

#include "includes.h"
#include "ansi.h"
#include "util.h"

// This static object will hold all of the
// active modes within the program, with 8
// booleans (bits) to be raised or lowered
static flag_t status = 0;

// Array of error messages
const char *errorMes[] =
{
	"too few arguments",
	"unknown option"
};

// Quick mnemonics for indexing the above array.
enum
{
	ARG = 0,
	UNK
};

// This function is not meant to be called directly, unless you
// want to provide a file and line number directly instead of
// nifty GCC extensions.
[[ __noreturn__ ]] void _error(char *file, int line, int index, flag_t *status)
{
        if(test(*status, ANSI))	fprintf(stderr, "%s(%s:%d)%s %s\n", RED, file, line, RESET, errorMes[index]);
        else                    fprintf(stderr, "(%s:%d) %s\n", file, line, errorMes[index]);
	exit(EXIT_FAILURE);
}

// Rather I prefer you call this, unless you can't.
#define error(x)        _error(__FILE__, __LINE__, x, &status)
#define alert(x, ...)   fprintf(stderr, "%s%s%s\n", red_if_color(x), __VA_ARGS__, reset_if_color(x))

#endif
