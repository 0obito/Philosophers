/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:56:44 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/26 21:07:02 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	supervise_starvation(t_philo *philo)
{
	while (philo != NULL)
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (get_current_time(philo->rules) - philo->last_time_ate
			>= (long long)philo->rules->time_to_die)
		{
			pthread_mutex_lock(&philo->rules->death_lock);
			philo->rules->death_flag = 1;
			pthread_mutex_unlock(&philo->rules->death_lock);
			philo_print("died", philo, 1);
			pthread_mutex_unlock(&philo->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->meal_lock);
		philo = philo->next;
	}
	return (0);
}

int	supervise_eaten_meals(t_philo *philo)
{
	t_philo	*ptr;
	int		full_philos;

	ptr = philo;
	full_philos = 0;
	while (philo != NULL)
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (philo->meals >= philo->rules->num_of_eat_time)
			full_philos += 1;
		pthread_mutex_unlock(&philo->meal_lock);
		philo = philo->next;
	}
	if (full_philos == ptr->rules->num_of_philos)
	{
		pthread_mutex_lock(&ptr->rules->death_lock);
		ptr->rules->death_flag = 1;
		pthread_mutex_unlock(&ptr->rules->death_lock);
		return (1);
	}
	return (0);
}

void	*threads_supervisor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo == NULL || philo->rules->num_of_philos == 1)
		return (NULL);
	while (1337)
	{
		if (supervise_starvation(philo))
			return (NULL);
		if (philo->rules->num_of_eat_time != -1 && supervise_eaten_meals(philo))
			return (NULL);
		usleep(50);
	}
	return (NULL);
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
