/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:05:19 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 22:28:28 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Destroys all mutexes in data struct
void	destroy_n_mutexes(t_data *data, int n)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->ate_mutex);
	pthread_mutex_destroy(&data->exit_mutex);
	pthread_mutex_destroy(&data->sync_mutex);
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->last_meal_mutexes[i]);
		++i;
	}
}

// Wait for threads to finish their execution in order
void	join_n_threads(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_join(data->philos[i++].thread, NULL);
}

// Cleanup function for simulation
void	sim_stop(t_data *data)
{
	join_n_threads(data, data->rules.num_philos);
	destroy_n_mutexes(data, data->rules.num_philos);
}

// Returns the current time in microseconds
long	philo_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
