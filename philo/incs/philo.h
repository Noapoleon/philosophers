/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:10:18 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/16 04:22:51 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:54:17 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/12 23:09:49 by nlegrand         ###   ########.fr       */
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


# define USAGE1	"Usage: %s <number_of_philosophers> <time_to_die> "
# define USAGE2	"<time_to_eat> <time_to_sleep> "
# define USAGE3	"[number_of_times_each_philosopher_should_eat]\n"

# define PHILO_ERR			"\033[31;7;1m[PHILO ERROR]\033[0m "
# define PE_FORMAT			"bad format\n"
# define PE_N_PHILO			"number_of_philosophers: "
# define PE_T_DIE			"time_to_die: "
# define PE_T_EAT			"time_to_eat: "
# define PE_T_SLEEP			"time_to_sleep: "
# define PE_N_MEALS			"number_of_times_each_philosopher_should_eat: "
# define PE_RET_MUTEX		"Failed to initialize return mutex\n"
# define PE_PRINT_MUTEX		"Failed to initialize print mutex\n"
# define PE_ALLOC_PHILOS	"Failed to allocate philos array list\n"
# define PE_FORK_MUTEX		"Failed to initialize fork mutex %d\n"
# define PE_CREATE			"Failed to create thread #%d\n"
# define PE_JOIN			"Failed to join thread #%d\n"
# define SETUP_FAILED		0
# define SETUP_DONE			1

# define COL_TIM	"\033[7;1m"
# define COL_RST	"\033[0m"
# define MSG_FRK	"\033[35;1mhas taken a fork\033[0m\n" // make light purple
# define MSG_EAT	"\033[32;1mis eating\033[0m\n"
# define MSG_THK	"\033[33;1mis thinking\033[0m\n"
# define MSG_SLP	"\033[36;1mis sleeping\033[0m\n"
# define MSG_DED	"\033[31;7;5;1mdied\033[0m\n"
# define EATING		1
# define NOT_EATING	0

typedef struct s_vars	t_vars;
typedef struct s_philo	t_philo;
struct s_philo
{
	int				pos;
	pthread_t		thread;
	pthread_mutex_t	fork;
	long			last_meal; // probably should protect with mutex
	int				num_meals; // that too
	t_vars			*vars;
	t_philo			*next;
};
//struct	s_reaper
//{
//	// ntm fini d'abord les 'ing
//};
struct s_vars
{
	int				num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				num_meals_min;
	long			start;
	int				print_width;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	ret_mutex;
	int				ret;
};

// utils.c
int		atoi_philo(char *str);
void	philo_terminate(t_philo *philos, t_vars *vars);
void	destroy_n_mutexes(t_philo *philos, int count);
// setup.c
int		philo_setup(t_philo **philos, t_vars *vars, int ac, char **av);
int		vars_setup(t_vars *vars, int ac, char **av);
int		get_inputs(t_vars *vars, int ac, char **av);
void	set_print_width(t_vars *vars);
int		print_errors(t_vars *vars);
int		make_philos(t_philo **philos, t_vars *vars);
// threads.c
int		print_state(t_philo *philo, t_vars *vars, char *action, int eating);
void	*routine(void *arg);
int		start_philos(t_philo *philos, t_vars *vars);
int		join_philos(t_philo *philos, t_vars *vars);
// states.c
int	print_state(t_philo *philo, t_vars *vars, char *action, int eating);
int	forking(t_philo	*philo, t_vars *vars);
int	eating(t_philo	*philo, t_vars *vars);


// tests.c REMOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVE LATER
int	test_colors();
int	show_philos(t_philo *philos, t_vars *vars);
int	test_loop(t_philo *philos, t_vars *vars);

#endif
