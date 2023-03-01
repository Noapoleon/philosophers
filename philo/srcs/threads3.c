/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:16:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 22:30:02 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	const long	now = philo_gettime();

	pthread_mutex_lock(philo->last_meal_mutex);
	if (now - philo->last_meal > philo->data->rules.time_die)
		return (pthread_mutex_unlock(philo->last_meal_mutex), 1);
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (0);
}

// Prints a status message for every status change of given philosopher
int	print_state(long time, t_philo *philo, const char *state)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->exit_mutex);
	if (philo->data->exit)
	{
		pthread_mutex_unlock(&philo->data->exit_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (-1);
	}
	printf(FLD_TIM FLD_POS "%s", (time - philo->data->start) / 1000, philo->pos,
		state);
	pthread_mutex_unlock(&philo->data->exit_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

// Prints a death message  and sets exit to one
void	print_set_death(long time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->exit_mutex);
	if (philo->data->exit)
	{
		pthread_mutex_unlock(&philo->data->exit_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	philo->data->exit = 1;
	printf(FLD_TIM FLD_POS FLD_DED, (time - philo->data->start) / 1000,
		philo->pos);
	pthread_mutex_unlock(&philo->data->exit_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// Alternative function to philo_gettime which also sets the last meal time of
// the philo
// Returns the current time in microseconds
long	set_meal_time(t_philo *philo)
{
	const long	now = philo_gettime();

	pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal = now;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (now);
}
