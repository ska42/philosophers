/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 03:18:32 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/19 03:40:31 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

void		eating(t_philosopher *phi)
{
	gettimeofday(phi->time_last_meal, NULL);
	logs(phi->parameters->time_start, phi->time_last_meal,
phi->nb, " is eating\n");
	phi->nb_eat++;
	usleep(phi->parameters->time_to_eat * 1000);
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
	if (sem_wait(phi->sem_last_meal)) // TODO: handling error ?
		return (ERROR_SEM);
	if (phi->nb_eat ==
phi->parameters->number_of_time_each_philosophers_must_eat ||
!phi->time_last_meal || ((size_t)((time_action.tv_sec -
phi->time_last_meal->tv_sec) * 1000 + (time_action.tv_usec -
phi->time_last_meal->tv_usec) * 0.001) > phi->parameters->time_to_die))
	{
		if (phi->time_last_meal && phi->nb_eat !=
phi->parameters->number_of_time_each_philosophers_must_eat)
		{
			free(phi->time_last_meal);
			logs(phi->parameters->time_start,
&time_action, phi->nb, " died\n");
		}
		phi->time_last_meal = NULL;
		if (sem_post(phi->sem_last_meal)) //TODO: handling error ?
			return (ERROR_SEM);
		return (1);
	}
	eating(phi);
	if (sem_post(phi->sem_last_meal)) //TODO: handling error ?
		return (ERROR_SEM);
	return (0);
}

/*
** function: {taking_forks}
**
** parameters:
** (t_philosopher *){phi} - philosopher's structure
**
** return (int) - return no-null if a philosopher has died during process
**
** description:
** each philosophers must take 2 forks before eating. To avoid every
** philosophers to take the left or right fork at the same time and keep
** everyone safe of a blocked situation, just giving the first and second time,
** the right or left fork depending if the philosopher is odd or even.
*/

#include <stdio.h>

int			taking_forks(t_philosopher *phi)
{
	int				i;
	struct timeval	time_action;

	i = 0;
	printf("%p\n", phi->parameters->forks);
	return (1);
	while (i++ < 2)
	{
			if (sem_wait(phi->parameters->forks)) //TODO: handling error ?
				return (ERROR_SEM);
			gettimeofday(&time_action, NULL);
			logs(phi->parameters->time_start, &time_action, phi->nb,
" has taken a fork\n");
	}
	if (!phi->time_last_meal)
		return (1);
	return (0);
}

/*
** function: {alive}
**
** parameters:
** (void *){args} - contain philosopher's structure
**
** return (void *) - just exiting if the philosopher is dead
**
** description:
** thinking - eating - spleeping on a loop with timer, it call {eating} when
** it's the action's turn, if {eating} returns a no-null value, it mean that the
** philosopher died so it exit the function resulting of a kill of the pthread.
*/

void		*alive(void *args)
{
	t_philosopher	*phi;
	struct timeval	time_action;

	phi = (t_philosopher *)args;
	while (1)
	{
		if (taking_forks(phi))
			return (NULL);
		if (check_eating(phi))
		{
			sem_post(phi->parameters->forks); //TODO: handling error
			sem_post(phi->parameters->forks);
			return (NULL);
		}
		sem_post(phi->parameters->forks);
		sem_post(phi->parameters->forks);
		gettimeofday(&time_action, NULL);
		logs(phi->parameters->time_start,
&time_action, phi->nb, " is sleeping\n");
		usleep(phi->parameters->time_to_sleep * 1000);
		gettimeofday(&time_action, NULL);
		logs(phi->parameters->time_start,
&time_action, phi->nb, " is thinking\n");
	}
	return (NULL);
}
