/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 03:18:32 by lmartin           #+#    #+#             */
/*   Updated: 2020/07/17 04:30:10 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** function: {eating}
**
** parameters:
** (t_philosopher *){phi} - philosopher's structure
**
** return (int) - error's code
**
** description:
** action of eat
*/

int			eating(t_philosopher *phi)
{
	if (!phi->time_last_meal)
		return (1);
	if (gettimeofday(phi->time_last_meal, NULL))
		throw_error(ERROR_TIMEOFDAY);
	logs(phi->parameters->time_start, phi->time_last_meal,
phi->nb, " is eating\n");
	phi->nb_eat++;
	ft_usleep(phi->parameters->time_to_eat * 1000);
	return (0);
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
	int				ret;
	struct timeval	time_action;

	if (gettimeofday(&time_action, NULL))
		throw_error(ERROR_TIMEOFDAY);
	if (!phi->time_last_meal || ((size_t)((time_action.tv_sec -
phi->time_last_meal->tv_sec) * 1000 + (time_action.tv_usec -
phi->time_last_meal->tv_usec) * 0.001) > phi->parameters->time_to_die))
	{
		free(phi->time_last_meal);
		logs(phi->parameters->time_start,
&time_action, phi->nb, " died\n");
		phi->time_last_meal = NULL;
		ret = -1;
	}
	else
		ret = eating(phi);
	if (sem_post(phi->parameters->forks))
		throw_error(ERROR_SEM);
	if (sem_post(phi->parameters->forks))
		throw_error(ERROR_SEM);
	if (sem_post(phi->parameters->available_eat))
		throw_error(ERROR_SEM);
	return (ret);
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
** each philosophers must take 2 forks before eating.
** {phi->parameters->available_eat} is done to avoid that philosophers take all
** 1 fork and deadlock
*/

int			taking_forks(t_philosopher *phi)
{
	struct timeval	time_action;

	if (!phi->time_last_meal)
		return (1);
	if (sem_wait(phi->parameters->available_eat))
		throw_error(ERROR_SEM);
	if (sem_wait(phi->parameters->forks))
		throw_error(ERROR_SEM);
	if (gettimeofday(&time_action, NULL))
		throw_error(ERROR_TIMEOFDAY);
	logs(phi->parameters->time_start, &time_action, phi->nb,
" has taken a fork\n");
	if (sem_wait(phi->parameters->forks))
		throw_error(ERROR_SEM);
	if (gettimeofday(&time_action, NULL))
		throw_error(ERROR_TIMEOFDAY);
	logs(phi->parameters->time_start, &time_action, phi->nb,
" has taken a fork\n");
	return (0);
}

/*
** function: {routine}
**
** parameters:
** (t_philosopher *){phi} - philosopher
**
** return (int) - no-null if death
**
** description:
** routine of the philosopher (thinking - eating - sleeping)
*/

int			routine(t_philosopher *phi)
{
	int				ret;
	struct timeval	time_action;

	if ((ret = check_eating(phi)))
		return (-1);
	if (phi->nb_eat ==
phi->parameters->number_of_time_each_philosophers_must_eat)
		return (1);
	if (gettimeofday(&time_action, NULL))
		throw_error(ERROR_TIMEOFDAY);
	logs(phi->parameters->time_start,
&time_action, phi->nb, " is sleeping\n");
	ft_usleep(phi->parameters->time_to_sleep * 1000);
	if (!phi->time_last_meal)
		return (1);
	if (gettimeofday(&time_action, NULL))
		throw_error(ERROR_TIMEOFDAY);
	logs(phi->parameters->time_start,
&time_action, phi->nb, " is thinking\n");
	return (0);
}

/*
** function: {alive}
**
** parameters:
** (philosopher *){phi} - contain philosopher's structure
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
	int				ret;

	while (!taking_forks(phi) && !(ret = routine(phi)))
		NULL;
	if (ret == -1)
		exit(1);
	exit(0);
}
