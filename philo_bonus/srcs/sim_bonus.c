/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:24:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/12 08:31:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Forks process and starts a monitor thread as well as a looping philosophing
// function
// Returns 0 on success, -1 otherwise
int	sim_start(t_data *data)
{
	const pid_t	main_pid = getpid();
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
			data->pids[i] = main_pid;
			philosophing(&data->philo, data);
		}
		++i;
	}
	i = 0;
	while (i++ < data->rules.num_philos * 2)
		sem_post(data->sync_sem);
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = arg;
	philo = &data->philo;
	while (1)
	{
		check_death(philo_gettime(), philo, data);
		philo_usleep(50, philo, data);
	}
}

// Routine for philosopher
void	philosophing(t_philo *philo, t_data *data)
{
	pthread_t monitor; // test

	sem_wait(data->sync_sem);
	philo->start = philo_gettime();
	philo->last = philo->start;
	pthread_create(&monitor, NULL, &monitoring, data); // test
	if (philo->pos % 2 == 0)
		philo_usleep(usleep(10000), philo, data);
	while (1)
	{
		forking(philo, data); // add death check
		eating(philo, data);
		if (philo->meals == data->rules.num_meals)
		{
			sem_close(data->forks_sem);
			sem_close(data->sync_sem);
			sem_close(data->print_sem);
			sem_close(data->forking_sem);
			exit(PHILO_ATE); // might cause valgrind problems
		}
		sleeping(philo, data);
		print_state(philo_gettime(), philo, FLD_THK, data);
		check_death(philo_gettime(), philo, data);
	}
}

void	sim_wait_end(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->rules.num_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			kill_n_children(data, data->rules.num_philos);
			break ;
		}
		++i;
	}
	destroy_sems(data); // trying to call that from dying philo
	//		data->pids[i] = pid; // dont know what this line was doing here so ill just comment it
}
