/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:07:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/13 05:17:29 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Unimportant function :]
int	main(int ac, char **av)
{
	t_data		data;

	if (sim_setup(&data, ac, av) == -1)
		return (1);
	if (start_meals_monitor(&data) == -1)
		return (close_sems(&data), unlink_sems(), free(data.pids), 2);
	if (sim_start(&data) == -1)
		return (close_sems(&data), unlink_sems(), free(data.pids), 3);
	sim_wait_end(&data);
	close_sems(&data);
	unlink_sems();
	free(data.pids);
	return (0);
}
