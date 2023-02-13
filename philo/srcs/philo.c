/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:58:59 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/13 16:53:20 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mails = 0;
pthread_mutex_t mutex;

void	*start_routine(void	*arg)
{
	int	i;

	const char	*name = arg;
	printf("Thread #%s created!\n", name);
	i = 0;
	while(i < 100000)
	{
		pthread_mutex_lock(&mutex);
		++mails;
		pthread_mutex_unlock(&mutex);
		++i;
	}
	printf("Ending thread routine #%s\n", name);
	return (NULL);
}

//void	*start_routine2(void	*arg)
//{
//	const char	*name = arg;
//	printf("Thread #%s created!\n", name);
//	sleep(1);
//	printf("In thread #%s x is %d\n", name, x);
//	printf("Ending thread\n");
//	return (NULL);
//}

int	main(int ac, char **av)
{
	t_vars	vars;
	pthread_t	t1;
	pthread_t	t2;
	pthread_mutex_init(&mutex, NULL);

	if (vars_setup(&vars, ac, av) == -1)
		return (1);
	pthread_create(&t1, NULL, &start_routine, "1");
	pthread_create(&t2, NULL, &start_routine, "2");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("number of mails -> %d\n", mails);
	//test_colors();
	return (0);
}
