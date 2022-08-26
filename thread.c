#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

//if philo didn't start eating from last meal or begging the semulation they die

pthread_mutex_t	*forks;
pthread_mutex_t writing,meal;
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
	int		im_eating;
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
		usleep(250); 
}


void	print(char *msg, t_philos *p)
{
	pthread_mutex_lock(&writing);
	long time = get_time() - p->current_time;
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

	pthread_mutex_lock(&writing);
	p->meals_count += 1;
	p->time_last_meal = get_time();
	p->im_eating = 1;
	pthread_mutex_unlock(&writing);
	ft_usleep(p->time_eat);
	pthread_mutex_lock(&writing);
	p->im_eating = 0;
	pthread_mutex_unlock(&writing);

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
	//printf ("this my thread %d and time %ld\n", p->name, get_time() - p->time_last_meal);
	while (1)
	{
		eating(p);
		sleeping_n_thinking(p);
	}
	return (NULL);
}

int	main (int ac, char **av)
{
	t_philos		*ph;
	t_data			*data = malloc(sizeof(t_data));
	int				must_eat;
	int				nb_of_meals = 0;
	int				arr[atoi(av[1])];


	if (ac < 5 || ac > 6)
	{
		printf ("enter all the parameters pls\n");
		exit(1);
	}
	int i = -1;
	if (av[5])
	{
		must_eat = atoi(av[5]);
		while (++i < atoi(av[1]))
			arr[i] = -1;
	}
	else
		must_eat = -1;
	thread = malloc (sizeof(pthread_t) * atoi(av[1]));
	i = 0;
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
	//	ph[i].current_time = get_time();
		ph[i].data = data;
		ph[i].meals_count = 0;
		ph[i].im_eating = 0;
		i++;
	};
	i = 0;
	pthread_mutex_init(&writing, NULL);
	pthread_mutex_init(&meal, NULL);
	while (i < total)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = -1;
	data->start_time = get_time();
	while (++i < total) 
	{
		ph[i].current_time = data->start_time;
		ph[i].time_last_meal = get_time();
		pthread_create(&thread[i], NULL, &routine, &ph[i]);
		usleep(50);
	}

	while (1)
	{
		int 	i = -1;
		int 	x = 0;
		long	time;
		long	total = ph[0].total;
		while(++i < total)
		{
			//printf ("meals of %d is %d\n", ph[i].name, ph[i].meals_count);
			pthread_mutex_lock(&writing);
			if (ph[i].meals_count == must_eat)
			{
				if (arr[i] == -1)
				{
					arr[i] = must_eat;
					nb_of_meals += 1;
				}
				if (nb_of_meals == atoi(av[1]))
				{
					// pthread_mutex_lock(&writing);
					printf ("end of simulation\n");
					/*int d = -1;
		.			while (++d < total)
					{
						pthread_detach(thread[d]);
						pthread_mutex_destroy(&forks[d]);
					}*/
					return (0);
				}
			}
			pthread_mutex_unlock(&writing);
			pthread_mutex_lock(&writing);
			if (get_time() - ph[i].time_last_meal >= ph[i].time_die && !ph[i].im_eating)
			{
				// pthread_mutex_lock(&writing);
				int d = -1;
				while (++d < total)
				{
					pthread_detach(thread[d]);
					pthread_mutex_destroy(&forks[d]);
				}
				time = get_time() - ph[i].time_last_meal;			
				printf ("\033[0;31m%ld ms %d died\033[0m\n", time, ph[i].name);
				//printf ("nb_of_meals is %d and arr[0] == %d\n", nb_of_meals, arr[0]);
				x= 1;
				break ;
			}
			pthread_mutex_unlock(&writing);
		}
		if (x == 1)
			break;
		usleep(10);
	}
	i = 0;
	while (i < total)
	{
		pthread_join(thread[i], NULL);
		i++;
	}

	//printf ("end of simulation\n");

	return (0);
}

