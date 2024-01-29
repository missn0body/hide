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
#include "../lib/ansi.h"
#include "../lib/error.h"
#include "../lib/util.h"

const char *VERSION = "1.0.0";

#define UNHIDE	(1 << 5)
#define HEXMODE (1 << 6)

void showUsage(void)
{
	printf("hide (%s): a simple blowfish scramble schtick by anson.\n", VERSION);
        puts("Usage: hide -a (--ansi) -u (--unhide) -x (--hex) -h (--help)\n");
        puts("Be warned: the only cipher mode supported as of now is EBC.");
	puts("Use this application with the right data for the right purpose.");
}

int main(int argc, char *argv[])
{
	_Assert(argc >= 2 || argv[1] != nullptr, "too few arguments. try \"--help\"");

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

	/*
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

	stripStr(exp);
	printf("%s\n", exp);
	*/

	char input[256] = {0}, key[56] = {0}, *programName = argv[0];
	int c;

	// Iterate through all arguments sent, character by character
        while(--argc > 0 && (*++argv)[0] != '\0')
        {
		if((*argv)[0] != '-')
		{
			if(key[0] != '\0')
			{
				_NoteArg(programName, "discarded program input", *argv);
				continue;
			}

			strncpy((input[0] == '\0') ? input : key, *argv, (input[0] == '\0') ? sizeof(input) : sizeof(key));
		}

		if((*argv)[0] == '-')
		{
	                // If there's another dash, then it's a long option.
	                // Move the pointer up 2 places and compare the word itself.
	                if((*argv)[1] == '-')
	                {
	                        // Using continue statements here so that the user
	                        // can use both single character and long options
	                        // simultaniously, and the loop can test both.
	                        if(strcmp((*argv) + 2, "help")    == 0) { showUsage(); exit(EXIT_SUCCESS);   }
				if(strcmp((*argv) + 2, "hex") 	  == 0) { setbit(status, HEXMODE); continue; }
				if(strcmp((*argv) + 2, "unhide")  == 0) { setbit(status, UNHIDE);  continue; }
	                        if(strcmp((*argv) + 2, "ansi")    == 0) { setbit(status, ANSI);    continue; }
	                }
	                while((c = *++argv[0]))
	                {
	                        // Single character option testing here.
	                        switch(c)
	                        {
	                                case 'h': showUsage(); exit(EXIT_SUCCESS);
					case 'u': setbit(status, UNHIDE);  break;
					case 'x': setbit(status, HEXMODE); break;
	                                case 'a': setbit(status, ANSI);    break;
	                                // This error flag can either be set by a
	                                // completely unrelated character inputted,
	                                // or you managed to put -option instead of
	                                // --option.
	                                default : _Error("unknown option. try \"--help\""); exit(EXIT_FAILURE);
	                        }
	                }

			continue;
		}
        }

	_Assert(input[0] != '\0', "no plaintext recieved");
	_Assert(key[0] != '\0', "no key recieved");

	printf("encrypting \"%s\" with key \"%s\"...\n", input, key);

	// Compressing the given string into some length of 32-bit blocks
	u32 compressedInput[128] = {0}, first = 0, second = 0;
	int compLen = compressStr(input, compressedInput);

	// Encryption!
	BLOWFISH_CTX *context = malloc(sizeof(BLOWFISH_CTX));
	_Assert(context != NULL, "memory fault");

	Blowfish_Init(context, (unsigned char *)key, strlen(key));
	for(int i = 0; i < compLen; i += 2)
	{
		first = compressedInput[i];
		second = compressedInput[i + 1];

		if(second == 0 || (i + 1) >= compLen) second = 0x9BADFACE;

		Blowfish_Encrypt(context, &first, &second);

		if(test(status, HEXMODE)) 	printf("%X %X", first, second);
		else 				printf("%u %u", first, second);
	}

	putchar('\n');

	// Clean up
	Blowfish_Zero(context);
	free(context);
	return 0;
}
