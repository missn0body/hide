#ifndef hide__util__h
#define hide__util__h

#include "includes.h"

// We're not using "char", just in case there's some
// dystopian future where they changed the definition
// of "char". Might be just bias, but I put more trust
// in stdint.h's typedefs.
typedef uint8_t flag_t;

// Shorthands for setting bits in a flag typedef
#define setbit(x, y)   	((x) |= (y))
#define unsetbit(x, y) 	((x) &= (~(y)))

// Shorthand for testing a bit in a flag typedef
// e.g. if(test(status, ANSI)) { /*do ANSI stuff*/ }
#define test(x, y)	(((x) & (y)) != 0)

// Only to be used for hardcoded, non-allocated arrays
#define nelems(x)	(sizeof(x) / sizeof((x)[0]))

#endif
