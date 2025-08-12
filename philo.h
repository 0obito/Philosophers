#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

// could do two different structs:
// - 1st for ac == 5
// - 2nd for ac == 6

/* struct to store the philosophers' given parameters.*/
typedef struct s_params
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat_time;
}	t_params;

/* struct to store and track the program's data, for smoother and clean code. */
typedef struct s_philo
{
	t_params	*params;
}	t_philo;

/* every function prototype. */
int			ft_atoi(char *s);
t_philo		*set_params(int ac, char *av[]);
void		check_params(int ac, t_philo **ph);
void		print_params(t_philo *ph);

#endif /*PHILO_H*/
