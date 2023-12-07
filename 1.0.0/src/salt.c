#include "../lib/salt.h"

// Based off of the basic design from rot47.net
void rot47(char *input, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(isprint(input[i]))
		{
			input[i] = 33 + ((input[i] + 14) % 94);
		}
	}
}

// See also: strfry()
char *stirfry(char *base, int length)
{
	char *returnValue = calloc(length + 1, sizeof(char));
	if(returnValue == nullptr) return nullptr;

	for(int i = 0, ri = 0; i < length;)
	{
		// Get a random index (ri = random index)
		ri = rand() % length;
		if(!*(returnValue + ri) && *(base + i))
		{
			// Assign the value then, and only increment
			// if we have a blank index, overwriting is
			// rather unnecessary
			returnValue[ri] = base[i];
			i++;
		}
	}

	returnValue[length - 1] = '\0';
	return returnValue;
}

// TODO: fix bugs with calculating halves of strings
char *salter(char *base, int length)
{
	char *returnValue = calloc(length + 1, sizeof(char));
	char *scramble = stirfry(base, strlen(base));

	if(returnValue == nullptr || scramble == nullptr) return nullptr;

	size_t half = (strlen(scramble) / 2);
	int remain = (strlen(scramble) % 2);

	// Copy over the first half of the scrambled input
	memcpy(returnValue, scramble, half);
	// Second half is a simple ROT13 type cipher shift,
	// specifically ROT47
	char *secondHalf = (scramble + half);
	rot47(secondHalf, strlen(secondHalf));
	memcpy(returnValue + half, secondHalf, half + remain);

	returnValue[length - 1] = '\0';
	return returnValue;
}
