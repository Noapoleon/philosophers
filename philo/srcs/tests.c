/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:59:21 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/16 23:51:30 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int	test_colors() // remove later
//{
//	struct		timeval	tv;
//	suseconds_t	usecs;
//
//	if (gettimeofday(&tv, NULL) == -1)
//		return (perror("test_colors > gettimeofday"), -1);
//	usecs = tv.tv_usec / 1000;
//	printf("time in seconds -> %ld\n", tv.tv_sec);
//	printf("time in microseconds -> %ld\n", tv.tv_usec);
//	printf("time in milliseconds-> %03ld\n", usecs);
//	printf(COL_REV "%03ld" COL_RST "X " COL_DIE "died" COL_RST "\n", usecs);
//	printf(COL_REV "%03ld" COL_RST "X " COL_EAT "is eating" COL_RST "\n", usecs);
//	printf(COL_REV "%03ld" COL_RST "X " COL_THK "is thinking" COL_RST "\n", usecs);
//	printf(COL_REV "%03ld" COL_RST "X " COL_SLP "is sleeping" COL_RST "\n", usecs);
//	return (0);
//}

int	show_philos(t_philo *philos, t_vars *vars)
{
	int	i;
	t_philo	*curr;

	curr = &philos[0];
	i = 0;
	while (i < vars->num_philos)
	{
		printf("Philo #%d:\n", curr->pos);
		//printf("prev -> %p\n", curr->prev);
		printf("next -> %p\n\n", curr->next);
		curr = curr->next;
		++i;
	}
	return (0);
}

int	test_loop(t_philo *philos, t_vars *vars)
{
	(void)vars;
	t_philo	*curr;

	printf("here!!\n");
	curr = &philos[0];
	while (1)
	{
		printf("Philo #%d:\n", curr->pos);
		printf("next num -> %d\n", curr->next->pos);
		curr = curr->next;
	}
	return (0);
}

void	sleep_test()
{
	struct timeval	tv1;
	struct timeval	tv2;
	long			diff;

	gettimeofday(&tv1, NULL);
	usleep(200000);
	gettimeofday(&tv2, NULL);
	diff = (tv2.tv_sec * 1000 + tv2.tv_usec / 1000) - (tv1.tv_sec * 1000 + tv1.tv_usec / 1000);
	printf("slept for -> %ldms\n", diff);
}

void	test_monitors(t_monitor *monitors, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philos)
	{
		printf("Monitor %d:\n", i);
		printf("philo -> %d\n", monitors[i].philo->pos);
		++i;
	}
}
