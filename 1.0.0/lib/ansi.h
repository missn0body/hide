#ifndef hide__ansi__h
#define hide__ansi__h

#include "util.h"

// Set the last bit on, which will be used when
// checking for ANSI mode
#define ANSI		(1 << 7)

// ANSI escape codes, to use for color output, cause
// I quite like colors in my terminal :)
#define RED             "\033[30;101m"
#define BLUE            "\033[34m"
#define GREEN           "\033[32m"
#define RESET           "\033[0m"

// Macro shorthands, for inserting as a string variable
// into a printf-like statment
// e.g. printf("%s%s%s", red_if_color(status), "whatever", reset_if_color(status))
#define green_if_color(x)	(test((x), ANSI) ? GREEN: "")
#define red_if_color(x)		(test((x), ANSI) ? RED 	: "")
#define blue_if_color(x)	(test((x), ANSI) ? BLUE : "")
#define reset_if_color(x)	(test((x), ANSI) ? RESET: "")

#endif
