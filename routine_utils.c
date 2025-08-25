/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:02:39 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/25 11:47:10 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(t_rules *rules)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (((long long)tv.tv_sec * 1000)
			+ ((long long)tv.tv_usec / 1000)) - rules->start_time;
	return (current_time);
}

int	go_sleep(t_philo *philo, long long sleep_time)
{
	long long	now;
	long long	later;

	now = get_current_time(philo->rules);
	later = get_current_time(philo->rules);
	while (later - now < sleep_time)
	{
		// pthread_mutex_lock(&philo->rules->death_lock);
		// if (philo->rules->death_flag == 1)
		// {
		// 	pthread_mutex_unlock(&philo->rules->death_lock);
		// 	return (1);
		// }
		// pthread_mutex_unlock(&philo->rules->death_lock);
		usleep(25);
		later = get_current_time(philo->rules);
	}
	return (0);
}

int	philo_print(char *operation, t_philo *philo)
{
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(&philo->rules->print_lock);
	printf("%lld %d ", get_current_time(philo->rules), philo->num);
	printf("%s\n", operation);
	pthread_mutex_unlock(&philo->rules->print_lock);
	return (0);
}
