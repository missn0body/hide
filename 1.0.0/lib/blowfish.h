#ifndef hide__blowfish__h
#define hide__blowfish__h

/*
	blowfish.h:  Header file for blowfish.c

	Copyright (C) 1997 by Paul Kocher

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.
	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

	See blowfish.c for more information about this file.
*/

#include "includes.h"
#include "util.h"

/*
	Paul Kocher's code, along with Blowfish in general, was originally meant for
	32-bit systems. Bruce Schneier's reference C code even includes old DOS headers.
	Both Kocher and Schneier used the 'unsigned long' data type for holding 32-bit
	data, and while those types are ensured to be at least 32-bit, it is still
	implementation-defined. using stdint.h typedefs makes the compiler play nice,
	and also clears up any vaugeness.
*/

typedef struct
{
	u32 P[16 + 2];
	u32 S[4][256];

} BLOWFISH_CTX;

// Blowfish functions
void 	Blowfish_Init		(BLOWFISH_CTX *ctx, unsigned char *key, int keyLen);
void 	Blowfish_Encrypt	(BLOWFISH_CTX *ctx, u32 *xl, u32 *xr);
void 	Blowfish_Decrypt	(BLOWFISH_CTX *ctx, u32 *xl, u32 *xr);
void 	Blowfish_Zero		(BLOWFISH_CTX *ctx);

// Text encoding/decoding functions
void	compress		(unsigned char *input, u32* buffer);
void   	expand			(u32 input, char *buffer);
int     compressStr		(char *input, u32 *buffer);
void	expandStr		(u32 *input, int length, char *buffer);

#endif
