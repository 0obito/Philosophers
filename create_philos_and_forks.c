#include "philo.h"

pthread_mutex_t	*create_forks(int num_of_forks, pthread_mutex_t	**forks,
								t_rules *rules)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * num_of_forks);
	if (!(*forks))
		return (perror("Error"), NULL);
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&((*forks)[i]), NULL))
		{
			perror("Error");
			free(rules);
			free(*forks);
			*forks = NULL;
			return (NULL);
		}
		i++;
	}
	return (*forks);
}

int	set_philo_values(int i, t_philo *ptr,
		t_rules *rules, pthread_mutex_t *forks)
{
	int	num_of_forks;

	if (!ptr)
		return (perror("Error"), 1);
	num_of_forks = rules->num_of_philos;
	ptr->num = i;
	ptr->rules = rules;
	ptr->left_f = &(forks[i % num_of_forks]);
	ptr->right_f = &(forks[(i + 1) % num_of_forks]);
	ptr->next = NULL;
	if (pthread_create(&(ptr->thread), NULL, philo_cycle, (void *)ptr))
		return (perror("Error"), 1);
	return (0);
}

int	fill_philo(int i, t_philo **ph, t_rules *rules, pthread_mutex_t *forks)
{
	t_philo	*ptr;
	int		j;

	ptr = *ph;
	j = 0;
	while (j < i)
	{
		ptr = ptr->next;
		j++;
	}
	if (set_philo_values(i, ptr, rules, forks) == 1)
		return (1);
	return (0);
}

t_philo	*create_philos(int num_of_philos, t_philo **ph,
						t_rules *rules, pthread_mutex_t *forks)
{
	t_philo	*ptr;
	int		i;

	*ph = malloc(sizeof(t_philo));
	ptr = *ph;
	i = -1;
	while (++i < num_of_philos)
	{
		if (fill_philo(i, ph, rules, forks) == 1)
			return (free_in_philos_creation(rules, forks, ph), NULL);
		ptr->next = malloc(sizeof(t_philo));
		ptr = ptr->next;
	}
	i = -1;
	ptr = *ph;
	while (++i < num_of_philos)
	{
		if (pthread_join(ptr->thread, NULL))
			return (free_in_philos_creation(rules, forks, ph), NULL);
		ptr = ptr->next;
	}
	return (*ph);
}
