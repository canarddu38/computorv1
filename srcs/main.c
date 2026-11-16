#include "log.h"
#include "ast.h"
#include "resolution.h"

int	resolve(char *equation)
{
	int 		degree = 0;
	t_ast_chain	*ast = calloc(1, sizeof(t_ast_chain));
	if (!ast)
		return 1;

	// process polynomial equation
	if (parse_polynomial(equation, ast) == false)
		return 1;
	
	simplify_equation(&ast, &degree);
	resolve_polynomial(ast, degree);
	
	cleanup_ast_chain(&ast);
	return 0;
}

int	main(int argc, char **argv)
{
	char	stdin_buf[4096];

	if (argc == 1)
	{
		size_t read_size = read(0, stdin_buf, 4096);
		if (read_size <= 0)
		{
			log(0, "Could not read stdin, closing...");
			return 1;
		}

		while (stdin_buf[read_size - 1] == '\n' && read_size > 0)
			stdin_buf[read_size-- - 1] = '\0';
		
		return resolve(stdin_buf);
	}
	else if (argc == 2)
		return resolve(argv[1]);
	else
	{
		log(3, "Usage: ", argv[0], " \"5 * X^1 - 9 * X^2 = 1 * X^1\"");
		return 1;
	}
}
