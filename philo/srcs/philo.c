/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:58:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/13 22:38:54 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_vars	vars;

	if (vars_setup(&vars, ac, av) == -1)
		return (printf(PHILO_ERR PE_SETUP), 1);
	//test_colors();
	if (start_philos(&vars) == -1)
		return (printf(PHILO_ERR PE_START_FUNC), 1);
	if (join_philos(&vars) == -1)
		return (printf(PHILO_ERR PE_JOIN_FUNC), 1);
	philo_terminate(&vars);
	return (0);
}
