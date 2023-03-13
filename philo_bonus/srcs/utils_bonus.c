/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:08:50 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/13 05:14:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Parses string into integer and stores it in dst
// Formatting is very strict, only numbers are allowed, no whitespace and no
// negatives values and returns an error when parsed value is out of [min;max]
// Also not safe becaues doesn't check that given string is not NULL
// Returns 0 on success, -1 otherwise
int	atoi_philo(char *str, long min, long max, long *dst)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		if (n < INT_MIN || n > INT_MAX)
			return (-1);
		++i;
	}
	if (n < min || n > max || str[i] != '\0')
		return (-1);
	return ((*dst = n), 0);
}

// Closes sems :o
void	close_sems(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->sync_sem);
	sem_close(data->print_sem);
	sem_close(data->forking_sem);
	sem_close(data->ate_sem);
}

// Closes and unlinks all semaphores
void	unlink_sems(void)
{
	static char	sem_name[13] = LAST_SEM_DEFAULT;
	int			i;
	int			j;

	sem_unlink("/forks_sem");
	sem_unlink("/sync_sem");
	sem_unlink("/print_sem");
	sem_unlink("/forking_sem");
	sem_unlink("/ate_sem");
	i = 0;
	while (i++ < MAX_PHILOS)
	{
		j = i;
		sem_name[11] = j % 10 + '0';
		j /= 10;
		sem_name[10] = j % 10 + '0';
		j /= 10;
		sem_name[9] = j % 10 + '0';
		sem_unlink(sem_name);
	}
}

// Returns current time in microseconds
long	philo_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

// Kills all philosophers children processes
void	kill_n_children(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (data->pids[i] != 0 && data->pids[i] != -1)
			kill(data->pids[i], SIGKILL);
		++i;
	}
}
