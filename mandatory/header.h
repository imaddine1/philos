/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharile <iharile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:29:28 by iharile           #+#    #+#             */
/*   Updated: 2022/08/26 15:29:47 by iharile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

typedef	struct forks
{
	pthread_mutex_t	*forks;
}	t_fork;

typedef struct philosospher
{
	pthread_t		philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			im_eating;
	long			meals_count;
	t_fork			*forks;
}	t_philos;
