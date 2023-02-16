/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:52:58 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/16 04:28:09 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function executed at thread creation
// Stops looping when a philosopher dies
void	*routine(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = arg;
	vars = philo->vars;
	if (philo->pos % 2)
		usleep(100);
	while (1)
	{
		if (print_state(philo, vars, MSG_THK, NOT_EATING) != 0)
			return (NULL);
		if (forking(philo, vars) != 0)
			return (NULL);
		if (eating(philo, vars) != 0)
			return (NULL);
		if (print_state(philo, vars, MSG_SLP, NOT_EATING) != 0)
			return (NULL);
	}
	return (NULL); // could create other returns to handle errors
}

// Launches creation of all threads with the routine command
int	start_philos(t_philo *philos, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (printf(PHILO_ERR PE_CREATE, i + 1), -1);
		++i;
	}
	return (0);
}

// Waits for all philosopher threads to return
int	join_philos(t_philo *philos, t_vars *vars)
{
	int	i;
	int	*res;

	i = 0;
	while (i < vars->num_philos)
	{
		if (pthread_join(philos[i].thread, (void **)&res) != 0)
			return (printf(PHILO_ERR PE_JOIN, i + 1), -1);
		++i;
	}
	return (0);
}
