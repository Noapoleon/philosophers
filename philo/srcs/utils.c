/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:05:19 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/13 03:10:03 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Parses ints from av to philo values and prints errors if some are present
// Returns 0 for no errors and -1 otherwise
int	vars_setup(t_vars *vars, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("Usage: %s <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_should_eat]\n", av[0]), -1);
	vars->num_philo = atoi_philo(av[1]);
	vars->time_die = atoi_philo(av[2]);
	vars->time_eat = atoi_philo(av[3]);
	vars->time_sleep = atoi_philo(av[4]);
	if (ac == 6)
		vars->num_meals_min = atoi_philo(av[5]);
	else
		vars->num_meals_min = -2;
	if (print_errors(vars) != 0)
		return (-1);
	return (0);
}

// Parses string into integer, string must represent a positive non-zero integer
// Returns parsed int or -1 in case of error
int	atoi_philo(char *str)
{
	long	n;
	int		i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		++i;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	n = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		if (n < INT_MIN || n > INT_MAX)
			return (-1);
		++i;
	}
	if (n == 0)
		return (-1);
	return (n);
}

// Prints error messages for bad input values
// Returns 0 for no errros and a nonzero positive number if there are errors
int	print_errors(t_vars	*vars)
{
	int	errors;

	errors = 0;
	if (vars->num_philo == -1 && ++errors)
		printf("[PHILO ERROR] number_of_philosophers: bad value\n");
	if (vars->time_die == -1 && ++errors)
		printf("[PHILO ERROR] time_to_die: bad value\n");
	if (vars->time_eat == -1 && ++errors)
		printf("[PHILO ERROR] time_to_eat: bad value\n");
	if (vars->time_sleep == -1 && ++errors)
		printf("[PHILO ERROR] time_to_sleep: bad value\n");
	if (vars->num_meals_min == -1 && ++errors)
		printf("[PHILO ERROR] number_of_times_each_philosopher_should_eat: \
bad value\n");
	return (errors);
}
