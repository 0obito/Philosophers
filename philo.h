#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

/* struct to store the philosophers' given parameters.*/
typedef struct s_rules
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat_time;
}	t_rules;

typedef struct s_philo
{
	int				num;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*left_f;
	t_rules			*rules;
	pthread_t		thread;
	struct s_philo	*next;
}	t_philo;

/* struct to store and track the program's data, for smoother and clean code. */
// typedef struct s_program
// {
// 	t_params		*params;
// 	t_philo			*philos;
// 	pthread_mutex_t	lock;
// }	t_program;

/* every function prototype. */
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(char *s);
t_rules			*create_rules(int ac, char *av[], t_rules **rules);
void			check_rules(int ac, t_rules **rules);
void			print_rules(t_rules *rules);
pthread_mutex_t	*create_forks(int num_of_forks, pthread_mutex_t	**forks,
					t_rules *rules);
t_philo			*create_philos(int num_of_philos, t_philo **ph,
					t_rules *rules, pthread_mutex_t *forks);
int				fill_philo(int i, t_philo **ph,
					t_rules *rules, pthread_mutex_t *forks);
int				set_philo_values(int i, t_philo *ptr,
					t_rules *rules, pthread_mutex_t *forks);
void			free_in_philos_creation(t_rules *rules,
					pthread_mutex_t *forks, t_philo **ph);
void			free_philo_struct(t_philo **ph);
void			*philo_cycle(void *ptr);

#endif /*PHILO_H*/
