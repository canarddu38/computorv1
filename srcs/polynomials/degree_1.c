#include "resolution.h"

int		degree_one(t_ast_chain *ast)
{
	float a = ast->a;
	float b = ast->next->a;

	float x0 = -a / b;
	printf("%g\n", x0);
	return true;
}