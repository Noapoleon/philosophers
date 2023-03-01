/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 01:37:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 22:28:28 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Locks mutex and sets exit attribute to 1
void	set_exit(t_data *data)
{
	pthread_mutex_lock(&data->exit_mutex);
	data->exit = 1;
	pthread_mutex_unlock(&data->exit_mutex);
}

// Gets the exit attribute from data while locking mutexes
int	get_exit(t_data *data)
{
	int	exit;

	pthread_mutex_lock(&data->exit_mutex);
	exit = data->exit;
	pthread_mutex_unlock(&data->exit_mutex);
	return (exit);
}

// Checks if all threads are started
// Returns 1 if all are there, 0 otherwise
int	all_synced(t_data *data)
{
	pthread_mutex_lock(&data->sync_mutex);
	if (data->synced == data->rules.num_philos && data->start != 0)
		return (pthread_mutex_unlock(&data->sync_mutex), 1);
	pthread_mutex_unlock(&data->sync_mutex);
	return (0);
}

// Sleeps in small intervals for better precision
void	philo_usleep(long time)
{
	const long	start = philo_gettime();

	while (philo_gettime() - start < time)
		usleep(5);
}
