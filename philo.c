#include "philo.h"

int	main(int ac, char *av[])
{
	t_rules			*rules;
	pthread_mutex_t	*forks;
	t_philo			*ph;

	if (create_rules(ac, av, &rules) == NULL)
		return (1);
	if (create_forks((rules->num_of_philos), &forks, rules) == NULL)
		return (1);
	if (create_philos(rules->num_of_philos, &ph, rules, forks) == NULL)
		return (1);
	printf("All threads done!\n");
}
