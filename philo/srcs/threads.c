/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:52:58 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/22 12:29:48 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Philosopher threads routine
void	*philosophing(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = arg;
	vars = philo->vars;
	pthread_mutex_lock(&vars->sync_mutex);
	++vars->sync_count;
	pthread_mutex_unlock(&vars->sync_mutex);
	while (vars->sync_count != vars->num_philos)
		;
	philo->start = get_time();
	philo->last = philo->start;
	if (philo->pos % 2)
		my_usleep(500);
	while (1)
	{
		if (print_state(philo, vars, MSG_THK, get_time()) != 0)
			return (NULL);
		if (forking(philo, vars) != 0)
			return (NULL);
		if (eating(philo, vars) != 0)
			return (NULL);
		if (print_state(philo, vars, MSG_SLP, get_time()) != 0)
			return (NULL);
		my_usleep(vars->time_sleep);
	}
	return (NULL);
}

// Monitor threads routine
void	*monitoring(void *arg)
{
	t_monitor	*monitor;
	t_philo		*philo;
	t_vars		*vars;
	long		now;

	monitor = arg;
	philo = monitor->philo;
	vars = monitor->vars;
	while (vars->sync_count != vars->num_philos)
		;
	while (philo->start == -1)
		;
	while (1)
	{
		now = get_time();
		pthread_mutex_lock(&philo->last_mutex);
		if ((now - philo->last) >= vars->time_die) // lost precision because of get_time
		{
//			printf("num %d -> now - philo->last = %ld\n", philo->pos, now - philo->last);
//			printf("time_die = %ld\n", vars->time_die);
			if (set_death(vars, philo, now) != 0)
				return (pthread_mutex_unlock(&philo->last_mutex), NULL);
		}
		pthread_mutex_unlock(&philo->last_mutex);
	}
	return (NULL);
}

// Launches creation of all threads with the routine command
int	start_sim(t_philo *philos, t_monitor *monitors, t_vars *vars)
{
	int	i;
	long	before;
	long	after;

	vars->start = get_time();
	i = 0;
	before = get_time();
	while (i < vars->num_philos)
		if (launch_thread_duo(philos, monitors, vars, i++) != 0)
			return (-1);
	after = get_time();
	printf("delay -> %ld\n", after - before);
	return (0);
}

int	launch_thread_duo(t_philo *philos, t_monitor *monitors, t_vars *vars, int i)
{
	//philos[i].last = vars->start; // put back later maybe
	if (pthread_create(&philos[i].thread, NULL, &philosophing, &philos[i]) != 0)
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
