#include "../lib/blowfish.h"
#include "../lib/ansi.h"

int main(int argc, char *argv[])
{
	//_Assert(argc >= 2, "too few arguments");

	u32 originalL = (u32)'A', originalR = (u32)'A', L = originalL, R = originalR;
	blowfish_init("TESTKEY", strlen("TESTKEY"));

	blowfish_encrypt(&L, &R);
	printf("%08x %08x\n", L, R);
	printf("Test encryption %s\n", (L == 0xDF333FD2L && R == 0x30A71BB4L) ? "okay" : "failed");

	blowfish_decrypt(&L, &R);
	printf("%08x %08x\n", L, R);
        printf("Test decryption %s\n", (L == originalL && R == originalR) ? "okay" : "failed");
	return 0;
}
