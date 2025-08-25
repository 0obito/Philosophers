/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:55:33 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/25 11:52:03 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_case(t_philo *philo)
{
	go_sleep(philo, philo->rules->time_to_die);
	philo_print("died", philo);
	pthread_mutex_unlock(philo->left_f);
	return ;
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->death_lock);
	if (philo->rules->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->rules->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->death_lock);
	return (0);
}

int	lock_forks(t_philo *philo, int num_of_philos)
{
	pthread_mutex_lock(philo->left_f);
	philo_print("has taken a fork", philo);
	if (philo->left_f == philo->right_f)
		return (one_philo_case(philo), 1);
	pthread_mutex_lock(philo->right_f);
	philo_print("has taken a fork", philo);
	philo->rules->forks[(philo->num) % num_of_philos] *= -1;
	philo->rules->forks[(philo->num + 1) % num_of_philos] *= -1;
	return (0);
}

int	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
	if (philo->left_f != philo->right_f)
		pthread_mutex_unlock(philo->right_f);
	return (0);
}

void	*philo_cycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->num % 2 == 0)
		go_sleep(philo, 10);
	while (1337)
	{
		if (check_death(philo))
			return (NULL);
		if (lock_forks(philo, philo->rules->num_of_philos))
			break ;
		pthread_mutex_lock(&philo->meal_lock);
		philo->last_time_ate = get_current_time(philo->rules);
		pthread_mutex_unlock(&philo->meal_lock);
		if (philo_print("is eating", philo))
			break ;
		go_sleep(philo, philo->rules->time_to_eat);
		unlock_forks(philo);
		if (philo_print("is sleeping", philo))
			break ;
		go_sleep(philo, philo->rules->time_to_sleep);
		if (philo_print("is thinking", philo))
			break ;
	}
	return (NULL);
}
