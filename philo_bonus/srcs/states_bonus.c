/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 03:59:20 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/12 09:07:10 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Prints given status message with given timestamp
void	print_state(long time, t_philo *philo, char *state, t_data *data)
{
	sem_wait(data->print_sem);
	printf(FLD_TIM FLD_POS "%s", (time - philo->start) / 1000, philo->pos,
		state);
	sem_post(data->print_sem);
}

// Prints the death message and doesn't unlock the semaphore so there won't be
// subsequent messages
void	print_death(long time, t_philo *philo, t_data *data)
{
	sem_wait(data->print_sem);
	printf(FLD_TIM FLD_POS FLD_DED, (time - philo->start) / 1000, philo->pos);
}
