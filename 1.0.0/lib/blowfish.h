#ifndef hide__blowfish__h
#define hide__blowfish__h

/*
	Functions and algorithms involving the Blowfish
	cypher originally created and released into the
	public domain by Bruce Schineder in 1993
*/

#include "includes.h"

#define SUBBOX_FIRST_DIM	4
#define SUBBOX_SECOND_DIM	256
#define PERMBOX_COUNT 		18

#define ENCRYPT_ROUNDS		16
#define DECRYPT_ROUNDS		17

// For less complicated-looking code
typedef uint32_t u32;

static u32 subbox[SUBBOX_FIRST_DIM][SUBBOX_SECOND_DIM] = {};
static u32 permbox[PERMBOX_COUNT] = {};

static inline void swap(u32 *x, u32 *y)
{
	u32 buf = *x;
	*x = *y;
	*y = buf;
}

// Splits the 32-bit input into 8-bit quadrants used
// to index the s-box (substitution box). The s-box
// accepts 8-bit input and returns 32-bit output
// (it is essentially a lookup table, after all)
static inline u32 feistel(u32 input)
{
	u32 temp = subbox[0][input >> 24] + subbox[1][input >> 16 & 0xFF];
	return (temp ^ subbox[2][input >> 8 & 0xFF]) + subbox[3][input & 0xFF];
}

void blowfish_encrypt	(u32 *left, u32 *right);
void blowfish_decrypt	(u32 *left, u32 *right);
void blowfish_init	(char *key);

#endif
