#include "philo.h"

void	free_philo_struct(t_philo **ph)
{
	t_philo	*ptr;
	t_philo	*tmp;

	ptr = *ph;
	tmp = *ph;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
}

void	free_in_philos_creation(t_rules *rules,
			pthread_mutex_t *forks, t_philo **ph)
{
	free(rules);
	free(forks);
	free_philo_struct(ph);
}
