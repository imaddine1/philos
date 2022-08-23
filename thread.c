#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

//if philo didn't start eating from last meal or begging the semulation they die

pthread_mutex_t	*forks;
pthread_mutex_t writing;
pthread_t		*thread;

typedef struct data{
	long	start_time;
}	t_data;

typedef struct philosopher
{
	int		id;
	int		l_f;
	int		r_f;
	int 	name;
	int		meals_count;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	long	current_time;
	long	time_last_meal;
	long	die;
	int		total;
	t_data	*data;
}	t_philos;

long 	get_time(void)
{
	struct timeval	calcultime;
	long	long		time;

	gettimeofday(&calcultime, NULL);
	time = (calcultime.tv_sec * 1000) + (calcultime.tv_usec / 1000);
	return (time);
}
void	ft_usleep(long dur)
{
	long	start;

	start = get_time();
	while (get_time() - start < dur)
		usleep(50);
}


void	print(char *msg, t_philos *p)
{
	pthread_mutex_lock(&writing);
	long time = get_time() - p->data->start_time;
	printf("%ld ms %d %s\n", time, p->name, msg);
	pthread_mutex_unlock(&writing);
}



void	eating(t_philos *p)	
{
	long	time;

	pthread_mutex_lock(&forks[p->l_f]);
	print ("has taken a fork", p);
	pthread_mutex_lock(&forks[p->r_f]);
	print ("has taken a fork", p);
	print("\033[32mis eating\033[0m", p);
	p->time_last_meal = get_time();
	ft_usleep(p->time_eat);
	pthread_mutex_unlock(&forks[p->l_f]);
	pthread_mutex_unlock(&forks[p->r_f]);
	/*printf ("this is time %ld and his name is %d\n", p->time_last_meal, p->name);
	if (p->time_last_meal >= p->time_die)
	{
		pthread_mutex_lock(&writing);
		return(1);
	}
	return (0);
	pthread_mutex_unlock(&writing);*/
}

// sleep and think display
void sleeping_n_thinking(t_philos *p)
{
	print("is sleeping", p);
	ft_usleep(p->time_sleep);
	print("is thinking", p);
}

// check philosopher if diey


// this is my routine ;
void	*routine(void *arg)
{
	t_philos	*p = (t_philos *)arg;

	if (p->name % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		eating(p);
		//printf ("this philos %d have a die %ld\n", p->name, p->die);
		sleeping_n_thinking(p);
	}
	return (NULL);
}

int	main (int ac, char **av)
{
	t_philos		*ph;
	t_data			*data = malloc(sizeof(t_data));


	if (ac != 5)
	{
		printf ("enter all the parameters pls\n");
		exit(1);
	}
	thread = malloc (sizeof(pthread_t) * atoi(av[1]));
	int i = 0;
	int total = atoi(av[1]);
	ph = malloc (sizeof(t_philos) * atoi(av[1]));
	forks = malloc (sizeof(pthread_mutex_t) * atoi(av[1]));
	while (i < total)
	{
		ph[i].id = i;
		ph[i].total = atoi(av[1]);
		ph[i].l_f = i;
		ph[i].r_f = (i + 1) % total;
		ph[i].name = i + 1;
		ph[i].time_die = atoi(av[2]);
		ph[i].time_eat = atoi(av[3]);
		ph[i].time_sleep = atoi(av[4]);
		ph[i].current_time = 0;
		ph[i].data = data;
		ph[i].time_last_meal = 10;
		ph[i].die = 0;
		i++;
	};
	i = 0;
	pthread_mutex_init(&writing, NULL);
	while (i < total)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = -1;
	data->start_time = get_time();
	while (++i < total) 
	{
		ph[i].current_time = (ph[i].data)->start_time;
		ph[i].time_last_meal = get_time();
		//printf ("%d my last meal\n", ph[i].name);
		pthread_create(&thread[i], NULL, &routine, &ph[i]);
		usleep(1);
	}
	while (1)
	{
		i = -1;
		int x = 0;
		long	time;
		long	total = ph[0].total;
		while(++i < total)
		{
			//usleep((ph[i].time_eat / 10) * 1000);
			//printf ("im  i == %d\n", i);
			if (get_time() - ph[i].time_last_meal >= ph[i].time_die)
			{
				pthread_mutex_lock(&writing);
				int d = -1;
				while (++d < total)
				{
					pthread_detach(thread[d]);
					pthread_mutex_destroy(&forks[d]);
					ph[i].die = 1;
				}
				time = get_time() - ph[i].time_last_meal;			
				printf ("\033[0;31m%ld ms %d died\033[0m\n", time, ph[i].name);
				x= 1;
				break ;
			}
		}
		if (x == 1)
			break;
	}

	//printf ("end of simulation\n");
	i = 0;
	while (i < total)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (0);
}

