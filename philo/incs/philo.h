
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

# define COL_EAT	"\033[32;1m"
# define COL_THK	"\033[33;1m"
# define COL_SLP	"\033[36;1m"
# define COL_DIE	"\033[41;30;1;5m"
# define COL_RST	"\033[0m"

# define PE_FORMAT "bad format"
//# define PE_NUMPHILO	"bad

typedef struct s_vars	t_vars;
typedef struct s_philo	t_philo;
struct s_philo
{
	t_philo	*prev;
	int	pos;
	t_philo	*next;
};
struct s_vars
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_meals_min;
//	t_philo	*philos;
};

// utils.c
int	vars_setup(t_vars *vars, int ac, char **av);
int	atoi_philo(char *str);
int	print_errors(t_vars *vars);

// tests.c REMOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVE LATER
int	test_colors();

#endif
