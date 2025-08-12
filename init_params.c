#include "philo.h"

int	ft_atoi(char *s)
{
	int		i;
	int		sign;
	long	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = (ret * 10) + (long)(s[i] - '0');
		i++;
	}
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i])
		return (-1);
	return ((int)(ret * sign));
}

void	check_params(int ac, t_philo **ph)
{
	t_philo	*p;

	p = *ph;
	if (p->params->num_of_philos < 0 || p->params->time_to_die < 0
		|| p->params->time_to_eat < 0 || p->params->time_to_sleep < 0
		|| (p->params->num_of_eat_time < 0 && ac == 6))
	{
		printf("Invalid parameter!\n");
		free(*ph);
		(*ph = NULL);
	}
}

t_philo	*set_params(int ac, char *av[])
{
	t_philo		*ph;
	t_params	*params;

	if (ac != 5 && ac != 6)
		return (NULL);
	params = malloc(sizeof(t_params));
	ph = malloc(sizeof(t_philo));
	if (!ph || !params)
	{
		perror("Error");
		free(params);
		free(ph);
		return (NULL);
	}
	params->num_of_philos = ft_atoi(av[1]);
	params->time_to_die = ft_atoi(av[2]);
	params->time_to_eat = ft_atoi(av[3]);
	params->time_to_sleep = ft_atoi(av[4]);
	params->num_of_eat_time = -1;
	if (ac == 6)
		params->num_of_eat_time = ft_atoi(av[5]);
	ph->params = params;
	check_params(ac, &ph);
	return (ph);
}

void	print_params(t_philo *ph)
{
	if (ph)
	{
		printf("%d\n", ph->params->num_of_philos);
		printf("%d\n", ph->params->time_to_die);
		printf("%d\n", ph->params->time_to_eat);
		printf("%d\n", ph->params->time_to_sleep);
		printf("%d\n", ph->params->num_of_eat_time);
	}
}
