/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:07:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/08 21:04:57 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Unimportant function :]
int	main(int ac, char **av)
{
	t_data		data;
	//pthread_t	meals_thread;

	if (sim_setup(&data, ac, av) == -1)
		return (1);
	if (sim_start(&data) == -1)
		return (destroy_sems(&data), 2);
	//if (data->rules.num_meals)
	//	if (pthread_create(&meals_thread, NULL, &meals_monitoring, &data) != 0)
	//		return (3);
	sim_wait_end(&data);
	return (0);
}
