/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:50:45 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/21 09:08:06 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Parses ints from av to philo values and prints errors if some are present
// Returns 0 for no errors and -1 otherwise
int	vars_setup(t_vars *vars, int ac, char **av)
{
	if (get_inputs(vars, ac, av) == -1)
		return (-1);
	vars->sync = sem_open("/sem_sync", O_CREAT, 0644, 0);
	if (vars->sync == SEM_FAILED)
		return (printf(PHILO_ERR PE_SEMSYNC_OPEN), -1);
	vars->forks = sem_open("/sem_forks", O_CREAT, 0644, vars->num_philos);
	if (vars->forks == SEM_FAILED)
		return (printf(PHILO_ERR PE_SEMFORKS_OPEN), -1);
	//vars->start = 0;
	//vars->ret = 0;
	//vars->had_enough = 0;
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
