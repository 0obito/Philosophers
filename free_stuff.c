/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:55:24 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/26 21:06:44 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_rules(t_rules **rules)
{
	if (*rules)
	{
		free((*rules)->forks);
		pthread_mutex_destroy(&(*rules)->print_lock);
		pthread_mutex_destroy(&(*rules)->death_lock);
		free(*rules);
		*rules = NULL;
	}
}

void	free_forks_mutexes(pthread_mutex_t **forks_mutexes, int last_fork)
{
	int	i;

	i = 0;
	if (!(*forks_mutexes))
		return ;
	while (i < last_fork)
	{
		pthread_mutex_destroy(&((*forks_mutexes)[i]));
		i++;
	}
	free(*forks_mutexes);
	*forks_mutexes = NULL;
}

void	free_philos(t_philo **philos_head)
{
	t_philo	*ptr;
	t_philo	*tmp;

	ptr = *philos_head;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
}

void	free_in_philos_creation(t_rules *rules,
			pthread_mutex_t **forks_mutexes, t_philo **philos_head)
{
	free_philos(philos_head);
	free_forks_mutexes(forks_mutexes, rules->num_of_philos);
	free(rules);
}

void	free_all(t_philo **philos_head, pthread_mutex_t **forks_mutexes
				, t_rules **rules)
{
	free_philos(philos_head);
	free_forks_mutexes(forks_mutexes, (*rules)->num_of_philos);
	free_rules(rules);
}
