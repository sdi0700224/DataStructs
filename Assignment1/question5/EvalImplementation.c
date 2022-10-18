#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "Item.h"
#include "STACK.h"

//Η υλοποίηση χρησιμοποιεί τον ήδη έτοιμο κώδικα του μαθήματος που μετατρέπει την Infix σε Postfix έτσι όπως εχει πει κ. Κουμπαράκης 
//στην παρουσίαση της εργασίας
//Προστέθηκε κώδικας για πολυψήφιους αριθμούς και να αποτιμά κιόλας την παράσταση, υπήρξε απάντηση στο Piazza για αυτήν τη λύση 
//για όσους το είχαμε κάνει έτσι ήδη ότι είναι εντάξει και δεν θα υπάρξει επίπτωση στη βαθμολογία

int calc(int n1, int n2, char ch) //Makes the proper calculation depenting on the operator and returns
{
	int r;

	if(ch == '+')
	{
		r = n2 + n1;
	}
	else if(ch == '-')
	{
		r = n2 - n1;
	}
	else if(ch == '*')
	{
		r = n2 * n1;
	}
	else if(ch == '/')
	{
		r = n2 / n1;
	}
	else if(ch == '%')
	{
		r = n2 % n1;
	}
	else
	{
		printf("Error! Not valid operator!");
		return INT_MIN;
	}
	return r;
}


int inf_eval(char input[])
{ 	
	char *a = input; 
	int i, k, j = 0, N = strlen(a);
	char buffer[N], ch;	//Accumulates digits and evaluates also non sigle-digit numbers
	int postopbuff[N], *pbuff = postopbuff;	//Works like a Stack
	int n1, n2, r;

    for (k = 0; k < N; k++)
	{
		buffer[k] = '\0'; 
	}
	STACKinit(N);
    for (i = 0; i < N; i++)
    {
        if (a[i] == ')')
		{
			ch = STACKpop();
			n1 = *(--pbuff);	//Reduce pointer before POP everytime
			n2 = *(--pbuff);
			r = calc(n1, n2, ch);
			*(pbuff++) = r;
		}
        if ((a[i] == '+') || (a[i] == '*') || (a[i] == '-') || (a[i] == '/') || (a[i] == '%'))
		{
        	STACKpush(a[i]);
		}
        if ((a[i] >= '0') && (a[i] <= '9'))
		{
			buffer[j] = a[i];
			j++;
			if ((i + 1 == N) || (isdigit(a[i+1]) == 0)) //If we are at the end of array or next element is non digit
			{											//Time to evaluate and reinitialize buffer
				*(pbuff++) = atoi(buffer); //Increase pointer after insertion everytime
				j = 0;
				for (k = 0; k < N; k++)
				{
					buffer[k] = '\0'; 
				}
			}
		}
    }
	return *(--pbuff);
}