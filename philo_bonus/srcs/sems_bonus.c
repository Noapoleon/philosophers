/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sems_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:24:54 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/21 09:00:13 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosophing(t_vars *vars, int pos)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf(PHILO_ERR PE_FORK, pos);
		phibo_terminate(vars, EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		sem_wait(vars->sync);
		printf("Philo %d passed the sem_wait for sync\n", pos);
		phibo_terminate(vars, EXIT_SUCCESS);
	}
}
