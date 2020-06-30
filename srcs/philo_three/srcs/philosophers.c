/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:16:37 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/30 02:29:32 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** function: {wait_philosophers}
**
** parameters:
** (t_philo_three *){phi} - program's structure
**
** return (int) - error's code
**
** description:
** wait for a philosopher to finish, then kill all if one has died.
*/

int		wait_philosophers(t_philo_three *phi)
{
	int				nb_end;
	int				status;
	t_philosopher	*ptr;

	ptr = phi->philosophers;
	status = 0;
	nb_end = 0;
	while (!status && nb_end < phi->parameters->number_of_philosophers)
	{
		if (waitpid(-1, &status, 0) < 0)
			throw_error(ERROR_FORK);
		nb_end++;
	}
	if (status)
	{
		ptr = phi->philosophers;
		while (ptr)
		{
			if (kill(ptr->pid, SIGINT))
				throw_error(ERROR_KILL);
			ptr = ptr->next;
		}
	}
	return (0);
}

/*
** function: {launch_philosophers}
**
** parameters:
** (t_philo_three *){phi} - program's structure
**
** return (int): error's code
**
** description:
** allocate and setup the lock on last_meal and
** launch all pthread on philosophers then call {wait_philosophers}
*/

int		launch_philosophers(t_philo_three *phi)
{
	int				pid;
	t_philosopher	*ptr;

	if (!(phi->parameters->time_start = malloc(sizeof(struct timeval))))
		return (ERROR_MALLOC);
	if (gettimeofday(phi->parameters->time_start, NULL))
		return (ERROR_TIMEOFDAY);
	ptr = phi->philosophers;
	while (ptr)
	{
		ptr->time_last_meal->tv_sec = phi->parameters->time_start->tv_sec;
		ptr->time_last_meal->tv_usec = phi->parameters->time_start->tv_usec;
		ptr->nb_eat = 0;
		if (!(ptr->parameters = copy_parameters(phi->parameters)))
			return (ERROR_MALLOC);
		if (!(pid = fork()))
			alive((void *)ptr);
		if (pid < 0)
			return (ERROR_FORK);
		ptr->pid = pid;
		ptr = ptr->next;
	}
	return (wait_philosophers(phi));
}

/*
** function: {init_philosophers}
**
** parameters:
** (t_philo_three *){phi} - program's structure
**
** return (int): error's code
**
** description:
** init all philosophers
*/

int		init_philosophers(t_philo_three *phi)
{
	int				i;
	t_philosopher	*ptr;

	if (!(phi->philosophers = malloc(sizeof(t_philosopher))))
		return (ERROR_MALLOC);
	i = 0;
	ptr = phi->philosophers;
	while (ptr && (ptr->nb = i + 1) &&
i++ < phi->parameters->number_of_philosophers)
	{
		if (!(ptr->time_last_meal = malloc(sizeof(struct timeval))))
			return (ERROR_MALLOC);
		if (i < phi->parameters->number_of_philosophers &&
	!(ptr->next = malloc(sizeof(t_philosopher))))
			return (ERROR_MALLOC);
		ptr = ptr->next;
	}
	return (0);
}
