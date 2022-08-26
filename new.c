#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>


unsigned long long get_time()
{
	struct timeval	time;
	unsigned long long	start_time;


	if (gettimeofday(&time, NULL) != 0)
	{
		printf ("error happend \n");
		exit (1);
	}
	start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (start_time);
}
int	main(int ac, char **av)
{
	unsigned long long	time_o_now;
	long	arg;
	int		x;

	arg = atoi(av[1]);
	x = 0;
	time_o_now = get_time();
	printf ("the wasted time is %llu number the usleep use %d\n", get_time() - time_o_now, x);
	while (get_time() - time_o_now < arg)
	{
		x += 1;
		usleep(250);
		printf ("updated time %llu\n", (get_time() - time_o_now));
	}
	printf ("the wasted time is %llu number the usleep use %d\n", get_time() - time_o_now, x);
}