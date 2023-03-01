/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:52:58 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 21:54:25 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Philosopher threads routine
void	*philosophing(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = arg;
	data = philo->data;
	if (sync_philo_thread(philo, data) == -1)
		return (NULL);
	if (philo->pos % 2 == 0) // changed that to == 0 not sure what that changes
		philo_usleep(10000);
	while (1)
	{
		if (forking(philo) == -1)
			break ;
		if (eating(philo, data) == -1)
			break ;
		if (sleeping(philo, data) == -1)
			break ;
		if (print_state(philo_gettime(), philo, FLD_THK) == -1) // i think doing this like this will allow messages to be printed after the death of a philo
			break ;
	}
	return (NULL);
}

// Creates every thread
// Returns 0 on success, -1 otherwise
int	sim_start(t_data *data)
{
	int		i;
	t_philo	*curr;

	i = 0;
	while (i < data->rules.num_philos)
	{
		curr = &data->philos[i];
		if (pthread_create(&curr->thread, NULL, &philosophing, curr) != 0)
			return (printf(PHILO_ERR PE_THREAD_CREATE, i + 1),
				set_exit(data), join_n_threads(data, i), -1);
		++i;
	}
	sync_main_thread(data);
	return (0);
}

void	sync_main_thread(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->sync_mutex);
		if (data->synced == data->rules.num_philos)
		{
			pthread_mutex_unlock(&data->sync_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->sync_mutex);
	}
	pthread_mutex_lock(&data->sync_mutex);
	data->start = philo_gettime();
	pthread_mutex_unlock(&data->sync_mutex);
}

int	sync_philo_thread(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->sync_mutex);
	++data->synced;
	pthread_mutex_unlock(&data->sync_mutex);
	while (!all_synced(data))
		if (get_exit(data))
			return (-1);
	pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal = data->start;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (0);
}

void	monitoring(t_data *data)
{
	t_rules	*rules;
	int	i;

	rules = &data->rules;
	philo_usleep(20000);
	while (1)
	{
		i = 0;
		while (i < rules->num_philos)
		{
			if (get_exit(data))
				return ;
			if (check_death(&data->philos[i]))
				return (print_set_death(philo_gettime(), &data->philos[i]));
			++i;
		}
		pthread_mutex_lock(&data->ate_mutex);
		if (rules->num_meals && data->ate_meals == rules->num_philos)
			return (pthread_mutex_unlock(&data->ate_mutex), set_exit(data));
		pthread_mutex_unlock(&data->ate_mutex);
	}
}
