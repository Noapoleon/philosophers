/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 03:59:20 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/12 08:32:59 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	forking(t_philo *philo, t_data *data) // CHANGE THIS NOW otherwise death will be delayed in some situations
{
	sem_wait(data->forking_sem); // wont prevent 4 310 200 100 but SHOULD prevent 5 800 200 200 death
	sem_wait(data->forks_sem);
	check_death(philo_gettime(), philo, data);
	print_state(philo_gettime(), philo, FLD_FRK, data);
	sem_wait(data->forks_sem);
	check_death(philo_gettime(), philo, data);
	print_state(philo_gettime(), philo, FLD_FRK, data);
	sem_post(data->forking_sem);
}

void	eating(t_philo *philo, t_data *data)
{
	print_state((philo->last = philo_gettime()), philo, FLD_EAT, data);
	philo_usleep(data->rules.time_eat, philo, data);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	++philo->meals;
}

void	sleeping(t_philo *philo, t_data *data)
{
	print_state(philo_gettime(), philo, FLD_SLP, data);
	philo_usleep(data->rules.time_sleep, philo, data);
}

void	print_state(long time, t_philo *philo, char *state, t_data *data)
{
	sem_wait(data->print_sem);
	printf(FLD_TIM FLD_POS "%s", (time - philo->start) / 1000, philo->pos,
		state);
	sem_post(data->print_sem);
}

void	print_death(long time, t_philo *philo, t_data *data)
{
	sem_wait(data->print_sem);
	printf(FLD_TIM FLD_POS FLD_DED, (time - philo->start) / 1000, philo->pos);
	//sem_post(data->print_sem); // so that it doesn't unlock the semaphore
}

void	check_death(long time, t_philo *philo, t_data *data)
{
	if (time - philo->last > data->rules.time_die)
	{
		//print_state(time, philo, FLD_DED, data);
		print_death(time, philo, data);
		sem_close(data->forks_sem);
		sem_close(data->sync_sem);
		sem_close(data->print_sem);
		sem_close(data->forking_sem);
		exit(PHILO_DED);
	}
}
