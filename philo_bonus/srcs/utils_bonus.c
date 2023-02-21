/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:08:50 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/21 08:59:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	phibo_terminate(t_vars *vars, int exit_mode)
{
	sem_close(vars->sync);
	sem_close(vars->forks);
	exit(exit_mode);
}
