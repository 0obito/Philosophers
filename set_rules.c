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

// 11 Lines
void	check_rules(int ac, t_rules **rules)
{
	t_rules	*p;

	p = *rules;
	if (p->num_of_philos < 0 || p->time_to_die < 0
		|| p->time_to_eat < 0 || p->time_to_sleep < 0
		|| (p->num_of_eat_time < 0 && ac == 6))
	{
		write(2, "One Or More Parameters Is Invalid !\n", 36);
		free(*rules);
		(*rules = NULL);
	}
}

// 21 Lines
t_rules	*create_rules(int ac, char *av[], t_rules **rules)
{
	if (ac != 5 && ac != 6)
		return (NULL);
	*rules = malloc(sizeof(t_rules));
	if (!(*rules))
		return (perror("Error"), NULL);
	(*rules)->num_of_philos = ft_atoi(av[1]);
	(*rules)->time_to_die = ft_atoi(av[2]);
	(*rules)->time_to_eat = ft_atoi(av[3]);
	(*rules)->time_to_sleep = ft_atoi(av[4]);
	(*rules)->num_of_eat_time = -1;
	if (ac == 6)
		(*rules)->num_of_eat_time = ft_atoi(av[5]);
	check_rules(ac, rules);
	return (*rules);
}
