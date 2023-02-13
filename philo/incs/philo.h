
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

# define COL_EAT	"\033[32;1m"
# define COL_THK	"\033[33;1m"
# define COL_SLP	"\033[36;1m"
# define COL_DIE	"\033[41;30;1;5m"
# define COL_RST	"\033[0m"

# define USAGE1	"Usage: %s <number_of_philosophers> <time_to_die> "
# define USAGE2	"<time_to_eat> <time_to_sleep> "
# define USAGE3	"[number_of_times_each_philosopher_should_eat]\n"

# define PHILO_ERR			"[PHILO_ERROR] "

# define PE_SETUP			"Setup failed!\n"
# define PE_FORMAT			"bad format\n"
# define PE_N_PHILO			"number_of_philosophers: "
# define PE_T_DIE			"time_to_die: "
# define PE_T_EAT			"time_to_eat: "
# define PE_T_SLEEP			"time_to_sleep: "
# define PE_N_MEALS			"number_of_times_each_philosopher_should_eat: "
# define PE_ALLOC_PHILOS	"make_philos > Failed to allocate philos array\n"

# define PE_START_FUNC		"Failed to start one or more philosopher threads\n"
# define PE_CREATE			"start_philos > pthread_create\n"

# define PE_JOIN_FUNC		"Failed to join all philosophers\n"
# define PE_JOIN			"join_philos > pthread_join\n"

typedef struct s_vars	t_vars;
typedef struct s_philo	t_philo;
struct s_philo
{
	t_philo		*prev; // might come in handy, remove otherwise
	int			pos;
	pthread_t	thread;
	t_philo		*next; // might come in handy, remove otherwise
};
struct s_vars
{
	int	num_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_meals_min;
	t_philo	*philos;
};

// utils.c
int		vars_setup(t_vars *vars, int ac, char **av);
int		atoi_philo(char *str);
int		print_errors(t_vars *vars);
// probably move later
int		make_philos(t_vars *vars);
int		start_philos(t_vars *vars);
int		join_philos(t_vars *vars);
void	philo_terminate(t_vars *vars);

// tests.c REMOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVE LATER
int	test_colors();
int	show_philos(t_vars *vars);

#endif
