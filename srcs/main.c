#include "log.h"
#include "ast.h"
#include "resolution.h"

int	main(int argc, char **argv)
{
	int			degree = 0;

	if (argc == 1)
	{
		char stdin_buf[4096];
		if (read(0, stdin_buf, 4096) <= 0)
		{
			log(0, "Could not read stdin, closing...");
			return 1;
		}

		// TODO: stdin
		t_ast_chain *ast = calloc(1, sizeof(t_ast_chain));
		if (!ast)
			return 1;

		// process polynomial equation
		if (parse_polynomial(stdin_buf, ast) == false)
			return 1;
		
		simplify_equation(ast, &degree);
		resolve_polynomial(ast, degree);
		return 0;
	}
	else if (argc == 2)
	{
		t_ast_chain *ast = calloc(1, sizeof(t_ast_chain));
		if (!ast)
			return 1;

		// process polynomial equation
		if (parse_polynomial(argv[1], ast) == false)
			return 1;
		
		simplify_equation(ast, &degree);
		resolve_polynomial(ast, degree);
		return 0;
	}
	else
	{
		log(3, "Usage: ", argv[0], " \"5 * X^1 - 9 * X^2 = 1 * X^1\"");
		return 1;
	}
}
