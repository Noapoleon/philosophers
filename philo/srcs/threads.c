/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:52:58 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/17 01:10:50 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Philosopher threads routine
void	*philosophing(void *arg)
{
	t_philo			*philo;
	t_vars			*vars;

	philo = arg;
	vars = philo->vars;
	set_meal_time(philo); // might complain return value is ignored, maybe use (void)
	if (philo->pos % 2)
		usleep(200);
	//set_meal_time(philo); // might complain return value is ignored, maybe use (void) // old position, testing with above one
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
		usleep(vars->time_sleep);
	}
	return (NULL); // could create other returns to handle errors
}

// Monitor threads routine
void	*monitoring(void *arg) // monitor routine
{
	t_monitor	*monitor;
	t_philo		*philo;
	t_vars		*vars;
	long		now;

	monitor = arg;
	philo = monitor->philo;
	vars = monitor->vars;
	usleep(200);
	if (philo->pos % 2)
		usleep(200);
	while (1)
	{
		// usleep can probably be implemented easily inside here, - 1ms
		pthread_mutex_lock(&vars->ret_mutex);
		if (vars->ret)
			return (pthread_mutex_unlock(&vars->ret_mutex), NULL);
		pthread_mutex_unlock(&vars->ret_mutex);
		now = get_now_time();
		pthread_mutex_lock(&philo->last_mutex);
		if ((now - philo->last) * 1000 >= vars->time_die)
		{
			set_death(vars, philo, now);
			printf("death set here\n");
		}
		pthread_mutex_unlock(&philo->last_mutex);
	}
	return (NULL);
}

// Launches creation of all threads with the routine command
int	start_sim(t_philo *philos, t_monitor *monitors, t_vars *vars)
{
	int	i;

	vars->start = get_now_time();
	i = 0;
	while (i < vars->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &philosophing,
			&philos[i]) != 0)
		{
			pthread_mutex_lock(&vars->ret_mutex);
			vars->ret = 1;
			pthread_mutex_unlock(&vars->ret_mutex);
			join_n_threads(philos, monitors, i, i - 1);
			return (printf(PHILO_ERR PE_CREATE, i + 1), -1);
		}
		if (pthread_create(&monitors[i].thread, NULL, &monitoring,
			&monitors[i]) != 0)
		{
			pthread_mutex_lock(&vars->ret_mutex);
			vars->ret = 1;
			pthread_mutex_unlock(&vars->ret_mutex);
			join_n_threads(philos, monitors, i, i);
			return (printf(PHILO_ERR PE_CREATE, i + 1), -1);
		}
		++i;
	}
	return (0);
}

// Joins threads for philosophers and monitors to the specified amount
int	join_n_threads(t_philo *philos, t_monitor *monitors,
	int num_philos, int num_monitors)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	while (philos && i < num_philos)
		if (pthread_join(philos[i++].thread, NULL) != 0 && ++error)
			printf(PHILO_ERR PE_JOIN_PHILO, i);
	i = 0;
	while (monitors && i < num_monitors)
		if (pthread_join(monitors[i++].thread, NULL) != 0 && ++error)
			printf(PHILO_ERR PE_JOIN_MONITOR, i);
	return (error);
}
