/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:34:57 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 21:54:32 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Locks fork mutexes
// Returns 0 on success, -1 if get_exit returned 1
int	forking(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_state(philo_gettime(), philo, FLD_FRK) == -1) // i think doing this like this will allow messages to be printed after the death of a philo
		return (pthread_mutex_unlock(philo->left_fork), -1);
	if (philo->left_fork == philo->right_fork)
		return (pthread_mutex_unlock(philo->left_fork), -1);
	pthread_mutex_lock(philo->right_fork);
	if (print_state(philo_gettime(), philo, FLD_FRK) == -1) // i think doing this like this will allow messages to be printed after the death of a philo
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), -1);
	return (0);
}

// Sends philosopher into eating for amount of time specified in rules struct
// Returns 0 on success, -1 if get_exit returned 1
int	eating(t_philo *philo, t_data *data)
{
	if (print_state(set_meal_time(philo), philo, FLD_EAT) == -1)
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), -1);
	philo_usleep(data->rules.time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (++philo->meals == data->rules.num_meals)
	{
		pthread_mutex_lock(&data->ate_mutex);
		++data->ate_meals;
		pthread_mutex_unlock(&data->ate_mutex);
	}
	return (0);
}

// Sends philosopher into sleep for amount of time specified in rules struct
// Returns 0 on success, -1 if get_exit returned 1
int	sleeping(t_philo *philo, t_data *data)
{
	if (print_state(philo_gettime(), philo, FLD_SLP) == -1) // i think doing this like this will allow messages to be printed after the death of a philo
		return (-1);
	philo_usleep(data->rules.time_sleep);
	if (get_exit(data))
		return (-1);
	return (0);
}

//int	thinking(t_philo *philo)
//{
//	if (print_state(philo_gettime(), philo, FLD_THK) == -1) // i think doing this like this will allow messages to be printed after the death of a philo
//		return (-1);
//	return (0);
//}
