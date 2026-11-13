#include "resolution.h"

int		degree_zero(t_ast_chain *ast)
{
	float a = ast->a;
	if (a == 0)
	{	
		printf("Any real number is a solution.\n");
		return true;
	}
	else
	{
		printf("No solution.\n");
		return false;
	}
}