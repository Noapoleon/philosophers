/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:16:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/16 04:27:18 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Mutex-protected print of philosophers actions with colors
int	print_state(t_philo *philo, t_vars *vars, char *action, int eating)
{
	struct timeval	tv;
	long			now;
	
	pthread_mutex_lock(&vars->print_mutex);
	pthread_mutex_lock(&vars->ret_mutex);
	if (vars->ret)
		return (pthread_mutex_unlock(&vars->print_mutex), 1);
	pthread_mutex_unlock(&vars->ret_mutex);
	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (eating)
		philo->last_meal = now;
	printf("\033[7;1m%05ld\033[0m %*.d %s", now - vars->start,
		vars->print_width, philo->pos, action);
	pthread_mutex_unlock(&vars->print_mutex);
	return (0);
}

// Picks up forks when available
// Returns 0 if success, 1 otherwise or when one of the philosophers died
int	forking(t_philo	*philo, t_vars *vars)
{
	pthread_mutex_lock(&philo->fork);
	if (print_state(philo, vars, MSG_FRK, NOT_EATING) != 0)
		return (pthread_mutex_unlock(&philo->fork), 1);
	pthread_mutex_lock(&philo->next->fork);
	if (print_state(philo, vars, MSG_FRK, NOT_EATING) != 0)
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork), 1);
	return (0);
}

// Eats for time_to_eat
int	eating(t_philo	*philo, t_vars *vars)
{
	if (print_state(philo, vars, MSG_EAT, EATING) != 0)
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork), 1);
	usleep(vars->time_eat); // check weird delay thing (about 10ms, which is BAD!!)
	++philo->num_meals; // protect with mutex
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (0);
}
