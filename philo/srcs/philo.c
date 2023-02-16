/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:58:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/16 04:11:12 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Unimportant function
int	main(int ac, char **av)
{
	t_philo		*philos;
	t_vars	vars;

	if (ac != 5 && ac != 6)
		return (printf(USAGE1 USAGE2 USAGE3, av[0]), 1);
	if (philo_setup(&philos, &vars, ac, av) == -1)
		return (2);
	if (start_philos(philos, &vars) == -1)
		return (philo_terminate(philos, &vars), 3);
	if (join_philos(philos, &vars) == -1)
		return (philo_terminate(philos, &vars), 4);
	philo_terminate(philos, &vars);
	return (0);
}
