#include "log.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
		return 1; // TODO: stdin
	else if (argc == 2)
	{
		// handle polynomial equ.
	}
	else
	{
		log("Usage: ", argv[0], " \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"");
		return 1;
	}
	return 0;
}
