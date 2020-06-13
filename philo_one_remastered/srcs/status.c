/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 03:18:32 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/13 21:44:31 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** function: {eating}
**
** parameters:
** (t_philosopher *){phi} - philosopher's structure
**
** return (void)
**
** description:
** action of eat
*/

#include <stdio.h>
void		eating(t_philosopher *phi)
{	
	gettimeofday(phi->time_last_meal, NULL);
	logs(phi->parameters->time_start, phi->time_last_meal,
phi->nb, " is eating\n");
	usleep(phi->parameters->time_to_eat * 1000);
	phi->nb_eat++;
}

/*
** function: {check_eating}
**
** parameters:
** (t_philosopher *){phi} - philosopher's structure
**
** return (int): no-null number if the philosopher is dead
**
** description:
** action of eat of a philosopher, it look at the last meal, and replace it if
** the philosopher just ate in time
*/

int			check_eating(t_philosopher *phi)
{
	struct timeval	time_action;

	gettimeofday(&time_action, NULL);
	pthread_mutex_lock(phi->lock_last_meal);
	if ((int)phi->nb_eat ==
phi->parameters->number_of_time_each_philosophers_must_eat ||
!phi->time_last_meal || ((time_action.tv_sec -
phi->time_last_meal->tv_sec) * 1000 + (time_action.tv_usec -
phi->time_last_meal->tv_usec) * 0.001 > phi->parameters->time_to_die))
	{
		if (phi->time_last_meal)
		{
			free(phi->time_last_meal);
			logs(phi->parameters->time_start,
&time_action, phi->nb, " died\n");
		}
		phi->time_last_meal = NULL;
		pthread_mutex_unlock(phi->lock_last_meal);
		return (1);
	}
	eating(phi);
	pthread_mutex_unlock(phi->lock_last_meal);
	return (0);
}

/*
** function: {alive}
**
** parameters:
** (t_philosopher *){phi} - philosopher's structure
**
** return (void) - just exiting if the philosopher is dead
**
** description:
** thinking - eating - spleeping on a loop with timer, it call {eating} when
** it's the action's turn, if {eating} returns a no-null value, it mean that the
** philosopher died so it exit the function resulting of a kill of the pthread.
*/

void		alive(t_philosopher *phi)
{
	struct timeval	time_action;

	while (1)
	{
		pthread_mutex_lock(phi->left_fork);
		gettimeofday(&time_action, NULL);
		logs(phi->parameters->time_start, &time_action, phi->nb,
" has taken a left fork /!\\ delete side later\n");
		pthread_mutex_lock(phi->right_fork);
		gettimeofday(&time_action, NULL);
		logs(phi->parameters->time_start, &time_action, phi->nb,
" has taken a right fork /!\\ delete side later\n");
		if (check_eating(phi))
		{	
			pthread_mutex_unlock(phi->right_fork);
			pthread_mutex_unlock(phi->left_fork);
			return ;
		}
		pthread_mutex_unlock(phi->right_fork);
		pthread_mutex_unlock(phi->left_fork);
		gettimeofday(&time_action, NULL);
		logs(phi->parameters->time_start,
&time_action, phi->nb, " is sleeping\n");
		usleep(phi->parameters->time_to_sleep * 1000);
		gettimeofday(&time_action, NULL);
		logs(phi->parameters->time_start,
&time_action, phi->nb, " is thinking\n");
	}
}

/*
** function: {init_life}
**
** parameters:
** (void *){args} - contain philosopher's structure
**
** return (void)
**
** description:
** init {start} to pass it through {alive} function to avoid multiple call at
** {time_start} and avoid mutex lock/unlock, init also time_last_meal with the
** starting time.
*/


void		*init_life(void *args)
{
	t_philosopher	*phi;

	phi = (t_philosopher *)args;

	alive(phi);
	return (NULL);
}