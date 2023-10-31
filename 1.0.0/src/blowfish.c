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
	*left 	= *left ^ permbox[16];
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


void blowfish_init(char *input)
{
	// TODO: actually finish this
	return;
}
