/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:55:42 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/25 11:48:28 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Necessary Libraries Inclusions */
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

/* struct to store the program rules to follow.
   with other variables, like locks and checks. */
typedef struct s_rules
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat_time;
	int				*forks;
	int				death_flag;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}	t_rules;

/* struct to keep each philosopher's needed data. */
typedef struct s_philo
{
	int				num;
	int				meals;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*left_f;
	t_rules			*rules;
	pthread_t		thread;
	long long		last_time_ate;
	pthread_mutex_t	meal_lock;
	struct s_philo	*next;
}	t_philo;

/* General Useful Functions */
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(char *s);

/* Struct Useful Functions */
t_philo			*create_philo(int num, t_rules *rules,
					pthread_mutex_t *forks_mutexes);
t_philo			*append_philo(t_philo **philos_head, t_rules *rules,
					pthread_mutex_t *forks_mutexes);

/* Memory Freeing Functions */
void			free_rules(t_rules **rules);
void			free_forks_mutexes(pthread_mutex_t **forks_mutexes,
					int last_fork_index);
void			free_in_philos_creation(t_rules *rules,
					pthread_mutex_t **forks_mutexes, t_philo **ph);
void			free_philos(t_philo **ph);
void			free_all(t_philo **philos_head,pthread_mutex_t **forks_mutexes,
					t_rules **rules);

/* Main Program Functions */
t_philo			*create_philos(int num_of_philos, t_philo **philos_head,
					t_rules *rules, pthread_mutex_t **forks_mutexes);
t_rules			*create_rules(int ac, char *av[], t_rules **rules);
void			*philo_cycle(void *ptr);
pthread_mutex_t	*create_forks(pthread_mutex_t **forks_mutexes, t_rules *rules);

long long		get_current_time(t_rules *rules);
int				go_sleep(t_philo *philo, long long sleep_time);
int				philo_print(char *operation, t_philo *philo);
// void			set_time_start(t_philo *philo, t_rules *rules);
int				threads_supervisor(t_philo **philos_head);
int				check_death(t_philo *philo);

#endif /*PHILO_H*/
