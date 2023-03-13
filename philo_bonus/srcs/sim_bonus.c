/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:24:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/13 05:24:05 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Forks process and starts a monitor thread as well as a looping philosophing
// function
// Returns 0 on success, -1 otherwise
int	sim_start(t_data *data)
{
	pid_t		pid;
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
			free(data->pids);
			philosophing(&data->philo, data);
		}
		++i;
	}
	i = 0;
	while (i++ < data->rules.num_philos)
		sem_post(data->sync_sem);
	return (0);
}

// Routine for philosopher
void	philosophing(t_philo *philo, t_data *data)
{
	sem_wait(data->sync_sem);
	philo->start = philo_gettime();
	philo->last = philo->start;
	start_monitoring(philo, data);
	if (philo->pos % 2 == 0)
		philo_usleep(usleep(10000));
	while (1)
	{
		forking(philo, data);
		eating(philo, data);
		sleeping(philo, data);
		print_state(philo_gettime(), philo, FLD_THK, data);
		check_death(philo_gettime(), philo, data);
	}
}

// Waits for each philosopher to return
// If one philosopher returns with an error code all other philos are killed
// and simulation terminates
void	sim_wait_end(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->rules.num_philos)
	{
		waitpid(-1, &ret, 0);
		if (WIFEXITED(ret))
		{
			kill_n_children(data, data->rules.num_philos);
			break ;
		}
		++i;
	}
}
