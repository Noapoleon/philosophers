/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:05:19 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/13 22:41:58 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Parses ints from av to philo values and prints errors if some are present
// Returns 0 for no errors and -1 otherwise
int	vars_setup(t_vars *vars, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf(USAGE1 USAGE2 USAGE3, av[0]), -1);
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
	make_philos(vars);

	return (0);
}

// Parses string into integer, string must represent a positive non-zero integer
// Formatting is very strict, only numbers are allowed, no whitespace and no
// negatives values
// Returns parsed int or -1 in case of error
int	atoi_philo(char *str)
{
	long	n;
	int		i;

	if (!str)
		return (-1);
	i = 0;
	n = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		if (n < INT_MIN || n > INT_MAX)
			return (-1);
		++i;
	}
	if (n == 0 || str[i] != '\0')
		return (-1);
	return (n);
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

int	make_philos(t_vars *vars)
{
	int	i;

	vars->philos = malloc(sizeof(t_philo) * vars->num_philos);
	if (vars->philos == NULL)
		return (printf(PHILO_ERR PE_ALLOC_PHILOS), -1);
	i = 0;
	while (i < vars->num_philos)
	{
		//if (pthread_create(&vars->thread, &start_routiine, NULL) != 0) // not sure but i think i need to start the threads later
		//	return (philo_terminate(vars), -1);
		vars->philos[i].pos = i + 1;
		if (i == 0)
			vars->philos[i].prev = &vars->philos[vars->num_philos - 1];
		else
			vars->philos[i].prev = &vars->philos[i - 1];
		if (i == vars->num_philos - 1)
			vars->philos[i].next = &vars->philos[0];
		else
			vars->philos[i].next = &vars->philos[i + 1];
		++i;
	}
	return (0);
}

void	*dummy_routine(void *arg)
{
	const t_philo	*philo = arg;

	printf("Creating philo #%d...\n", philo->pos);
	return (NULL); // wtf am i supposed to send here?
}

int	start_philos(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philos)
	{
		if (pthread_create(&vars->philos[i].thread, NULL, &dummy_routine, &vars->philos[i]) != 0)
			return (printf(PHILO_ERR PE_CREATE), -1);
		++i;
	}
	return (0);
}

int	join_philos(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philos)
	{
		if (pthread_join(vars->philos[i].thread, NULL) != 0)
			return (printf(PHILO_ERR PE_JOIN), -1);
		printf("Thread #%d finished.\n", i + 1);
		++i;
	}
	return (0);
}

void	philo_terminate(t_vars *vars)
{
//	int	i;

//	i = 0;
//	while (i < vars->num_philo)
//		pthread_detach(vars->philos[i]); // not sure i need to do that
	free(vars->philos);
}
