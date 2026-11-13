#ifndef MATHS_H
#define MATHS_H

#define MAX_ITERATIONS 10

static inline float	sqrt(float nbr)
{
	float	x;
	int		i;

	x = 1.0f;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		x = 0.5 * (x + (nbr / x));
		i++;
	}
	return (x);
}

#endif