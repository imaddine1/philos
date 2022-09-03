/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:28 by iharile           #+#    #+#             */
/*   Updated: 2022/09/03 20:25:43 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
// color \033[0;33m    \033[0m
// don't forget why unlock and lock not organised in eat function
// check ft_atoi it's behave very well
// handle number that equal or under to the zero
// if last_option is zero than we don't need eat nothing
// check the initialized data
// ./philo 100 300 100 100
// ./philo 2 400 100 100 1 after many execution the dead lock happend

typedef struct data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	int				number_of_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
}		t_data;

typedef struct philosospher
{
	pthread_t	philos;
	long		start_time;
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
int		check_err(int ac, char **av);
void	initialize_data(t_philos *ph, t_data *frk, char **av);
long	get_time(void);
void	ft_usleep(long duration);
void	*routine(void	*arg);
void	sleep_n_think(t_philos *ph);
void	eat(t_philos *ph);
void	sleep_n_think(t_philos *ph);
void	ft_printf(t_philos *ph, char *str);
int		death_n_meals(t_philos *ph, int total);
#endif