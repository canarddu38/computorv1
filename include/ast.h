#ifndef AST_H
#define AST_H

#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "log.h"

#define true		1
#define false		0

#define max(a, b)	(a>b)?a:b;

typedef struct
{
	int		exp_p;
}	t_ast_exp_x;

typedef struct s_ast_chain
{
	float					a;
	t_ast_exp_x				x;

	struct s_ast_chain		*next;
}	t_ast_chain;

static inline void	cleanup_ast_chain(t_ast_chain **lst)
{
	t_ast_chain	*current;
	t_ast_chain	*next_one;

	if (!lst)
		return;
	
	current = *lst;
	while (current)
	{
		next_one = current->next;
		free(current);
		current = next_one;
	}
	*lst = NULL;
}

int		parse_polynomial(char *equation_str, t_ast_chain *ast);
void	simplify_equation(t_ast_chain *ast, int *degree);

#endif