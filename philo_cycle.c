#include "philo.h"

void	*philo_cycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->num % 2 == 0)
		sleep(1);
	pthread_mutex_lock(philo->left_f);
	pthread_mutex_lock(philo->right_f);
	printf("Philo[%d]\nI am alive!\n", philo->num + 1);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	return (NULL);
}
