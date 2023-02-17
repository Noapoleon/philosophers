/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:16:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/17 19:38:54 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Sets the meal time in the philo struct safely by locking the mutex
long	set_meal_time(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->last_mutex);
	philo->last = get_now_time();
	now = philo->last;
	pthread_mutex_unlock(&philo->last_mutex);
	return (now);
}

// Mutex-protected print of philosophers actions with colors
int	print_state(t_philo *philo, t_vars *vars, char *action, int eating)
{
	long	now;

	if (eating)
		now = set_meal_time(philo);
	else
		now = get_now_time();
	pthread_mutex_lock(&vars->print_mutex);
	pthread_mutex_lock(&vars->ret_mutex);
	if (vars->ret)
		return (pthread_mutex_unlock(&vars->ret_mutex),
			pthread_mutex_unlock(&vars->print_mutex), 1);
	pthread_mutex_unlock(&vars->ret_mutex);
	printf("\033[7;1m%05ld\033[0m %*.d %s", now - vars->start,
		vars->print_width, philo->pos, action);
	pthread_mutex_unlock(&vars->print_mutex);
	return (0);
}

// Locks ret mutex and outputs the death message
// Setting ret to 1 will prevent living philosophers to print further status
// messages
void	set_death(t_vars *vars, t_philo *philo, long now)
{
	pthread_mutex_lock(&vars->print_mutex);
	pthread_mutex_lock(&vars->ret_mutex);
	if (vars->ret)
	{
		pthread_mutex_unlock(&vars->ret_mutex);
		pthread_mutex_unlock(&vars->print_mutex);
		return ;
	}
	vars->ret = 1;
	printf("\033[7;1m%05ld\033[0m %*.d %s", now - vars->start,
		vars->print_width, philo->pos, MSG_DED);
	pthread_mutex_unlock(&vars->ret_mutex);
	pthread_mutex_unlock(&vars->print_mutex);
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
int	eating(t_philo *philo, t_vars *vars)
{
	if (print_state(philo, vars, MSG_EAT, EATING) != 0)
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork), 1);
	usleep(vars->time_eat);
	++philo->num_meals; // protect with mutex for monitor
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (0);
}
