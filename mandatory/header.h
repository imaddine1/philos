/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:28 by iharile           #+#    #+#             */
/*   Updated: 2022/08/27 18:43:29 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

// don't forget why unlock and lock not organised in eat function
// check ft_atoi it's behave very well

typedef	struct data
{
	pthread_mutex_t	*forks;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	long		current_time;
	int			must_eat;
}	t_data;

typedef struct philosospher
{
	pthread_t	philos;
	int			name;
	int			im_eating;
	int			meals_count;
	int			l_f;
	int			r_f;
	long		last_meal;
	t_data		*data;
}	t_philos;

int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		check_err(char **av);
void	initialize_data(t_philos *ph, t_data *frk, char **av);
long	get_time();
void	ft_usleep(long duration);
void	*routine(void	*arg);
void	sleep_n_think(t_philos *ph);
void	eat(t_philos *ph);
void	sleep_n_think(t_philos *ph);
void	ft_printf(t_philos *ph, char *str);
void	death_n_meals(t_philos *ph, int total);
