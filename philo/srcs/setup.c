/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:39:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/22 10:33:57 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Parses ints from av to philo values and prints errors if some are present
// Returns 0 for no errors and -1 otherwise
int	vars_setup(t_vars *vars, int ac, char **av)
{
	if (get_inputs(vars, ac, av) == -1)
		return (-1);
	if (pthread_mutex_init(&vars->print_mutex, NULL) != 0)
		return (printf(PHILO_ERR PE_PRINT_MUTEX), -1);
	if (pthread_mutex_init(&vars->ret_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&vars->print_mutex),
			printf(PHILO_ERR PE_RET_MUTEX), -1);
	if (pthread_mutex_init(&vars->sync_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&vars->print_mutex),
			pthread_mutex_destroy(&vars->ret_mutex),
			printf(PHILO_ERR PE_SYNC_MUTEX), -1);
	vars->start = 0;
	vars->ret = 0;
	vars->had_enough = 0;
	vars->sync_count = 0;
	return (0);
}

// Gets the number inputs from the program arguments
// Returns 0 on success and -1 otherwise
int	get_inputs(t_vars *vars, int ac, char **av)
{
	vars->num_philos = atoi_philo(av[1]);
	vars->time_die = atoi_philo(av[2]);
	vars->time_eat = atoi_philo(av[3]);
	vars->time_sleep = atoi_philo(av[4]);
	if (ac == 6)
		vars->num_meals_min = atoi_philo(av[5]);
	else
		vars->num_meals_min = 0;
	if (print_errors(vars) != 0)
		return (-1);
	vars->time_die *= 1000;
	vars->time_eat *= 1000;
	vars->time_sleep *= 1000;
	set_print_width(vars);
	return (0);
}

// Prints error messages for bad input values
// Returns 0 for no errros and a nonzero positive number if there are errors
int	print_errors(t_vars	*vars)
{
	int	errors;

	errors = 0;
	if (vars->num_philos == -1 && ++errors)
		printf(PHILO_ERR PE_N_PHILO PE_FORMAT);
	if (vars->time_die == -1 && ++errors)
		printf(PHILO_ERR PE_T_DIE PE_FORMAT);
	if (vars->time_eat == -1 && ++errors)
		printf(PHILO_ERR PE_T_EAT PE_FORMAT);
	if (vars->time_sleep == -1 && ++errors)
		printf(PHILO_ERR PE_T_SLEEP PE_FORMAT);
	if (vars->num_meals_min == -1 && ++errors)
		printf(PHILO_ERR PE_N_MEALS PE_FORMAT);
	return (errors);
}

// Gets width variable for printing philosopher number
void	set_print_width(t_vars *vars)
{
	int	pow;
	int	len;

	pow = 1;
	len = 1;
	while (vars->num_philos / pow >= 10)
	{
		pow *= 10;
		++len;
	}
	vars->print_width = len;
}
