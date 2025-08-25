/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:55:39 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/25 00:12:50 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_rules(t_rules *rules)
{
	if (rules)
	{
		printf("%d\n", rules->num_of_philos);
		printf("%d\n", rules->time_to_die);
		printf("%d\n", rules->time_to_eat);
		printf("%d\n", rules->time_to_sleep);
		printf("%d\n", rules->num_of_eat_time);
	}
}

static t_rules	*check_rules(int ac, t_rules **rules)
{
	t_rules	*p;

	p = *rules;
	if (p->num_of_philos < 0 || p->time_to_die < 0
		|| p->time_to_eat < 0 || p->time_to_sleep < 0
		|| (ac == 6 && p->num_of_eat_time < 0))
	{
		ft_putstr_fd("One or More Parameters Are Invalid!\n\
Passed Parameters Must Be >= 0 and Must Consist of Digits.\n\
Parameters Must Also Stay Within The Limits of an Integer.\n", 2);
		return (NULL);
	}
	return (*rules);
}

t_rules	*create_rules(int ac, char *av[], t_rules **rules)
{
	*rules = malloc(sizeof(t_rules));
	if (!(*rules))
		return (NULL);
	(*rules)->num_of_philos = ft_atoi(av[1]);
	(*rules)->time_to_die = ft_atoi(av[2]);
	(*rules)->time_to_eat = ft_atoi(av[3]);
	(*rules)->time_to_sleep = ft_atoi(av[4]);
	(*rules)->num_of_eat_time = -1;
	if (ac == 6)
		(*rules)->num_of_eat_time = ft_atoi(av[5]);
	(*rules)->death_flag = 0;
	(*rules)->forks = NULL;
	if (pthread_mutex_init(&(*rules)->print_lock, NULL)
		|| pthread_mutex_init(&(*rules)->death_lock, NULL))
		return (NULL);
	if (check_rules(ac, rules) == NULL)
		return (NULL);
	(*rules)->start_time = get_current_time(*rules);
	return (*rules);
}
