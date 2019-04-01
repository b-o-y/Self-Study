/*
* Travis Henderson
* C Exercises
* Date Last Modified: 17/08/20
*
* 5-10:
* Write the program expr which evaluates reverse
* Polish expression from the command line, where each
* operator or operand is a separate argument. For example
* expr 2 3 4 + *
* evaluates 2 * (3+4)
*
* Notes:
* -I named the program 510, not expr.
* -Has no error checking.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char ops[10]; // Contains operations.
	int nums[10]; // Contains operands.
	int i = 0; // Indexing.
	int j = 0;
	
	while (--argc > 0) // This loop creates two buffers for operands and operators.
	{
		char op = argv[argc][0];
		if (op == '/' || op == '+' || op == '-' || op == '*')
			ops[j++] = op;
		else
			nums[i++] = atoi(argv[argc]);
	}

	int expr = 0;
	int jj = 0; // I don't really like indexing the other way around, but whatever.
	int ii = 0;
	switch(ops[jj++])
	{
		case '/':
			expr = nums[ii++] / nums[ii++];
			break;
		case '+':
			expr = nums[ii++] + nums[ii++];
			break;
		case '-':
			expr = nums[ii++] - nums[ii++];
			break;
		case '*':
			expr = nums[ii++] * nums[ii++];
			break;
		default:
			printf("Invalid input\n");
			return 0;
	}

	while (jj < j) // Finishes all remaining operations and operands.
	{
		switch(ops[jj++])
		{
			case '/':
				expr /= nums[ii++];
				break;
			case '+':
				expr += nums[ii++];
				break;
			case '-':
				expr -= nums[ii++];
				break;
			case '*':
				expr *= nums[ii++];
				break;
			default:
				printf("Invalid input\n");
				return 0;
		}
	}
	printf("%d\n", expr);

	return 0;
}
