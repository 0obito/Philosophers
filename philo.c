#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo	*ph;

	ph = set_params(ac, av);
	if (!ph)
		return (1);
	print_params(ph);
	return (0);
}
