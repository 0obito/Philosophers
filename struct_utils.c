/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:56:16 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/25 01:08:44 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(int num, t_rules *rules, pthread_mutex_t *forks_mutexes)
{
	t_philo	*ptr;
	int		num_of_forks_mutexes;

	ptr = malloc(sizeof(t_philo));
	if (!ptr)
		return (NULL);
	num_of_forks_mutexes = rules->num_of_philos;
	ptr->num = num;
	ptr->last_time_ate = get_current_time(rules);
	ptr->meals = 0;
	ptr->next = NULL;
	ptr->rules = rules;
	if (pthread_mutex_init(&ptr->meal_lock, NULL))
		return (NULL);
	ptr->left_f = &(forks_mutexes[num % num_of_forks_mutexes]);
	ptr->right_f = &(forks_mutexes[(num + 1) % num_of_forks_mutexes]);
	if (pthread_create(&ptr->thread, NULL, philo_cycle, (void *)ptr))
		return (NULL);
	return (ptr);
}

t_philo	*append_philo(t_philo **philos_head, t_rules *rules,
						pthread_mutex_t *forks_mutexes)
{
	t_philo		*ptr;
	static int	num;

	num += 1;
	if (*philos_head == NULL)
	{
		*philos_head = create_philo(num, rules, forks_mutexes);
		if (*philos_head == NULL)
			return (NULL);
		ptr = *philos_head;
	}
	else
	{
		ptr = *philos_head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = create_philo(num, rules, forks_mutexes);
		if (ptr->next == NULL)
			return (NULL);
		ptr = ptr->next;
	}
	return (ptr);
}
