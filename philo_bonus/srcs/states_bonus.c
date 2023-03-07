/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 03:59:20 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/07 04:40:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	forking(t_philo *philo, t_data *data)
{
	sem_wait(data->forks_sem);
	print_state(philo_gettime(), philo, FLD_FRK, data);
	sem_wait(data->forks_sem);
	print_state(philo_gettime(), philo, FLD_FRK, data);
}

void	eating(t_philo *philo, t_data *data)
{
	//sem_wait(data->last_meal_sem); // for monitoring, name for each semaphore will have to be custom like /last_sem019 no need for malloc tho just make a custom function with a static string ("/last_sem000") // FUCK THAT MAKES A LOT OF SEMAPHORES TO UNLINK, eeeh whatever i can do it in main everytime i start the program or after or something
	print_state((philo->last = philo_gettime()), philo, FLD_EAT, data);
	//sem_post(data->last_meal_sem);
	philo_usleep(data->rules.time_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	if (++philo->meals == data->rules.num_meals)
		sem_post(data->ate_sem);
}

void	sleeping(t_philo *philo, t_data *data)
{
	print_state(philo_gettime(), philo, FLD_SLP, data);
	philo_usleep(data->rules.time_sleep);
}

void	print_state(long time, t_philo *philo, char *state, t_data *data)
{
	sem_wait(data->print_sem);
	printf(FLD_TIM FLD_POS "%s", (time - philo->start) / 1000, philo->pos,
		state);
	sem_post(data->print_sem);
}
