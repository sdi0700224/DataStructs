/* This code is from the book "Algorithms in C" by Robert Sedgewick */

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)


void sort(Item a[], int l, int r)
{ 	
	int i;

    for(i = (l + 1); i <= r; i++) 
	{
		compexch(a[l], a[i]);
	}
    for(i = (l + 2); i <= r; i++)
    { 	
		int j = i; 
		Item v = a[i];
        while(less(v, a[j-1]))
        { 	
			a[j] = a[j-1]; 
			j--; 
		}
        a[j] = v;
    }
}


int main(int argc, char *argv[])
{ 	
	int i=0, N = atoi(argv[1]);
    int *a = malloc(N*sizeof(int));

    for(i = 0; i < N; i++)
	{
      	a[i] = 1000*(1.0*rand()/RAND_MAX);
	}
    for(i = 0; i < N; i++) 
	{	
		printf("%3d ", a[i]);
	}
    printf("\n");
    sort(a, 0, N-1);
    for(i = 0; i < N; i++) 
	{	
		printf("%3d ", a[i]);
	}
    printf("\n");
}