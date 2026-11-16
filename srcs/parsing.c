#include "ast.h"

#define CHARSET_NB				"0123456789."
#define CHARSET_OP				"+-"
#define CHARSET_SPACE			" \t\n\r\v\f"
#define CHARSET_INNER_FORM_OP	"*"
#define CHARSET_EQUATION_SEP	"="

static int	skip_characters(char *str, int *i, char *charset)
{
	int start_i = *i;
	while (str[*i] && strchr(charset, str[*i]) != 0)
		(*i)++;
	return (*i - start_i);
}

static float	extract_nb(char *str, int *i)
{
	float nb = atof(str + *i);
	int not_decimal_yet = 0;
	while (str[*i] && ((str[*i] >= '0' && str[*i] <= '9') || (str[*i] == '.' && not_decimal_yet++ == 0)))
		(*i)++;
	return nb;
}

static char	extract_char(char *str, int *i, char *charset)
{
	char *ptr = strchr(charset, str[*i]);
	return (ptr?ptr[0 & (*i)++]:'\0');
}

int	parse_polynomial(char *equation_str, t_ast_chain *current)
{

	int				i=0;
	t_ast_chain		*top = current;
	int				is_right_term = false;
	int				polynomial_form_count = 0;

	current->next = 0;
	while (equation_str[i])
	{
		// skip spaces
		skip_characters(equation_str, &i, CHARSET_SPACE);

		if (!equation_str[i])
			break;

		// new chain
		if (polynomial_form_count > 0)
		{
			current->next = (t_ast_chain *)calloc(1, sizeof(t_ast_chain));
			if (!current->next)
			{
				log(1, "Failed to allocate memory for ast chain\n");
				cleanup_ast_chain(&top);
				return 1;
			}
			current = current->next;
		}

		// check if = separator
		char operator = '\0';
		if (!is_right_term && extract_char(equation_str, &i, CHARSET_EQUATION_SEP))
		{
			is_right_term = true;
			skip_characters(equation_str, &i, CHARSET_SPACE);
		}
		else
		{
			// extract operator on a
			operator = extract_char(equation_str, &i, CHARSET_OP);
			if (!operator && polynomial_form_count > 0) // operator missing
				goto error;
		}

		skip_characters(equation_str, &i, CHARSET_SPACE);

		
		// extract a
		if (!equation_str[i] || !strchr(CHARSET_NB, equation_str[i])) // nan
			goto error;
		
		current->a = extract_nb(equation_str, &i);

		// apply negative if substraction
		if ((operator == '-' && !is_right_term) || is_right_term)
			current->a = -current->a;

		// space
		skip_characters(equation_str, &i, CHARSET_SPACE);

		if (!equation_str[i])
			break;

		// extract inner a * X^P form operator
		char mul_op = extract_char(equation_str, &i, CHARSET_INNER_FORM_OP);
		if (mul_op && mul_op != '*') // invalid operator
			goto error;

		// space
		skip_characters(equation_str, &i, CHARSET_SPACE);

		// verify format of X^ if exists
		if (extract_char(equation_str, &i, "X"))
		{
			if (!extract_char(equation_str, &i, "^"))
				goto error;

			if (!equation_str[i] || !strchr(CHARSET_NB, equation_str[i])) // nan
				goto error;
			
			// extract P
			current->x.exp_p = extract_nb(equation_str, &i);
		}
		
		polynomial_form_count++;
	}
	if (!is_right_term)
		goto error;

	return true;

error:
	log(1, "Invalid polynomial form: need to be in the form:\n       a * X^P + b * X^K ... = a * X^P + b * X^K ...");
	
	// cleanup
	cleanup_ast_chain(&top);

	return false;
}

void	simplify_equation(t_ast_chain **ast, int *degree)
{
	t_ast_chain	*current;
	t_ast_chain	*cmp;
	t_ast_chain	*prev;
	t_ast_chain	*sorted;
	t_ast_chain	*next;

	// simplify
	current = *ast;
	*degree = 0;
	while (current)
	{
		prev = current;
		cmp = current->next;
		while (cmp)
		{
			if (cmp->x.exp_p == current->x.exp_p)
			{
				float old_a = cmp->a;
				prev->next = cmp->next;
				free(cmp);
				cmp = prev->next;
				current->a += old_a;
			}
			else
			{
				prev = cmp;
				cmp = cmp->next;
			}
		}
		current = current->next;
	}

	// remove zero coefficients
	current = *ast;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->a == 0)
		{
			if (prev)
				prev->next = next;
			else
				*ast = next;
			free(current);
		}
		else
			prev = current;
		current = next;
	}

	// sort
	sorted = NULL;
	current = *ast;
	while (current)
	{
		next = current->next;
		if (!sorted || current->x.exp_p < sorted->x.exp_p)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			cmp = sorted;
			while (cmp->next && cmp->next->x.exp_p <= current->x.exp_p)
				cmp = cmp->next;
			current->next = cmp->next;
			cmp->next = current;
		}
		*degree = max(current->x.exp_p, *degree);
		current = next;
	}

	*ast = sorted;
}