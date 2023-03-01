/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:05:19 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 06:49:22 by nlegrand         ###   ########.fr       */
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
long	philo_gettime()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

//// returns the current time in milliseconds
//long	get_time(void)
//{
//	struct timeval	tv;
//	long			now;
//
//	gettimeofday(&tv, NULL);
//	now = tv.tv_sec * 1000000 + tv.tv_usec;
//	return (now);
//}
//
//void	my_usleep(long delay)
//{
//	struct timeval	start;
//	struct timeval	now;
//
//	gettimeofday(&start, NULL);
//	while (1)
//	{
//		gettimeofday(&now, NULL);
//		if ((now.tv_sec * 1000000 + now.tv_usec)
//			- (start.tv_sec * 1000000 + start.tv_usec) >= delay)
//			break ;
//	}
//}
//
//// Frees and destroys elements from t_philo and t_vars
//void	terminate_sim(t_philo *philos, t_monitor *monitors, t_vars *vars)
//{
//	destroy_n_mutexes(philos, vars->num_philos);
//	pthread_mutex_destroy(&vars->print_mutex);
//	pthread_mutex_destroy(&vars->ret_mutex);
//	pthread_mutex_destroy(&vars->sync_mutex);
//	free(philos);
//	free(monitors);
//}
