/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:07:38 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/21 09:05:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_vars	vars;
	int		i;

	if (ac != 5 && ac != 6)
		return (printf(USAGE1 USAGE2 USAGE3, av[0]), 1);
	if (vars_setup(&vars, ac, av) == -1)
		return (2);
	// probably some more setup to do here
	// also dont forget a print sem
	i = 0;
	while (i < vars.num_philos)
	{
		philosophing(&vars, ++i);
		sleep(1); // should all display their messages at the same time despite this because of the sync semaphore
	}
	while (i--)
		sem_post(vars.sync);
	while (i++ < vars.num_philos)
		wait(NULL); // FUNCTION NOT ALLOWED CHANGE LATER FOR WAITPID, probably will have to make a pid_t array of size vars->num_philos
	phibo_terminate(&vars, EXIT_SUCCESS);
	return (0);
}
