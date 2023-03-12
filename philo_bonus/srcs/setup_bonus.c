/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:50:45 by nlegrand          #+#    #+#             */
/*   Updated: 2023/03/12 08:31:20 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Safely initializes every variable and mutex required for the simulation
// Returns 0 on success, -1 otherwise
//int	sim_setup(t_data *data, int ac, char **av)
int	sim_setup(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf(USAGE1 USAGE2 USAGE3, av[0]), -1);
	if (get_rules(&data->rules, ac, av) == -1)
		return (-1);
	if (make_sems(data) == -1)
		return (printf(PHILO_ERR PE_SEMS), -1);
	//data->ate_meals = 0;
	data->philo.meals = 0;
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

// Opens the needed semaphores and checks for errors
// On success returns 0, otherwise -1
int	make_sems(t_data *data) // closing stuff that doesn't exist, check if that's fine
{
	sem_unlink("/forks_sem");
	sem_unlink("/sync_sem");
	sem_unlink("/print_sem");
	sem_unlink("/forking_sem");
	//sem_unlink("/ate_sem");
	//sem_unlink("/exit_sem");
	data->forks_sem = sem_open("/forks_sem", O_CREAT, 0644,
		data->rules.num_philos);
	if (data->forks_sem == SEM_FAILED)
		return (-1);
	data->sync_sem = sem_open("/sync_sem", O_CREAT, 0644, 0);
	if (data->sync_sem == SEM_FAILED)
		return (destroy_sems(data), -1);
	data->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (destroy_sems(data), -1);
	data->forking_sem = sem_open("/forking_sem", O_CREAT, 0644, 1);
	if (data->forking_sem == SEM_FAILED)
		return (destroy_sems(data), -1);
	//data->ate_sem = sem_open("/ate_sem", O_CREAT, 0644, 1);
	//if (data->ate_sem == SEM_FAILED)
	//	return (destroy_sems(data), -1);
	//data->exit_sem = sem_open("/exit_sem", O_CREAT, 0644, 0);
	//if (data->exit_sem == SEM_FAILED)
	//	return (destroy_sems(data), -1);
	return (0);
}
