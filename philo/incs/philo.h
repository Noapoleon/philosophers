/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:54:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/02 01:59:39 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>

# define MAX_PHILOS	200
# define MIN_TIME	60

# define USAGE1				"Usage: %s <number_of_philosophers> <time_to_die> "
# define USAGE2				"<time_to_eat> <time_to_sleep> "
# define USAGE3				"[number_of_times_each_philosopher_should_eat]\n"

# define PHILO_ERR			"\e[31;7;1m[PHILO ERROR]\e[0m "
# define PE_FORVAL			"bad format/value\n"
# define PE_N_PHILO			"number_of_philosophers: "
# define PE_T_DIE			"time_to_die: "
# define PE_T_EAT			"time_to_eat: "
# define PE_T_SLEEP			"time_to_sleep: "
# define PE_N_MEALS			"number_of_times_each_philosopher_should_eat: "
# define PE_THREAD_CREATE	"Failed to create thread #%d\n"
# define PE_THREAD_JOIN		"Failed to join thread #%d\n"

# define FLD_TIM	"\e[7;1m%06ld\e[0m"
# define FLD_POS	" %3d "
# define FLD_FRK	"\e[35;1mhas taken a fork\e[0m\n"
# define FLD_EAT	"\e[32;1mis eating\e[0m\n"
# define FLD_SLP	"\e[34;1mis sleeping\e[0m\n"
# define FLD_THK	"\e[33;1mis thinking\e[0m\n"
# define FLD_DED	"\e[31;7;1mdied\e[0m\n"

typedef struct s_rules	t_rules;
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
struct s_rules
{
	long	num_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	num_meals;
};
struct s_philo
{
	int				pos;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*last_meal_mutex;
	long			last_meal;
	int				meals;
};
struct s_data
{
	t_rules			rules;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	last_meal_mutexes[MAX_PHILOS];
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	ate_mutex;
	pthread_mutex_t	exit_mutex;
	pthread_mutex_t	sync_mutex;
	long			ate_meals;
	int				exit;
	long			start;
	int				synced;
};

// setup.c
int		sim_setup(t_data *data, int ac, char **av);
int		get_rules(t_rules *rules, int ac, char **av);
int		make_mutexes(t_data *data);
void	set_philos(t_data *data);
int		atoi_philo(char *str, long min, long max, long *dst);

// threads.c
void	*philosophing(void *arg);
int		sim_start(t_data *data);
void	sync_main_thread(t_data *data);
int		sync_philo_thread(t_philo *philo, t_data *data);
void	monitoring(t_data *data);
// threads2.c
int		forking(t_philo *philo);
int		eating(t_philo *philo, t_data *data);
int		sleeping(t_philo *philo, t_data *data);
// threads3.c
int		check_death(t_philo *philo);
int		print_state(long time, t_philo *philo, const char *state);
void	print_set_death(long time, t_philo *philo);
long	set_meal_time(t_philo *philo);

// utils.c
void	destroy_n_mutexes(t_data *data, int n);
void	join_n_threads(t_data *data, int n);
void	sim_stop(t_data *data);
long	philo_gettime(void);
// utils2.c
void	set_exit(t_data *data);
int		get_exit(t_data *data);
int		all_synced(t_data *data);
void	philo_usleep(long time);

#endif
