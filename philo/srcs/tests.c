#include "philo.h"

int	test_colors() // remove later
{
	struct		timeval	tv;
	suseconds_t	usecs;

	if (gettimeofday(&tv, NULL) == -1)
		return (perror("test_colors > gettimeofday"), -1);
	usecs = tv.tv_usec / 1000;
	printf("time in seconds -> %ld\n", tv.tv_sec);
	printf("time in microseconds -> %ld\n", tv.tv_usec);
	printf("time in milliseconds-> %03ld\n", usecs);
	printf("%03ld X " COL_DIE "died" COL_RST "\n", usecs);
	printf("%03ld X " COL_EAT "is eating" COL_RST "\n", usecs);
	printf("%03ld X " COL_THK "is thinking" COL_RST "\n", usecs);
	printf("%03ld X " COL_SLP "is sleeping" COL_RST "\n", usecs);
	return (0);
}
