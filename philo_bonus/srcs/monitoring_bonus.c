/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 03:13:35 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/14 19:01:06 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Creates meal semaphore and monitor thread safely
void	start_monitoring(t_philo *philo, t_data *data)
{
	pthread_t	monitor;
	static char	sem_name[13] = LAST_SEM_DEFAULT;
	int			i;

	i = philo->pos;
	sem_name[11] = i % 10 + '0';
	i /= 10;
	sem_name[10] = i % 10 + '0';
	i /= 10;
	sem_name[9] = i % 10 + '0';
	philo->last_sem = sem_open(sem_name, O_CREAT, 0644, 1);
	if (philo->last_sem == SEM_FAILED)
	{
		close_sems(data);
		exit(PHILO_EXIT_FAILURE);
	}
	if (pthread_create(&monitor, NULL, &monitoring, data) != 0)
	{
		sem_close(philo->last_sem);
		close_sems(data);
		exit(PHILO_EXIT_FAILURE);
	}
	pthread_detach(monitor);
}

// Routine function for monitor threads
void	*monitoring(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = arg;
	philo = &data->philo;
	while (1)
	{
		check_death(philo_gettime(), philo, data);
		philo_usleep(50);
	}
}

// Creates meals counter thread and returns -1 if it failed
int	start_meals_monitor(t_data *data)
{
	pthread_t	meals_thread;

	if (data->rules.num_meals)
	{
		if (pthread_create(&meals_thread, NULL, &meals_monitoring, data) != 0)
			return (-1);
		pthread_detach(meals_thread);
	}
	return (0);
}

// Counts meals and terminates process when all have eaten enough
void	*meals_monitoring(void *arg)
{
	t_data	*data;
	int		count;

	data = arg;
	count = 0;
	while (count != data->rules.num_philos)
	{
		sem_wait(data->ate_sem);
		++count;
	}
	kill_n_children(data, data->rules.num_philos);
	close_sems(data);
	unlink_sems();
	free(data->pids);
	exit(EXIT_SUCCESS);
}
