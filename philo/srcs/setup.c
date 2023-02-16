/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:39:09 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/16 04:19:59 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Gets time values from program arguments and allocates t_philo array list
int	philo_setup(t_philo **philos, t_vars *vars,
	int ac, char **av)
{
	*philos = NULL;
	if (vars_setup(vars, ac, av) == -1)
		return (-1);
	if (make_philos(philos, vars) == -1)
		return (pthread_mutex_destroy(&vars->print_mutex),
			pthread_mutex_destroy(&vars->ret_mutex), -1);
	return (0);
}

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
	vars->ret = 0;
	return (0);
}

// Gets the number inputs from the program arguments
// Returns 0 on success and -1 otherwise
int	get_inputs(t_vars *vars, int ac, char **av)
{
	struct timeval	tv;

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
	gettimeofday(&tv, NULL);
	vars->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
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

// Allocates and philos array list and inits mutexes
// Returns 0 on success and -1 otherwise
int	make_philos(t_philo **philos, t_vars *vars)
{
	t_philo	*curr;
	int	i;

	*philos = malloc(sizeof(t_philo) * vars->num_philos);
	if (*philos == NULL)
		return (printf(PHILO_ERR PE_ALLOC_PHILOS), -1);
	curr = *philos;
	i = 0;
	while (i < vars->num_philos)
	{
		curr = &(*philos)[i];
		curr->pos = i + 1;
		curr->num_meals = 0;
		curr->vars = vars;
		if (i == vars->num_philos - 1)
			curr->next = &(*philos)[0];
		else
			curr->next = &(*philos)[i + 1];
		if (pthread_mutex_init(&curr->fork, NULL) != 0)
			return (destroy_n_mutexes(*philos, i), free(*philos),
				printf(PHILO_ERR PE_FORK_MUTEX, i + 1), -1);
		++i;
	}
	return (0);
}
