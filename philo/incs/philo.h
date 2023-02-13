
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

typedef struct s_vars	t_vars;
struct s_vars
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_meals_min;
};

// utils.c
int	vars_setup(t_vars *vars, int ac, char **av);
int	atoi_philo(char *str);
int	print_errors(t_vars *vars);

#endif
