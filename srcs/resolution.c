#include "resolution.h"

static int (*resolution_table[])(t_ast_chain*) = {
	degree_zero,
	degree_one,
    degree_two
};

int	resolve_polynomial(t_ast_chain *ast, int degree)
{
	t_ast_chain *current = ast;
	int max_handled_degree = sizeof(resolution_table) / sizeof(resolution_table[0]);

	// add a const a=0 to equation if no const yet
	if (ast->x.exp_p != 0) 
	{
		t_ast_chain new = {.a=0, .x={.exp_p=0}, .next=ast};
		ast = &new;
	}

	printf("Reduced form: ");
	while (current)
	{
		printf("%g * X^%d", current->a, current->x.exp_p);
		if (current->next)
		{
			printf(" + ");
		}
		current = current->next;
	}
	printf(" = 0\n");
	if (degree > 0)
		printf("Polynomial degree: %d\n", degree);
	if (degree >= max_handled_degree)
	{
		printf("The polynomial degree is strictly greater than %i, I can't solve.\n", max_handled_degree - 1);
		return false;
	}

	return (resolution_table[degree](ast));
}