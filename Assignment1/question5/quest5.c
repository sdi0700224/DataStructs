#include <stdio.h>
#include <stdlib.h>
#include "EvalInterface.h"


int main(int argc, char *argv[])
{
	int result;

	result = inf_eval(argv[1]);
	printf("\nEvaluation:");
	printf("\n%d\n", result);
	
}
 