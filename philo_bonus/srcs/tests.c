#include "philo_bonus.h"

void	test_cmd(void)
{
	pid_t	pid;

	printf("Command from utils_bonus.c file\n");
	pid = fork();
	if (pid == -1)
	{
		printf("samere fork a pas marche...\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Hi, from the child process~\n");
		exit(EXIT_SUCCESS);
	}
	printf("My child's pid is %d\n", pid);
}

void	test_inputs(t_vars *vars)
{
	printf("TEST VARS:\n");
	printf("num_philos -> %d\n", vars->num_philos);
	printf("time_die -> %ld\n", vars->time_die);
	printf("time_eat -> %ld\n", vars->time_eat);
	printf("time_sleep -> %ld\n", vars->time_sleep);
	printf("num_meals_min -> %d\n", vars->num_meals_min);
}
