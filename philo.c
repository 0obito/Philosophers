/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:56:44 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/25 01:29:46 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_supervisor(t_philo **philos_head)
{
	t_philo	*ptr;
	int		full_philos;

	if ((*philos_head) == NULL)
		return (1);
	while (1337)
	{
		ptr = *philos_head;
		full_philos = 0;
		while (ptr != NULL)
		{
			if (get_current_time(ptr->rules) - ptr->last_time_ate
				>= (long long)ptr->rules->time_to_die)
			{
				philo_print("is dead", ptr);
				pthread_mutex_lock(&ptr->rules->death_lock);
				ptr->rules->death_flag = 1;
				pthread_mutex_unlock(&ptr->rules->death_lock);
				return (0);
			}
			pthread_mutex_lock(&ptr->meal_lock);
			if (ptr->meals == ptr->rules->num_of_eat_time)
				full_philos += 1;
			pthread_mutex_unlock(&ptr->meal_lock);
			ptr = ptr->next;
		}
		if (full_philos == (*philos_head)->rules->num_of_philos)
		{
			pthread_mutex_lock(&(*philos_head)->rules->death_lock);
			ptr->rules->death_flag = 1;
			pthread_mutex_lock(&(*philos_head)->rules->death_lock);
			return (0);
		}
		usleep(20);
	}
}

int	main(int ac, char *av[])
{
	t_philo			*philos;
	t_rules			*rules;
	pthread_mutex_t	*forks_mutexes;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Number of Passed Parameters is Incorrect:\n\
Try Passing 4 to 5 Parameters.\n", 2);
		return (1);
	}
	if (create_rules(ac, av, &rules) == NULL)
		return (free_rules(&rules), 1);
	if (create_forks(&forks_mutexes, rules) == NULL)
		return (free_rules(&rules), 1);
	philos = NULL;
	if (!create_philos(rules->num_of_philos, &philos, rules, &forks_mutexes))
	{
		free_forks_mutexes(&forks_mutexes, rules->num_of_philos);
		return (free_rules(&rules), 1);
	}
	free_all(&philos, &forks_mutexes, &rules);
}
