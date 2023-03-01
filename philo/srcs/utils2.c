/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 01:37:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 06:49:22 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_exit(t_data *data)
{
	pthread_mutex_lock(&data->exit_mutex);
	data->exit = 1;
	pthread_mutex_unlock(&data->exit_mutex);
}

int	get_exit(t_data *data)
{
	int	exit;

	pthread_mutex_lock(&data->exit_mutex);
	exit = data->exit;
	pthread_mutex_unlock(&data->exit_mutex);
	return (exit);
}

int	all_synced(t_data *data)
{
	pthread_mutex_lock(&data->sync_mutex);
	if (data->synced == data->rules.num_philos && data->start != 0)
		return (pthread_mutex_unlock(&data->sync_mutex), 1);
	pthread_mutex_unlock(&data->sync_mutex);
	return (0);
}

void	philo_usleep(long time)
{
	const long start = philo_gettime();

	while (philo_gettime() - start < time)
		usleep(5);
}

//void	wait_min_meals(t_vars *vars)
//{
//	while (1)
//	{
//		pthread_mutex_lock(&vars->ret_mutex);
//		if (vars->ret)
//			return ((void)pthread_mutex_unlock(&vars->ret_mutex));
//		if (vars->had_enough == vars->num_philos)
//			vars->ret = 1;
//		pthread_mutex_unlock(&vars->ret_mutex);
//	}
//}
