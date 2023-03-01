/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:16:29 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/01 20:41:01 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo) // maybe this should do something about the print mutex so nothing gets printed after death
{
	const long	now = philo_gettime();

	pthread_mutex_lock(philo->last_meal_mutex);
	if (now - philo->last_meal > philo->data->rules.time_die)
		return (pthread_mutex_unlock(philo->last_meal_mutex), 1);
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (0);
}

// Prints a status message for every status change of given philosopher
int	print_state(long time, t_philo *philo, const char *state)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->exit_mutex);
	if (philo->data->exit)
	{
		pthread_mutex_unlock(&philo->data->exit_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (-1);
	}
	printf(FLD_TIM FLD_POS "%s", (time - philo->data->start) / 1000, philo->pos,
		state); // make colorful later if delay allows it not sure it takes any longer tho need testing // not sure a variable can concatenate here
	pthread_mutex_unlock(&philo->data->exit_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

// Prints a death message  and sets exit to one
void	print_set_death(long time, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->exit_mutex);
	if (philo->data->exit)
	{
		pthread_mutex_unlock(&philo->data->exit_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	philo->data->exit = 1;
	printf(FLD_TIM FLD_POS FLD_DED, (time - philo->data->start) / 1000,
		philo->pos);// make colorful later if delay allows it not sure it takes any longer tho need testing // not sure a variable can concatenate here
	pthread_mutex_unlock(&philo->data->exit_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// Alternative function to philo_gettime which also sets the last meal time of
// the philo
// Returns the current time in microseconds
long	set_meal_time(t_philo *philo)
{
	const long	now = philo_gettime();
	pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal = now;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (now);
}

// Sets the meal time in the philo struct safely by locking the mutex
//long	set_meal_time(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->last_mutex);
//	philo->last = get_time();
//	pthread_mutex_unlock(&philo->last_mutex);
//	return (philo->last);
//}
//
//void	ft_putnbr_fd(int n, int fd)
//{
//	long	nn;
//	int		neg;
//	int		len;
//	char	tmp[11];
//	char	*ptr;
//
//	nn = (long)n * (1 - (neg = n < 0) * 2);
//	tmp[0] = '-';
//	len = neg;
//	while (nn >= 10)
//	{
//		tmp[len++] = nn % 10 + 48;
//		nn /= 10;
//	}
//	tmp[len++] = nn % 10 + 48;
//	ptr = tmp + len - 1;
//	while ((tmp + neg) < ptr)
//	{
//		nn = tmp[neg];
//		tmp[neg++] = *ptr;
//		*ptr-- = (char)nn;
//	}
//	write(fd, tmp, len);
//}
//size_t	ft_strlen(const char *s) // remove latre
//{
//	char	*ss;
//
//	ss = (char *)s;
//	while (*ss)
//		++ss;
//	return (ss - s);
//}
//void	ft_putstr_fd(char *s, int fd) // remove later
//{
//	if (s == NULL)
//		return ;
//	write(fd, s, ft_strlen(s));
//}
//
//// Mutex-protected print of philosophers actions with colors
//int	print_state(t_philo *philo, t_vars *vars, char *action, long time)
//{
//	pthread_mutex_lock(&vars->ret_mutex);
//	pthread_mutex_lock(&vars->print_mutex);
//	if (vars->ret)
//		return (pthread_mutex_unlock(&vars->ret_mutex), 1);
//	write(1, COL_TIM, 6);
//	ft_putnbr_fd((int)((time - philo->start) / 1000), 1);
//	write(1, COL_RST " ", 5);
//	ft_putnbr_fd(philo->pos, 1);
//	write(1, action, ft_strlen(action));
//	pthread_mutex_unlock(&vars->print_mutex);
//	pthread_mutex_unlock(&vars->ret_mutex);
//	return (0);
//}
////int	print_state(t_philo *philo, t_vars *vars, char *action, long time)
////{
////	pthread_mutex_lock(&vars->print_mutex);
////	pthread_mutex_lock(&vars->ret_mutex);
////	if (vars->ret)
////	{
////		pthread_mutex_unlock(&vars->ret_mutex);
////		pthread_mutex_unlock(&vars->print_mutex);
////		return (1);
////	}
////	printf("\033[7;1m%05ld\033[0m %*.d %s", (time - vars->start) / 1000,
////		vars->print_width, philo->pos, action);
////	pthread_mutex_unlock(&vars->ret_mutex);
////	pthread_mutex_unlock(&vars->print_mutex);
////	return (0);
////}
//
//// Locks ret mutex and outputs the death message
//// Setting ret to 1 will prevent living philosophers to print further status
//// messages
//int	set_death(t_vars *vars, t_philo *philo, long time)
//{
//	pthread_mutex_lock(&vars->ret_mutex);
//	pthread_mutex_lock(&vars->print_mutex);
//	if (vars->ret)
//		return (pthread_mutex_unlock(&vars->ret_mutex), 1);
//	vars->ret = 1;
//	write(1, COL_TIM, 6);
//	ft_putnbr_fd((int)((time - philo->start) / 1000), 1);
//	write(1, COL_RST " ", 5);
//	ft_putnbr_fd(philo->pos, 1);
//	write(1, MSG_DED, ft_strlen(MSG_DED));
//	pthread_mutex_unlock(&vars->print_mutex);
//	pthread_mutex_unlock(&vars->ret_mutex);
//	return (0);
//}
////int	set_death(t_vars *vars, t_philo *philo, long time)
////{
////	pthread_mutex_lock(&vars->print_mutex);
////	pthread_mutex_lock(&vars->ret_mutex);
////	if (vars->ret)
////	{
////		pthread_mutex_unlock(&vars->ret_mutex);
////		pthread_mutex_unlock(&vars->print_mutex);
////		return (1);
////	}
////	vars->ret = 1;
////	printf("\033[7;1m%05ld\033[0m %*.d %s", (time - vars->start) / 1000,
////		vars->print_width, philo->pos, MSG_DED);
////	pthread_mutex_unlock(&vars->ret_mutex);
////	pthread_mutex_unlock(&vars->print_mutex);
////	return (0);
////}
//
//// Picks up forks when available
//// Returns 0 if success, 1 otherwise or when one of the philosophers died
//int	forking(t_philo	*philo, t_vars *vars)
//{
//	pthread_mutex_lock(&philo->fork);
//	if (print_state(philo, vars, MSG_FRK, get_time()) != 0)
//		return (pthread_mutex_unlock(&philo->fork), 1);
//	while (1)
//	{
//		if (philo != philo->next)
//		{
//			pthread_mutex_lock(&philo->next->fork);
//			if (print_state(philo, vars, MSG_FRK, get_time()) != 0)
//				return (pthread_mutex_unlock(&philo->fork),
//					pthread_mutex_unlock(&philo->next->fork), 1);
//			break ;
//		}
//		pthread_mutex_lock(&vars->ret_mutex);
//		if (vars->ret)
//			return (1);
//		pthread_mutex_unlock(&vars->ret_mutex);
//	}
//	return (0);
//}
//
//// Eats for time_to_eat
//int	eating(t_philo *philo, t_vars *vars)
//{
//	if (print_state(philo, vars, MSG_EAT, set_meal_time(philo)) != 0)
//		return (pthread_mutex_unlock(&philo->fork),
//			pthread_mutex_unlock(&philo->next->fork), 1);
//	my_usleep(vars->time_eat);
//	++philo->meals;
//	if (philo->meals == vars->num_meals_min)
//		++vars->had_enough;
//	pthread_mutex_unlock(&philo->fork);
//	pthread_mutex_unlock(&philo->next->fork);
//	return (0);
//}
