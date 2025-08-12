#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

// could do two different structs:
// - 1st for ac == 5
// - 2nd for ac == 6

typedef struct s_params
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat_time;
}	t_params;

typedef struct s_philo
{
	t_params	*params;
	int			ret;
}	t_philo;

#endif /*PHILO_H*/
