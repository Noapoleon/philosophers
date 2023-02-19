/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:08:50 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/19 19:14:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	util_cmd(void)
{
	pid_t	pid;

	printf("Command from utils_bonus.c file\n");
	pid = fork();
	if (pid == -1)
	{
		printf("samere fork a pas marche...\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Hi, from the child process~\n");
		exit(EXIT_SUCCESS);
	}
	printf("My child's pid is %d\n", pid);
}
