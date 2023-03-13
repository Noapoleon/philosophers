/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 08:52:10 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/13 05:17:07 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Philo waits for forks >:[
void	forking(t_philo *philo, t_data *data)
{
	sem_wait(data->forking_sem);
	sem_wait(data->forks_sem);
	print_state(philo_gettime(), philo, FLD_FRK, data);
	sem_wait(data->forks_sem);
	print_state(philo_gettime(), philo, FLD_FRK, data);
	sem_post(data->forking_sem);
}

// Philo eats :]
void	eating(t_philo *philo, t_data *data)
{
	sem_wait(philo->last_sem);
	philo->last = philo_gettime();
	sem_post(philo->last_sem);
	print_state(philo->last, philo, FLD_EAT, data);
	philo_usleep(data->rules.time_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	if (data->rules.num_meals && ++philo->meals == data->rules.num_meals)
		sem_post(data->ate_sem);
}

// Philo goes to sleep :[
void	sleeping(t_philo *philo, t_data *data)
{
	print_state(philo_gettime(), philo, FLD_SLP, data);
	philo_usleep(data->rules.time_sleep);
}

// Checks the last meal time and compares it to current time
void	check_death(long time, t_philo *philo, t_data *data)
{
	sem_wait(philo->last_sem);
	if (time - philo->last > data->rules.time_die)
	{
		print_death(time, philo, data);
		close_sems(data);
		exit(PHILO_DEATH);
	}
	sem_post(philo->last_sem);
}

// Sleeps in small intervals for better precision
void	philo_usleep(long time)
{
	const long	start = philo_gettime();

	while (philo_gettime() - start < time)
		usleep(50);
}
