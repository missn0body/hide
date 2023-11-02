#include "../lib/blowfish.h"

void blowfish_encrypt(u32 *left, u32 *right)
{
	/*
		Every round consists of:
		- XOR left half of data with an (i)ndex from the perumtation table
		- use the XOR'd left half as input for Blowfish's "F" function
		  (nicknamed feistel here, for the basic cypher structure Blowfish
		  is built from)
		- XOR "F"'s output into the right half of the data
		- Then swap the two halves
	*/

	for(short i = 0; i < ENCRYPT_ROUNDS; i++)
	{
		*left 	= *left ^ permbox[i];
		*right 	= feistel(*left) ^ *right;
		swap(left, right);
	}

	swap(left, right);
	*right 	= *right ^ permbox[16];
	*left 	= *left ^ permbox[17];
}

void blowfish_decrypt(u32 *left, u32 *right)
{
	// Much like the algorithm for encryption but backwards

	// See this for why this works:
	// https://youtu.be/FGhj3CGxl8I?si=TgXFGX27GrwPcsXN

	for(short i = DECRYPT_ROUNDS; i > 1; i--)
	{
		*left 	= *left ^ permbox[i];
		*right 	= feistel(*left) ^ *right;
		swap(left, right);
	}

	swap(left, right);
	*right 	= *right ^ permbox[1];
	*left 	= *left ^ permbox[0];
}


void blowfish_init(char *key, int keylen)
{
	// (User's) sanity check
	if(key != nullptr || strlen(key) != 0 || strcmp(key, "") != 0) return;

	u32 keypart = 0x00, leftInput = 0x00, rightInput = 0x00;
	// Initializing the permutation box (permbox) with the given
	// key. If you want to change keys, then call this function
	// again with a different key
	for(short i = 0, keyindex = 0; i < PERMBOX_COUNT; i++)
	{
		keypart = 0x00;
		for(short j = 0; j < 4; j++)
		{
			keypart	 = (keypart << 8) | (u32) key[keyindex];
			keyindex = (keyindex + 1) % keylen;
		}

		permbox[i] = permbox[i] ^ keypart;
	}

	// Blowfish key expansion for permutation box
	for(short i = 0; i < PERMBOX_COUNT; i += 2)
	{
		blowfish_encrypt(&leftInput, &rightInput);
		permbox[i]     = leftInput;
		permbox[i + 1] = rightInput;
	}

	// Blowfish key expansion for substitution box
	for(short i = 0; i < SUBBOX_FIRST_DIM; i++)
	{
		for(short j = 0; j < SUBBOX_SECOND_DIM; j += 2)
		{
			blowfish_encrypt(&leftInput, &rightInput);
			subbox[i][j] 	 = leftInput;
			subbox[i][j + 1] = rightInput;
		}
	}

	return;
}
