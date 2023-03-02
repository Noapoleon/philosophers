/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:50:45 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/02 03:32:54 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Parses ints from av to philo values and prints errors if some are present
// Returns 0 for no errors and -1 otherwise
//int	vars_setup(t_vars *vars, int ac, char **av)
//{
//	if (get_inputs(vars, ac, av) == -1)
//		return (-1);
//	vars->sync = sem_open("/sem_sync", O_CREAT, 0644, 0);
//	if (vars->sync == SEM_FAILED)
//		return (printf(PHILO_ERR PE_SEMSYNC_OPEN), -1);
//	vars->forks = sem_open("/sem_forks", O_CREAT, 0644, vars->num_philos);
//	if (vars->forks == SEM_FAILED)
//		return (printf(PHILO_ERR PE_SEMFORKS_OPEN), -1);
//	//vars->start = 0;
//	//vars->ret = 0;
//	//vars->had_enough = 0;
//	return (0);
//}

// Safely initializes every variable and mutex required for the simulation
// Returns 0 on success, -1 otherwise
//int	sim_setup(t_data *data, int ac, char **av)
int	sim_setup(t_rules *rules, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf(USAGE1 USAGE2 USAGE3, av[0]), -1);
	//if (get_rules(&data->rules, ac, av) == -1)
	if (get_rules(rules, ac, av) == -1)
		return (-1);
	// open sems
	//if (make_mutexes(data) == -1)
	//	return (-1);
	//set_philos(data);
	//data->ate_meals = 0;
	//data->exit = 0;
	//data->start = 0;
	//data->synced = 0;
	return (0);
}

// Parses the program arguments and stores them in rules struct
// Returns 0 on success, -1 otherwise
int	get_rules(t_rules *rules, int ac, char **av)
{
	int	errors;

	errors = 0;
	if (atoi_philo(av[1], 1, MAX_PHILOS, &rules->num_philos) && ++errors)
		printf(PHILO_ERR PE_N_PHILO PE_FORVAL);
	if (atoi_philo(av[2], MIN_TIME, INT_MAX, &rules->time_die) && ++errors)
		printf(PHILO_ERR PE_T_DIE PE_FORVAL);
	if (atoi_philo(av[3], MIN_TIME, INT_MAX, &rules->time_eat) && ++errors)
		printf(PHILO_ERR PE_T_EAT PE_FORVAL);
	if (atoi_philo(av[4], MIN_TIME, INT_MAX, &rules->time_sleep) && ++errors)
		printf(PHILO_ERR PE_T_SLEEP PE_FORVAL);
	rules->num_meals = 0;
	if (ac == 6 && atoi_philo(av[5], 1, INT_MAX, &rules->num_meals) && ++errors)
		printf(PHILO_ERR PE_N_MEALS PE_FORVAL);
	rules->time_die *= 1000;
	rules->time_eat *= 1000;
	rules->time_sleep *= 1000;
	if (errors)
		return (-1);
	return (0);
}

// Initializes mutexes from data
// Returns 0 on success, -1 otherwise
//int	make_mutexes(t_data *data)
//{
//	int	i;
//
//	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
//		return (-1);
//	if (pthread_mutex_init(&data->ate_mutex, NULL) != 0)
//		return (pthread_mutex_destroy(&data->print_mutex), -1);
//	if (pthread_mutex_init(&data->exit_mutex, NULL) != 0)
//		return (pthread_mutex_destroy(&data->print_mutex),
//			pthread_mutex_destroy(&data->ate_mutex), -1);
//	if (pthread_mutex_init(&data->sync_mutex, NULL) != 0)
//		return (pthread_mutex_destroy(&data->exit_mutex),
//			pthread_mutex_destroy(&data->print_mutex),
//			pthread_mutex_destroy(&data->ate_mutex), -1);
//	i = 0;
//	while (i < data->rules.num_philos)
//	{
//		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
//			return (destroy_n_mutexes(data, i), -1);
//		if (pthread_mutex_init(&data->last_meal_mutexes[i], NULL) != 0)
//			return (pthread_mutex_destroy(&data->forks[i]),
//				destroy_n_mutexes(data, i), -1);
//		++i;
//	}
//	return (0);
//}

// Sets each philosopher's attributes
//void	set_philos(t_data *data)
//{
//	int		i;
//	t_philo	*curr;
//
//	i = 0;
//	while (i < data->rules.num_philos)
//	{
//		curr = &data->philos[i];
//		curr->pos = i + 1;
//		curr->data = data;
//		curr->left_fork = &data->forks[i];
//		if (i != data->rules.num_philos - 1)
//			curr->right_fork = &data->forks[i + 1];
//		else
//			curr->right_fork = &data->forks[0];
//		curr->last_meal_mutex = &data->last_meal_mutexes[i];
//		curr->last_meal = 0;
//		curr->meals = 0;
//		++i;
//	}
//}

// Parses string into integer and stores it in dst
// Formatting is very strict, only numbers are allowed, no whitespace and no
// negatives values and returns an error when parsed value is out of [min;max]
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
