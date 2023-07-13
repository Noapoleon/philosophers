/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:58:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/07/13 15:08:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function :]
int	main(int ac, char **av)
{
	t_data	data;

	if (sim_setup(&data, ac, av) == -1)
		return (1);
	if (sim_start(&data) == -1)
		return (destroy_n_mutexes(&data, data.rules.num_philos), 2);
	monitoring(&data);
	sim_stop(&data);
	return (0);
}
