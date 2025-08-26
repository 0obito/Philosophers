/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:55:33 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/26 21:07:32 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	eat(t_philo *philo)
{
	int	num_of_philos;

	num_of_philos = philo->rules->num_of_philos;
	pthread_mutex_lock(philo->left_f);
	philo->rules->forks[(philo->num) % num_of_philos] *= -1;
	philo_print("has taken a fork", philo, 0);
	pthread_mutex_lock(philo->right_f);
	philo->rules->forks[(philo->num + 1) % num_of_philos] *= -1;
	philo_print("has taken a fork", philo, 0);
	philo_print("is eating", philo, 0);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_time_ate = get_current_time(philo->rules);
	pthread_mutex_unlock(&philo->meal_lock);
	go_sleep(philo, philo->rules->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals += 1;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	if (check_death(philo))
		return ;
}

void	sleepp(t_philo *philo)
{
	philo_print("is sleeping", philo, 0);
	go_sleep(philo, philo->rules->time_to_sleep);
}

void	think(t_philo *philo)
{
	philo_print("is thinking", philo, 0);
}

void	*philo_cycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->rules->num_of_philos == 1)
		return (one_philo_case(philo), NULL);
	if (philo->num % 2 == 0)
		usleep(300);
	while (!check_death(philo))
	{
		eat(philo);
		sleepp(philo);
		think(philo);
	}
	return (NULL);
}
