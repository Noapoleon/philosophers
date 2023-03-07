/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:07:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/07 03:08:17 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Unimportant function :]
int	main(int ac, char **av)
{
	t_data	data;

	if (sim_setup(&data, ac, av) == -1)
		return (1);
	if (sim_start(&data) == -1)
		return (destroy_sems(&data), 2);
//	if (data->rules.num_meals)
//		check_meals(data); // creates a thread
	sem_wait(data.exit_sem);
	kill_n_children(&data, data.rules.num_philos);
	destroy_sems(&data);
	return (0);
}
