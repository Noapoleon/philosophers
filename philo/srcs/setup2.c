/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:52:49 by nlegrand          #+#    #+#             */
/*   Updated: 2023/02/19 03:45:30 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Allocates the philos and monitors arrays
// Returns 0 on success and -1 otherwise
int	sim_setup(t_philo **philos, t_monitor **monitors, t_vars *vars)
{
	if (make_philos(philos, vars) == -1)
		return (-1);
	if (make_monitors(monitors, *philos, vars) == -1)
		return (destroy_n_mutexes(*philos, vars->num_philos),
			free(*philos), -1);
	return (0);
}

// Allocates and philos array list and inits mutexes
// Returns 0 on success and -1 otherwise
int	make_philos(t_philo **philos, t_vars *vars)
{
	t_philo	*curr;
	int		i;

	*philos = malloc(sizeof(t_philo) * vars->num_philos);
	if (*philos == NULL)
		return (printf(PHILO_ERR PE_ALLOC_PHILOS), -1);
	i = 0;
	while (i < vars->num_philos)
	{
		curr = &(*philos)[i];
		curr->pos = i + 1;
		curr->last = 0;
		curr->meals = 0;
		curr->vars = vars;
		curr->next = *philos + (i != vars->num_philos - 1) * (i + 1);
		if (make_philo_mutexes(curr, i) == -1)
			return (destroy_n_mutexes(*philos, i), free(*philos), -1);
		++i;
	}
	return (0);
}

int	make_philo_mutexes(t_philo *philo, int i)
{
	if (pthread_mutex_init(&philo->fork, NULL) != 0)
		return (printf(PHILO_ERR PE_FORK_MUTEX, i + 1), -1);
	if (pthread_mutex_init(&philo->last_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&philo->fork),
			printf(PHILO_ERR PE_LAST_MUTEX, i + 1), -1);
	return (0);
}

// Allocates monitors
// Returns 0 on success and -1 otherwise
int	make_monitors(t_monitor **monitors, t_philo *philos, t_vars *vars)
{
	int	i;

	*monitors = malloc(sizeof(t_monitor) * vars->num_philos);
	if (*monitors == NULL)
		return (-1);
	i = 0;
	while (i < vars->num_philos)
	{
		(*monitors)[i].pos = i + 1;
		(*monitors)[i].philo = &philos[i];
		(*monitors)[i].vars = vars;
		++i;
	}
	return (0);
}
