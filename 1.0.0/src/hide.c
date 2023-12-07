#include "../lib/blowfish.h"
#include "../lib/ansi.h"
#include "../lib/salt.h"
#include "../lib/error.h"

int main(int argc, char *argv[])
{
	_Assert(argc >= 2, "too few arguments");
	blowfish_init("TESTKEY", strlen("TESTKEY"));

	/*
	int bufsize = (strlen(argv[1]) % 2 == 0) ? strlen(argv[1]) + 1 : strlen(argv[1]) + 2;
	char *buffer = malloc(bufsize);
	_Assert(buffer != nullptr, "memory fault");

	strncpy(buffer, argv[1], bufsize);
	if(strlen(argv[1]) % 2 != 0) buffer[bufsize - 2] = '0';
	buffer[bufsize - 1] = '\0';

	for(size_t i = 0; i < (size_t)(bufsize - 1); i += 2)
	{
		u32 L = buffer[i];
		u32 R = buffer[i + 1];

		blowfish_encrypt(&L, &R);
		printf("%c%c", (char)L, (char)R);
		//blowfish_decrypt(&L, &R);
		//printf("%c %c\n", (char)L, (char)R);
	}

	putchar('\n');
	free(buffer);
	*/

	size_t argvLen = strlen(argv[1]);
	bool isEven = (argvLen % 2 == 0);

	// The length of the added salt would be twice the amount of the plaintext,
	// but to protect against low plaintext lengths (2 times 2 minus 1 isn't much),
	// a set length of 5 would be for plaintext lengths lower than 3
	int saltPrefix 	= 4;
	int saltLength 	= (argvLen >= 3) ? ((argvLen * 2) - 1) 	: 6;
	int bufsize 	= (isEven) 	 ? (argvLen + 1) 	: (argvLen + 2);

	// To where the initial plaintext will be inputed, plus optional padding
	// (explained later)
	char *buffer = malloc(bufsize);
	// Buffer containing the salt string add-on
	char *salt   = salter(argv[1], saltLength + saltPrefix);
	// Final combined ciphertext output
	char *output  = malloc((bufsize + (saltLength + saltPrefix)) + 1);

	// Memory checks
	_Assert(buffer != nullptr, "memory fault");
	_Assert(salt   != nullptr, "memory fault");
	_Assert(output != nullptr, "memory fault");

	// The method of encoding for this app essentially indexes
	// two characters on a single loop, as the blowfish encryption
	// expects two halves of any given data.
	// As to make the entire loop processing easier, the plaintext
	// is padded with a '0' character if its length is odd,
	strncpy(buffer, argv[1], bufsize);
	if(!isEven) buffer[bufsize - 2] = '0';
	buffer[bufsize - 1] = '\0';

	printf("- %s\n", buffer);
	printf("] %s\n", salt);
	printf(": %s\n", output);

	free(buffer);
	free(salt);
	free(output);

	putchar('\n');
	return 0;
}
