/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:28 by iharile           #+#    #+#             */
/*   Updated: 2022/09/04 11:45:00 by iharile          ###   ########.fr       */
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