#ifndef hide__util__h
#define hide__util__h

#include "includes.h"

// We're not using "char", just in case there's some
// dystopian future where they changed the definition
// of "char". Might be just bias, but I put more trust
// in stdint.h's typedefs.
typedef uint8_t flag_t;

// These are seperate typedefs that the Blowfish algorithm
// uses quite a lot, so these smaller names save a little time.
typedef uint16_t u16;
typedef uint32_t u32;

// Shorthands for setting bits in a flag typedef
#define setbit(x, y)   	((x) |= (y))
#define unsetbit(x, y) 	((x) &= (~(y)))

// Shorthand for testing a bit in a flag typedef
// e.g. if(test(status, ANSI)) { /*do ANSI stuff*/ }
#define test(x, y)	(((x) & (y)) != 0)

// Only to be used for arrays on the stack
#define nelems(x)	(sizeof(x) / sizeof((x)[0]))

// No XOR swaps here...
inline void swap(u32 *first, u32 *second)
{
	if(first == second) return;

	u32 temp = *first;
	*first = *second;
	*second = temp;
}

#endif
