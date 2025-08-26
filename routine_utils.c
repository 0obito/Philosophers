/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:02:39 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/26 21:07:14 by aelmsafe         ###   ########.fr       */
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

	now = get_current_time(philo->rules);
	while (get_current_time(philo->rules) - now < sleep_time)
	{
		if (check_death(philo))
			return (1);
		usleep(50);
	}
	return (0);
}

int	philo_print(char *operation, t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->rules->print_lock);
	if (flag == 1 || !check_death(philo))
		printf("%lld %d %s\n",
			get_current_time(philo->rules), philo->num, operation);
	pthread_mutex_unlock(&philo->rules->print_lock);
	return (0);
}

void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	philo_print("has taken a fork", philo, 0);
	go_sleep(philo, philo->rules->time_to_die);
	philo_print("died", philo, 0);
	pthread_mutex_unlock(philo->left_f);
	return ;
}
