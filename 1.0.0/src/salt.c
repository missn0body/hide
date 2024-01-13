#include "../lib/salt.h"

// Based off of the basic design from rot47.net
void rot47(char *base, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(isprint(base[i]))
		{
			base[i] = 33 + ((base[i] + 14) % 94);
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

// Like stirfry, but insertion, unrelated to stirin' a pot
void stirin(char *dest, char *sub, int index)
{
	// Lengths of both strings plus one
	unsigned length = (strlen(dest) + strlen(sub) + 1);
	char *buf = calloc(length, sizeof(char));
	if(buf == nullptr) return;

	// Input the first part, up to where the substring begins
	strncpy(buf, dest, index);
	// So that strcat plays correctly
	buf[index] = '\0';
	// Input substring, then rest of first string
	strcat(buf, sub);
	strcat(buf, dest + index);
	// I'm not actually sure if strcat() inputs a terminator so
	// put this here just in case :)
	buf[length - 1] = '\0';

	// Copy the destination string
	strcpy(dest, buf);
	return;
}

char *saltext(char *base, int width)
{
	// GCC complains about the length of the format string, so
	// lets allocate for the worst case scenario
	char format[28];
        int pos = 0, len = 0;

	// This function assumes that the 'width' variable given
	// is the total prefix length, whats added to the beginning
	// of the 'base'
        sprintf(format, "%%%dd%%%dd", width / 2, width / 2);
	// Dynamically making a format string to pass to sscanf, since
        // sscanf does not support variable length widths
        sscanf(base, format, &pos, &len);

	char *returnValue = malloc(len + 1);
	if(returnValue == nullptr) return nullptr;

        strncpy(returnValue, base + pos + width, len);
	returnValue[len] = '\0';
	return returnValue;
}

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

	// Fill in the rest of the string with random garblely gooks
	// (length + 1) - strlen(returnValue + (half * 2)) being the
	// exact length of string that is currently empty
	char *startingPoint = returnValue + (half * 2);
	for(size_t i = 0; i < (length + 1) - strlen(returnValue + (half * 2)); i++)
	{
		// secret message, mwuhahahaha~
		*(startingPoint + i) = "1noitacavylimaf-reficulfotsen"[i % 13];
	}

	rot47(returnValue + (half * 2), strlen(returnValue + (half * 2)));
	returnValue[length - 1] = '\0';
	return returnValue;
}
