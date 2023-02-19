/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 01:37:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/19 03:44:40 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_min_meals(t_vars *vars)
{
	while (1)
	{
		pthread_mutex_lock(&vars->ret_mutex);
		if (vars->ret)
			return ((void)pthread_mutex_unlock(&vars->ret_mutex));
		if (vars->had_enough == vars->num_philos)
			vars->ret = 1;
		pthread_mutex_unlock(&vars->ret_mutex);
	}
}
