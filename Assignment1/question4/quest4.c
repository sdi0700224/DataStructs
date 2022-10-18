#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "puzzlerec.h"


int main(int argc, char *argv[])
{
	char *input = NULL;
	size_t len_max = 0;
	ssize_t len;

	printf("Please give a puzzle to solve:\n\n");
	len = getline (&input, &len_max, stdin);	//Get a line with a puzzle
	parsepuzzle(input, len);	//Solve it and print it's solutions
	free(input);
	return 0;
}