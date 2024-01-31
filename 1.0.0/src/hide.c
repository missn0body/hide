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

void showUsage(void)
{
	printf("hide (%s): a simple Blowfish scramble schtick by anson.\n", VERSION);
        puts("Usage: hide -a (--ansi) -u (--unhide) -h (--help)\n");
        puts("Be warned: the only cipher mode supported as of now is EBC.");
	puts("Use this application with the right data for the right purpose.");
}

int main(int argc, char *argv[])
{
	_Assert(argc >= 2 || argv[1] != nullptr, "too few arguments. try \"--help\"");
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

	printf("%s \"%s\" with key \"%s\"...\n", (test(status, UNHIDE)) ? "decrypting" : "encrypting", input, key);

	// The P and S boxes need to be setup regardless of encryption or decryption
	BLOWFISH_CTX *context = malloc(sizeof(BLOWFISH_CTX));
	_Assert(context != NULL, "memory fault");

	Blowfish_Init(context, (unsigned char *)key, strlen(key));

	// Decrypting is a bit more complicated, sigh
	if(test(status, UNHIDE))
	{
		char buffer[5] = {0};
		u32 first = 0, second = 0;

		// Decryption!
		char *chunk = strtok(input, "-");
		while(chunk != nullptr)
		{
			first =  (u32)(strtoul(chunk, nullptr, 16) >> 32);
			second = (u32) strtoul(chunk, nullptr, 16);

			Blowfish_Decrypt(context, &first, &second);

			expand(first, buffer);
			stripStr(buffer);
			printf("%s", buffer);

			// It's a bit hard to use stripStr() to remove
			// the bad face, so for the moment, we can just
			// stop ourselves from printing it
			if(second != 0x9BADFACE)
			{
				expand(second, buffer);
				stripStr(buffer);
				printf("%s", buffer);
			}

			chunk = strtok(nullptr, "-");
		}

		putchar('\n');
	}
	// Encryption is a little more straightforward
	else
	{
		// Compressing the given string into some length of 32-bit blocks
		u32 compressedInput[128] = {0}, first = 0, second = 0;
		int compLen = compressStr(input, compressedInput);

		// Encryption!
		for(int i = 0; i < compLen; i += 2)
		{
			first = compressedInput[i];
			second = compressedInput[i + 1];

			// Since Blowfish works in pairs, and I don't feel right
			// simply appending a zero, I designated this constant
			// to be appended in the case of the compression function
			// above outputing an uneven amount of 32-bit blocks
			if(second == 0 || (i + 1) >= compLen) second = 0x9BADFACE;

			Blowfish_Encrypt(context, &first, &second);

			// Every 64-bit block is segmented, so that if the output
			// of this program were to be fed back into itself to decrypt,
			// I would have an easier time extracting 32-bit chunks out of
			// strings.
			printf("%08X%08X-\n", first, second);
		}

		putchar('\n');
	}

	// Clean up
	Blowfish_Zero(context);
	free(context);
	return 0;
}
