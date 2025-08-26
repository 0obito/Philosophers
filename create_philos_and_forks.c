/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos_and_forks.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:57:03 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/25 00:51:39 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*create_forks(pthread_mutex_t **forks_mutexes,
								t_rules *rules)
{
	int	i;
	int	num_of_forks;
	int	*forks;

	num_of_forks = rules->num_of_philos;
	*forks_mutexes = malloc(sizeof(pthread_mutex_t) * num_of_forks);
	forks = malloc(sizeof(int) * num_of_forks);
	if (!(*forks_mutexes) || !forks)
		return (free(*forks_mutexes), free(forks), NULL);
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&((*forks_mutexes)[i]), NULL))
			return (free(forks), free_forks_mutexes(forks_mutexes, i), NULL);
		i++;
	}
	memset(forks, 0xFF, sizeof(int) * num_of_forks);
	rules->forks = forks;
	return (*forks_mutexes);
}

t_philo	*create_philos(int num_of_philos, t_philo **philos_head,
						t_rules *rules, pthread_mutex_t **forks_mutexes)
{
	t_philo			*ptr;
	pthread_t		monitor;
	int				n;

	n = num_of_philos;
	while (--n > -1)
		if (append_philo(philos_head, rules, *forks_mutexes) == NULL)
			return (free_philos(philos_head), NULL);
	ptr = *philos_head;
	rules->start_time = get_current_time(rules);
	while (ptr != NULL)
	{
		ptr->last_time_ate = rules->start_time;
		if (pthread_create(&ptr->thread, NULL, philo_cycle, (void *)ptr))
			return (NULL);
		ptr = ptr->next;
	}
	if (pthread_create(&monitor, NULL, threads_supervisor, (void *)(*philos_head)))
		return (NULL);
	ptr = *philos_head;
	while (ptr)
	{
		if (pthread_join(ptr->thread, NULL))
			return (free_philos(philos_head), NULL);
		ptr = ptr->next;
	}
	if (pthread_join(monitor, NULL))
		return (free_philos(philos_head), NULL);
	return (*philos_head);
}
