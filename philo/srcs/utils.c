/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:05:19 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/19 03:47:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

// Helper function for setup when mutex init fails to destroy previous ones
void	destroy_n_mutexes(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].fork);
		pthread_mutex_destroy(&philos[i].last_mutex);
		++i;
	}
}

// returns the current time in milliseconds
long	get_time(void)
{
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (now);
}

void	my_usleep(long delay)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		if ((now.tv_sec * 1000000 + now.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec) >= delay)
			break ;
	}
}

// Frees and destroys elements from t_philo and t_vars
void	terminate_sim(t_philo *philos, t_monitor *monitors, t_vars *vars)
{
	destroy_n_mutexes(philos, vars->num_philos);
	pthread_mutex_destroy(&vars->print_mutex);
	pthread_mutex_destroy(&vars->ret_mutex);
	free(philos);
	free(monitors);
}
