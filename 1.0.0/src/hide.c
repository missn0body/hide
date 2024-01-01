//#include "../lib/blowfish.h"
#include "../lib/ansi.h"
#include "../lib/salt.h"
#include "../lib/error.h"

int main(int argc, char *argv[])
{
	_Assert(argc >= 2, "too few arguments");
	//blowfish_init("TESTKEY", strlen("TESTKEY"));

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

	// The length of the added salt would be twice the amount of the plaintext,
	// but to protect against low plaintext lengths (2 times 2 minus 1 isn't much),
	// a set length of 5 would be for plaintext lengths lower than 3
	int saltPrefix 	= 6;
	int bufsize 	= strlen(argv[1]);
	int saltLength 	= (bufsize >= 3) ? ((bufsize * 2) - (bufsize / 2)) : 6;

	// To where the initial plaintext will be inputed, plus optional padding
	// (explained later)
	char *buffer = malloc(bufsize);
	// Buffer containing the salt string add-on
	char *salt   = salter(argv[1], saltLength);
	// Final combined ciphertext output
	char *output  = malloc((bufsize + (saltLength + saltPrefix)) + 1);

	// Memory checks
	_Assert(buffer != nullptr, "memory fault");
	_Assert(salt   != nullptr, "memory fault");
	_Assert(output != nullptr, "memory fault");

	strncpy(buffer, argv[1], bufsize);

	// Make a random integer and save it, this will be the index
	// that the plaintext will be inserted into. This random index
	// will also be printed into the string itself
	int plainBase 	= (rand() % (saltLength + saltPrefix)) - (bufsize - 1);
	// Protection against negative values
	int plainIndex 	= (plainBase < 0) ? (plainBase * -1) : plainBase;
	_Assert(plainIndex >= 1, "calculated impossible index, what?");

	// Left padded with zeros, and because of the format, the plaintext
	// within the salt cannot be located past index 9999
	sprintf(output, "%0*d%0*d%s", saltPrefix / 2, plainIndex, saltPrefix / 2, bufsize, salt);

	// Input the plaintext into the middle of the substring
	stirin(output, buffer, plainIndex + saltPrefix);

	// The method of encoding for this app essentially indexes
	// two characters on a single loop, as the blowfish encryption
	// expects two halves of any given data.
	// As to make the entire loop processing easier, the plaintext
	// is padded with a '0' character if its length is odd
	if(strlen(output) % 2 != 0) strcat(output, "0");
	output[strlen(output)] = '\0';
	// Final input to cipher here
	printf("%s\n", output);

	char extract[25], format[7];
	int pos = 0, len = 0;
	// Dynamically making a format string to pass to sscanf, since
	// sscanf does not support variable length widths
	sprintf(format, "%%%dd%%%dd", saltPrefix / 2, saltPrefix / 2);
	sscanf(output, format, &pos, &len);
	// Just proving that I can extract the plaintext out of the salt
	// given the blueprint in the beginning of salt
	strncpy(extract, output + pos + saltPrefix, len);
	printf("%s\n", extract);

	free(buffer);
	free(salt);
	free(output);

	putchar('\n');
	return 0;
}
