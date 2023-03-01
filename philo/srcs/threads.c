/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:52:58 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 07:10:38 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Philosopher threads routine
void	*philosophing(void *arg)
{
	t_philo	*philo;
	t_data	*data; // not necessary
	//t_rules	*rules; // not necessary

	philo = arg;
	data = philo->data; // not necessary
	//rules = &data->rules; // not necessary
	if (sync_philo_thread(philo, data) == -1)
		return (NULL);
	if (philo->pos % 2)
		philo_usleep(10000);
	while (1)
	{
		if (get_exit(data)) // for monitor testing
			break ;
		//if (forking == -1)
		//	break ;
		//if (eating == -1)
		//	break ;
		//if (sleeping == -1)
		//	break ;
		//if (thinking == -1)
		//	break ;
	}
	return (NULL);
}

// Creates every thread
// Returns 0 on success, -1 otherwise
int	sim_start(t_data *data)
{
	int		i;
	t_philo	*curr;

	// wait for threads and sleep a bit
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

void	monitoring(t_data *data) // more tweaking needed
{
	t_rules	*rules;
	int	i;

	rules = &data->rules;
	while (!all_synced(data))
		if (get_exit(data))
			return ;
	philo_usleep(20000);
	while (1)
	{
		i = 0;
		while (i < rules->num_philos)
		{
			if (get_exit(data))
				return ;
			if (check_death(&data->philos[i]))
				return (set_exit(data));
			++i;
		}
		// check ate_enough here
	}
}

//// Philosopher threads routine
//void	*philosophing(void *arg)
//{
//	t_philo	*philo;
//	t_vars	*vars;
//
//	philo = arg;
//	vars = philo->vars;
//	pthread_mutex_lock(&vars->sync_mutex);
//	++vars->sync_count;
//	pthread_mutex_unlock(&vars->sync_mutex);
//	while (vars->sync_count != vars->num_philos)
//		;
//	philo->start = get_time();
//	philo->last = philo->start;
//	if (philo->pos % 2)
//		my_usleep(500);
//	while (1)
//	{
//		if (print_state(philo, vars, MSG_THK, get_time()) != 0)
//			return (NULL);
//		if (forking(philo, vars) != 0)
//			return (NULL);
//		if (eating(philo, vars) != 0)
//			return (NULL);
//		if (print_state(philo, vars, MSG_SLP, get_time()) != 0)
//			return (NULL);
//		my_usleep(vars->time_sleep);
//	}
//	return (NULL);
//}
//
//// Monitor threads routine
//void	*monitoring(void *arg)
//{
//	t_monitor	*monitor;
//	t_philo		*philo;
//	t_vars		*vars;
//	long		now;
//
//	monitor = arg;
//	philo = monitor->philo;
//	vars = monitor->vars;
//	while (vars->sync_count != vars->num_philos)
//		;
//	while (philo->start == -1)
//		;
//	while (1)
//	{
//		now = get_time();
//		pthread_mutex_lock(&philo->last_mutex);
//		if ((now - philo->last) >= vars->time_die) // lost precision because of get_time
//		{
////			printf("num %d -> now - philo->last = %ld\n", philo->pos, now - philo->last);
////			printf("time_die = %ld\n", vars->time_die);
//			if (set_death(vars, philo, now) != 0)
//				return (pthread_mutex_unlock(&philo->last_mutex), NULL);
//		}
//		pthread_mutex_unlock(&philo->last_mutex);
//	}
//	return (NULL);
//}
//
//// Launches creation of all threads with the routine command
//int	start_sim(t_philo *philos, t_monitor *monitors, t_vars *vars)
//{
//	int	i;
//	long	before;
//	long	after;
//
//	vars->start = get_time();
//	i = 0;
//	before = get_time();
//	while (i < vars->num_philos)
//		if (launch_thread_duo(philos, monitors, vars, i++) != 0)
//			return (-1);
//	after = get_time();
//	printf("delay -> %ld\n", after - before);
//	return (0);
//}
//
//int	launch_thread_duo(t_philo *philos, t_monitor *monitors, t_vars *vars, int i)
//{
//	//philos[i].last = vars->start; // put back later maybe
//	if (pthread_create(&philos[i].thread, NULL, &philosophing, &philos[i]) != 0)
//	{
//		pthread_mutex_lock(&vars->ret_mutex);
//		vars->ret = 1;
//		pthread_mutex_unlock(&vars->ret_mutex);
//		join_n_threads(philos, monitors, i, i - 1);
//		return (printf(PHILO_ERR PE_CREATE, i + 1), -1);
//	}
//	if (pthread_create(&monitors[i].thread, NULL, &monitoring,
//			&monitors[i]) != 0)
//	{
//		pthread_mutex_lock(&vars->ret_mutex);
//		vars->ret = 1;
//		pthread_mutex_unlock(&vars->ret_mutex);
//		join_n_threads(philos, monitors, i, i);
//		return (printf(PHILO_ERR PE_CREATE, i + 1), -1);
//	}
//	return (0);
//}
//
//// Joins threads for philosophers and monitors to the specified amount
//int	join_n_threads(t_philo *philos, t_monitor *monitors,
//	int num_philos, int num_monitors)
//{
//	int	i;
//	int	error;
//
//	error = 0;
//	i = 0;
//	while (philos && i < num_philos)
//		if (pthread_join(philos[i++].thread, NULL) != 0 && ++error)
//			printf(PHILO_ERR PE_JOIN_PHILO, i);
//	i = 0;
//	while (monitors && i < num_monitors)
//		if (pthread_join(monitors[i++].thread, NULL) != 0 && ++error)
//			printf(PHILO_ERR PE_JOIN_MONITOR, i);
//	return (error);
//}
