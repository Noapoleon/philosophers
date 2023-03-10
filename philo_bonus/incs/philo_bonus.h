/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:06:44 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/13 14:08:59 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

# define MAX_PHILOS			200
# define MIN_TIME			60
# define PHILO_DEATH		1
# define PHILO_EXIT_FAILURE	255
# define LAST_SEM_DEFAULT	"/last_sem000\0"

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
# define PE_SEMS			"Failed to create all semaphores\n"
# define PE_THREAD_CREATE	"Failed to create monitor thread #%d\n"

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
	int		pos;
	long	start;
	long	last;
	int		meals;
	sem_t	*last_sem;
};
struct s_data
{
	t_rules	rules;
	sem_t	*forks_sem;
	sem_t	*sync_sem;
	sem_t	*print_sem;
	sem_t	*forking_sem;
	sem_t	*ate_sem;
	pid_t	*pids;
	t_philo	philo;
};

// setup_bonus.c
int		sim_setup(t_data *data, int ac, char **av);
int		get_rules(t_rules *rules, int ac, char **av);
int		make_sems(t_data *data);

// sim_bonus.c
int		sim_start(t_data *data);
void	philosophing(t_philo *philo, t_data *data);
void	sim_wait_end(t_data *data);

// monitoring_bonus.c
void	start_monitoring(t_philo *philo, t_data *data);
void	*monitoring(void *arg);
int		start_meals_monitor(t_data *data);
void	*meals_monitoring(void *arg);

// actions_bonus.c
void	forking(t_philo *philo, t_data *data);
void	eating(t_philo *philo, t_data *data);
void	sleeping(t_philo *philo, t_data *data);
void	check_death(long time, t_philo *philo, t_data *data);
void	philo_usleep(long time);

// states_bonus.c
void	print_state(long time, t_philo *philo, char *state, t_data *data);
void	print_death(long time, t_philo *philo, t_data *data);
void	check_death(long time, t_philo *philo, t_data *data);

// utils_bonus.c
int		atoi_philo(char *str, long min, long max, long *dst);
void	close_sems(t_data *data);
void	unlink_sems(void);
long	philo_gettime(void);
void	kill_n_children(t_data *data, int n);

#endif
