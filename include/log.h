#ifndef LOG_H
#define LOG_H

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

static inline void	log(int n, const char *str, ...)
{
	va_list l;

	va_start(l, str);
	fprintf(stderr, "\033[31mERROR\033[0m: %s", str);
	for (int i=1; i<n; i++)
	{
		char *s = va_arg(l, char *);
		if (!s)
			break;
		fprintf(stderr, "%s", s);
	}
	write(2, "\n", 1);
	va_end(l);
}

#endif