/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:58:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/17 19:07:33 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Unimportant function
int	main(int ac, char **av)
{
	t_philo		*philos;
	t_monitor	*monitors;
	t_vars		vars;

	philos = NULL;
	monitors = NULL;
	if (ac != 5 && ac != 6)
		return (printf(USAGE1 USAGE2 USAGE3, av[0]), 1);
	if (vars_setup(&vars, ac, av) == -1)
		return (2);
	if (sim_setup(&philos, &monitors, &vars) == -1)
		return (pthread_mutex_destroy(&vars.print_mutex),
			pthread_mutex_destroy(&vars.ret_mutex), -1);
	if (start_sim(philos, monitors, &vars) == -1)
		return (terminate_sim(philos, monitors, &vars), 5);
	if (join_n_threads(philos, monitors, vars.num_philos, vars.num_philos)
		!= 0)
		return (terminate_sim(philos, monitors, &vars), 6);
	terminate_sim(philos, monitors, &vars);
	return (0);
}
