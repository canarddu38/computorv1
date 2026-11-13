#include "resolution.h"

int		degree_two(t_ast_chain *ast)
{
	float a = ast->next->next->a;
	float b = ast->next->a;
	float c = ast->a;

	float det = b * b - 4 * a * c;
	if (det > 0)
	{
		float x1 = (-b - sqrt(det)) / (2 * a);
		float x2 = (-b + sqrt(det)) / (2 * a);
		printf("Discriminant is strictly positive, the two solutions are:\n");
		printf("%g\n", x1);
		printf("%g\n", x2);
	}
	else if (det == 0)
	{
		float x0 = -b / (2 * a);
		printf("Discriminant is null, the only solution is:\n");
		printf("%g\n", x0);
	}
	else if (det < 0)
	{
		int div = 2 * a;
		int real = -b;
		int imag = (int)sqrt(-det);

		printf("Discriminant is strictly negative, the two complex solutions are:\n");

		// simplify
		int gcd = 1;
		for (int i = 1; i <= abs(div); i++) {
			if (real % i == 0 && imag % i == 0 && div % i == 0) {
				gcd = i;
			}
		}

		real /= gcd;
		imag /= gcd;
		div /= gcd;

		printf("%d/%d + %di/%d\n", real, div, imag, div);
		printf("%d/%d - %di/%d\n", real, div, imag, div);
	}
	return true;
}