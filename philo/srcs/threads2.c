/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:16:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/19 03:42:49 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Sets the meal time in the philo struct safely by locking the mutex
long	set_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_mutex);
	philo->last = get_time();
	pthread_mutex_unlock(&philo->last_mutex);
	return (philo->last);
}

// Mutex-protected print of philosophers actions with colors
int	print_state(t_philo *philo, t_vars *vars, char *action, long time)
{
	pthread_mutex_lock(&vars->print_mutex);
	pthread_mutex_lock(&vars->ret_mutex);
	if (vars->ret)
	{
		pthread_mutex_unlock(&vars->ret_mutex);
		pthread_mutex_unlock(&vars->print_mutex);
		return (1);
	}
	printf("\033[7;1m%05ld\033[0m %*.d %s", time - vars->start,
		vars->print_width, philo->pos, action);
	pthread_mutex_unlock(&vars->ret_mutex);
	pthread_mutex_unlock(&vars->print_mutex);
	return (0);
}

// Locks ret mutex and outputs the death message
// Setting ret to 1 will prevent living philosophers to print further status
// messages
int	set_death(t_vars *vars, t_philo *philo, long time)
{
	pthread_mutex_lock(&vars->print_mutex);
	pthread_mutex_lock(&vars->ret_mutex);
	if (vars->ret)
	{
		pthread_mutex_unlock(&vars->ret_mutex);
		pthread_mutex_unlock(&vars->print_mutex);
		return (1);
	}
	vars->ret = 1;
	printf("\033[7;1m%05ld\033[0m %*.d %s", time - vars->start,
		vars->print_width, philo->pos, MSG_DED);
	pthread_mutex_unlock(&vars->ret_mutex);
	pthread_mutex_unlock(&vars->print_mutex);
	return (0);
}

// Picks up forks when available
// Returns 0 if success, 1 otherwise or when one of the philosophers died
int	forking(t_philo	*philo, t_vars *vars)
{
	pthread_mutex_lock(&philo->fork);
	if (print_state(philo, vars, MSG_FRK, get_time()) != 0)
		return (pthread_mutex_unlock(&philo->fork), 1);
	pthread_mutex_lock(&philo->next->fork);
	if (print_state(philo, vars, MSG_FRK, get_time()) != 0)
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork), 1);
	return (0);
}

// Eats for time_to_eat
int	eating(t_philo *philo, t_vars *vars)
{
	if (print_state(philo, vars, MSG_EAT, set_meal_time(philo)) != 0)
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork), 1);
	my_usleep(vars->time_eat);
	++philo->meals;
	if (philo->meals == vars->num_meals_min)
		++vars->had_enough;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (0);
}
