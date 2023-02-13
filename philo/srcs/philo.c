/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:58:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/13 03:14:57 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void	test_colors() // remove later
//{
//	(void);
//}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (vars_setup(&vars, ac, av) == -1)
		return (1);
	printf("value -> %d\n", vars.num_philo);
	//test_colors();
	return (0);
}
