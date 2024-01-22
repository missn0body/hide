/*
	hide.c:  main function for the "hide" utility. Contains code
		 related to "blowfish_test.c" as written by Paul Kocher.
		 The notice below belongs to "blowfish_test.c"

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
*/

#include "../lib/blowfish.h"

int main(int argc, char *argv[])
{
	if(argc < 2 || !*argv[1]) return -1;

	/*
	// BLOWFISH ENCRYPT, DECRYPT, AND ZERO TESTS

	u32 L = 1, R = 2;
  	BLOWFISH_CTX *ctx = malloc(sizeof(BLOWFISH_CTX));
	if(ctx == nullptr) return -1;

  	Blowfish_Init(ctx, (unsigned char*)"TESTKEY", 7);
  	Blowfish_Encrypt(ctx, &L, &R);
  	printf("%08X %08X\n", L, R);

	if (L == 0xDF333FD2L && R == 0x30A71BB4L) printf("Test encryption OK.\n");
  	else					  printf("Test encryption failed.\n");

	Blowfish_Decrypt(ctx, &L, &R);

  	if (L == 1 && R == 2) printf("Test decryption OK.\n");
  	else 		      printf("Test decryption failed.\n");

	Blowfish_Zero(ctx);
	free(ctx);
	*/

	// COMPRESS STRING AND EXPAND STRING TESTS
	u32 comp[10];
	int end = compressStr(argv[1], comp);

	for(int i = 0; i < end; i++)
	{
		printf("%08X\n", comp[i]);
	}

	char exp[41];
	expandStr(comp, 10, exp);

	printf("%s\n", exp);

	return 0;
}
