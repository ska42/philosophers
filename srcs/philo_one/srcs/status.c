/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 03:18:32 by lmartin           #+#    #+#             */
/*   Updated: 2020/07/17 04:28:55 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** function: {eating}
**
** parameters:
** (t_philosopher *){phi} - philosopher's structure
**
** return (int) - return no-null if death
**
** description:
** action of eat
*/

int			eating(t_philosopher *phi)
{
	int		ret;

	if (!phi->time_last_meal)
	{
		if (pthread_mutex_unlock(phi->lock_last_meal))
			throw_error(ERROR_MUTEX);
		return (1);
	}
	if (gettimeofday(phi->time_last_meal, NULL))
		throw_error(ERROR_TIMEOFDAY);
	if ((ret = logs(phi->parameters->time_start, phi->time_last_meal,
phi->nb, " is eating\n")))
		throw_error(ret);
	phi->nb_eat++;
	ft_usleep(phi->parameters->time_to_eat * 1000);
	if (pthread_mutex_unlock(phi->lock_last_meal))
		throw_error(ERROR_MUTEX);
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
	if (pthread_mutex_lock(phi->lock_last_meal))
		throw_error(ERROR_MUTEX);
	if (!phi->time_last_meal || ((size_t)((time_action.tv_sec -
phi->time_last_meal->tv_sec) * 1000 + (time_action.tv_usec -
phi->time_last_meal->tv_usec) * 0.001) > phi->parameters->time_to_die))
	{
		free(phi->time_last_meal);
		if ((ret = logs(phi->parameters->time_start,
&time_action, phi->nb, " died\n")))
			throw_error(ret);
		phi->time_last_meal = NULL;
	}
	ret = eating(phi);
	if (pthread_mutex_unlock(phi->right_fork->fork))
		throw_error(ERROR_MUTEX);
	if (pthread_mutex_unlock(phi->left_fork->fork))
		throw_error(ERROR_MUTEX);
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
** each philosophers must take 2 forks before eating. To avoid every
** philosophers to take the left or right fork at the same time and keep
** everyone safe of a blocked situation, just giving the first and second time,
** the right or left fork depending if the philosopher is odd or even.
*/

int			taking_forks(t_philosopher *phi)
{
	int				ret;
	int				i;
	t_fork			*fork;
	struct timeval	time_action;

	i = 0;
	if (!phi->time_last_meal)
		return (1);
	fork = ((phi->nb + i) % 2) ? phi->left_fork : phi->right_fork;
	while (i < 2)
	{
		if (fork->nb_last != phi->nb)
		{
			if (pthread_mutex_lock(fork->fork))
				throw_error(ERROR_MUTEX);
			if (gettimeofday(&time_action, NULL))
				throw_error(ERROR_TIMEOFDAY);
			if ((ret = logs(phi->parameters->time_start, &time_action, phi->nb,
" has taken a fork\n")))
				throw_error(ret);
			if ((fork->nb_last = phi->nb) && ++i != 2)
				fork = ((phi->nb + i) % 2) ? phi->left_fork : phi->right_fork;
		}
	}
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

	if ((ret = check_eating(phi)) || (phi->nb_eat ==
phi->parameters->number_of_time_each_philosophers_must_eat && (ret = 1)))
		return (ret);
	if (gettimeofday(&time_action, NULL))
		throw_error(ERROR_TIMEOFDAY);
	if ((ret = logs(phi->parameters->time_start,
&time_action, phi->nb, " is sleeping\n")))
		throw_error(ret);
	ft_usleep(phi->parameters->time_to_sleep * 1000);
	if (!phi->time_last_meal)
		return (1);
	if (gettimeofday(&time_action, NULL))
		throw_error(ERROR_TIMEOFDAY);
	if ((ret = logs(phi->parameters->time_start,
&time_action, phi->nb, " is thinking\n")))
		throw_error(ret);
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

	phi = (t_philosopher *)args;
	while (!taking_forks(phi) && !routine(phi))
		NULL;
	return (NULL);
}
