/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:06:44 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/21 09:05:22 by nlegrand         ###   ########.fr       */
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
# define PE_SEMSYNC_OPEN	"Failed to open sync semaphore\n"
# define PE_SEMFORKS_OPEN	"Failed to open forks semaphore\n"
# define PE_FORK			"Failed to fork process #%d\n"

typedef struct s_vars	t_vars;
struct s_vars
{
	int		num_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	int		num_meals_min;
	int		print_width;
	sem_t	*sync;
	sem_t	*forks;
};
//typedef struct s_philo	t_philo;
//struct s_philo
//{
//
//};

// sems_bonus.c
void	philosophing(t_vars *vars, int pos);

// utils_bonus.c
int		atoi_philo(char *str);
void	phibo_terminate(t_vars *vars, int exit_mode);

// setup_bonus.c
int		vars_setup(t_vars *vars, int ac, char **av);
int		get_inputs(t_vars *vars, int ac, char **av);
int		print_errors(t_vars *vars);
void	set_print_width(t_vars *vars);

// tests.c // REMOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVE LATER
void	test_cmd(void);
void	test_inputs(t_vars *vars);

#endif
