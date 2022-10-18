#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "puzzlerec.h"

int solflag = 0;	//Helps checking out solutions that start with 0.

void parsepuzzle(char *input, int len) //Basic parsing here, all non alpha characters are the same as '+' and '=', just does the job
{
	int i, j, flag, l1 = 0, l2 = 0, l3 = 0, l4 = 0, *values, errcounter;	//length of words, value of letters array, counter that helps error handling
	int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; //digits available
	char *w1, *w2, *w3, *letters, *tw2, *tw3;	//three words of puzzle, different letters and temps used for free

	w1 = malloc(50*sizeof(char));
	w2 = malloc(50*sizeof(char));
	w3 = malloc(50*sizeof(char));
	tw2 = w2;	//store for free
	tw3 = w3;	//same
	strcpy(w1 , input);
	if (!isalpha(*w1))
	{
		printf("Please give a valid puzzle!\nNot possible to solve\n");
		return;
	}
	for(i = 0; i < len; i++)
	{
		if (!isalpha(*(w1 + i)))	//First non alpha character
		{
			*(w1 + i) = '\0';	//Trick string to finish here
			strcpy(w2, (w1 + i + 1));	//Copy string from point where first word stops
			if (strlen(w2) == 0)
			{
				printf("Please give a valid puzzle!\nNot possible to solve\n");
				return;
			}
			l1 = i;	//Same first word lenght
			errcounter = strlen(w2);
			while(!isalpha(*w2))	//Dismiss characters untill next word
			{
				if (errcounter < 0)
				{
					printf("Please give a valid puzzle!\nNot possible to solve\n");
					return;
				}
				errcounter--;
				w2++;
			}
			break;
		}
	}
	for (i = 0; i < strlen(w2); i++)
	{
		if (!isalpha(*(w2 + i)))	//Same here as before
		{
			*(w2 + i) = '\0';
			strcpy(w3, (w2 + i + 1));
			if (strlen(w3) == 0)
			{
				printf("Please give a valid puzzle!\nNot possible to solve\n");
				return;
			}
			l2 = i;
			errcounter = strlen(w3);
			while(!isalpha(*w3))
			{
				if (errcounter < 0)
				{
					printf("Please give a valid puzzle!\nNot possible to solve\n");
					return;
				}
				errcounter--;
				w3++;
			}
			break;
		}
	}
	for (i = 0; i < strlen(w3); i++)
	{
		if (!isalpha(*(w3 + i)))
		{
			*(w3 + i) = '\0';
			l3 = i;
			break;
		}
	}
	letters = malloc((l1+l2+l3)*sizeof(char));
	for (i = 0; i < (l1+l2+l3); i++)	//Initialize array
	{
		*(letters + i) = '\0';
	}
	values = malloc((l1+l2+l3)*sizeof(int));
	for(i = 0; i < l1; i++)
	{
		flag = 1;
		for(j = 0 ; j < (l1 + l2 + l3); j++)
		{
			if(*(w1 + i) == *(letters + j))
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
		{
			l4++;
			*(letters + l4 - 1) = *(w1 + i);	//If letters is different save it
			*(values + l4 - 1) = -1;			//and initialize value to a negative number
		}
	}
	for(i = 0; i < l2; i++)
	{
		flag = 1;
		for(j = 0 ; j < (l1 + l2 + l3); j++)
		{
			if(*(w2 + i) == *(letters + j))
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
		{
			l4++;
			*(letters + l4 - 1) = *(w2 + i);	//Same for next words
			*(values + l4 - 1) = -1;
		}
	}
	for(i = 0; i < l3; i++)
	{
		flag = 1;
		for(j = 0 ; j < (l1 + l2 + l3); j++)
		{
			if(*(w3 + i) == *(letters + j))
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
		{
			l4++;
			*(letters + l4 - 1) = *(w3 + i);
			*(values + l4 - 1) = -1;
		}
	}
	printf("\n");
	if(l4 >= 10)	//Different letters can't be more than different digits
	{
		printf("Different letters shouldn't be more than digits!\nNot possible to solve\n");
		return;
	}
	if(l1 > l3 || l2 > l3) //Since we only add, input can't have more digits than result
	{
		printf("Result can't have less digits than inputs!\nNot possible to solve\n");
		return;
	}
	solverec(w1, w2, w3, l1, l2, l3, letters, values, l4, digits);	//Now that parsing finished call a recursive function to solve it
	if (solflag == 0)
	{
		printf("No solutions found\n");
	}
	free(w1);
	free(tw2);
	free(tw3);
	free(letters);
	free(values);
	return;
}

void solverec(char *w1, char *w2, char *w3, int l1, int l2, int l3, char* letters, int values[], int l4, int digits[])
{
	int i, j, k, flag = 1;
	int sum1 = 0, sum2 = 0, sum3 = 0;
	int printflag = 1, testsum=1;

	for(i = 0; i < l4; i++)
	{
		if(*(values + i) < 0)	//If there are more letters to find value
		{
			flag = 0;
			break;
		}
	}
	if(flag == 0)
	{
		for(j = 0; j < 10; j++)
		{
			if(digits[j] >= 0)
			{
				*(values + i) = j;	//Assign digit to letter
				digits[j] = -1; //Digit is used
				int tempdigits[10];	//New arrays to use for backtracking
				for (k = 0; k < 10; k++)
				{
					tempdigits[k] = digits[k];
				}
				int tempvalues[l4];
				for (k = 0; k < l4; k++)
				{
					tempvalues[k] = values[k];
				}
				solverec(w1, w2, w3, l1, l2, l3, letters, tempvalues, l4, tempdigits);	//Do again with new arrays and one less to find
				digits[j] = j;	//return to before state for another loop
			}
		}
	}
	else
	{
		for (i = 0; i < l1; i++)
		{
			for (j = 0; j < l4; j++)
			{
				if(*(w1+i) == *(letters + j))	//Find letter value for words
				{
					sum1 = sum1 + (pow(10, (l1 - i - 1))* (*(values + j)));	//Evaluate, using the proper power of 10, depenting of the place of each digit
				}
			}
		}
		for (i = 0; i < l2; i++)
		{
			for (j = 0; j < l4; j++)
			{
				if(*(w2+i) == *(letters + j))
				{
					sum2 = sum2 + (pow(10, (l2 - i - 1))* (*(values + j)));
				}
			}
		}
		for (i = 0; i < l3; i++)
		{
			for (j = 0; j < l4; j++)
			{
				if(*(w3+i) == *(letters + j))
				{
					sum3 = sum3 + (pow(10, (l3 - i - 1))* (*(values + j)));
				}
			}
		}
		testsum = 1;	//Here we find if the solution has a 0 in the begging of a word
		for(int i=1; i<l1; i++)
		{
			testsum = testsum * 10;
		}
		if(sum1 - testsum < 0)	
		{
			printflag = 0;	//If word starts with zero make the flag 0
		}
		testsum = 1;
		for(int i=1; i<l2; i++)
		{
			testsum = testsum * 10;
		}
		if(sum2 - testsum < 0)
		{
			printflag = 0;
		}
		testsum = 1;
		for(int i=1; i<l3; i++)
		{
			testsum = testsum * 10;
		}
		if(sum3 - testsum < 0)
		{
			printflag = 0;
		}
		if((sum1 + sum2 == sum3) && (printflag == 1)) //If requirement is valid and word doesn't start with zero
		{
			solflag = 1;	//At least one solution found
			printf ("%d + %d = %d\n", sum1, sum2, sum3);
			printf("%s\n", letters);
			for(i = 0; i < l4; i++)
			{
				printf("%d", *(values + i));
			}
			printf("\n\n");
		}
	}
	return;
}