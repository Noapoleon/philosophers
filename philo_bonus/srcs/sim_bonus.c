/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:24:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/07 04:40:03 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Forks process and starts a monitor thread as well as a looping philosophing
// function
// Returns 0 on success, -1 otherwise
int	sim_start(t_data *data)
{
	pid_t		pid;
	//pthread_t	monitor;
	int			i;

	i = 0;
	while (i < data->rules.num_philos)
	{
		data->philo.pos = i + 1;
		pid = fork();
		if (pid == -1)
			return (kill_n_children(data, i), -1);
		if (pid != 0)
			data->pids[i] = pid;
		else
		{
			//if (pthread_create(&monitor, NULL, &monitoring, data) != 0) // THIS IS NOT PROPER ERROR HANDLING, WONT DELETE SEMAPHORES
			//	return (printf(PHILO_ERR PE_THRAD_CREATE),
			//		kill_n_children(data, i + 1), -1); // +1 so it kills this child that has already been created
			philosophing(&data->philo, data);
		}
		++i;
	}
	i = 0;
	while (i++ < data->rules.num_philos * 2)
		sem_post(data->sync_sem);
	return (0);
}

// Routine for philosopher
void	philosophing(t_philo *philo, t_data *data)
{
	sem_wait(data->sync_sem);
	philo->start = philo_gettime();
	philo->last = philo->start;
	if (philo->pos % 2 == 0)
		philo_usleep(usleep(10000));
	while (1)
	{
		forking(philo, data);
		eating(philo, data);
		sleeping(philo, data);
		print_state(philo_gettime(), philo, FLD_THK, data);
	}
}

// Routine for monitor
//void	monitoring(void *arg)
//{
//	t_data	*data;
//	t_philo	*philo;
//	long	now;
//
//	data = arg;
//	philo = &data->philo;
//	sem_wait(data->sync_sem);
//	philo_usleep(20000);
//	while (1)
//	{
//		sem_wait(last_meal_sem);
//		now = philo_gettime();
//		if (now - philo->last > data->rules.time_die)
//		{
//			print_state(now, philo, FLD_DED, data); // not written yet // might cause death from multiple philos to be displayed
//			sem_post(data->exit_sem);
//		}
//		// might need to but a small sleep in there to reduce lag, like 50 microseconds or something
//		philo_usleep(50);
//	}
//}
