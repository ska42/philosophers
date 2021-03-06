/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 03:41:19 by lmartin           #+#    #+#             */
/*   Updated: 2020/07/17 04:34:18 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
** function: {wait_philosophers}
**
** parameters:
** (t_philo_two *){phi} - program's structure
**
** return (int) - error's code
**
** description:
** wait for a philosopher to finish, then kill all if one has died.
*/

int		wait_philosophers(t_philo_two *phi)
{
	int				c;
	t_philosopher	*ptr;

	c = 0;
	ptr = phi->philosophers;
	while (ptr && !usleep(1000) && (c = (ptr->nb_eat <
phi->parameters->number_of_time_each_philosophers_must_eat) ? 0 : c + 1) > -2)
		if (!ptr->time_last_meal || !ptr->next)
			ptr = (ptr->time_last_meal &&
c < phi->parameters->number_of_philosophers) ? phi->philosophers : NULL;
		else
			ptr = ptr->next;
	c = 0;
	ptr = phi->philosophers;
	while (c < phi->parameters->number_of_philosophers)
	{
		if (sem_wait(ptr->sem_last_meal))
			return (ERROR_SEM);
		c += (!ptr->time_last_meal) ? 1 : !!(ptr->time_last_meal = NULL) + 0;
		if (sem_post(ptr->sem_last_meal))
			return (ERROR_SEM);
		if (!(ptr = ptr->next) && c != phi->parameters->number_of_philosophers)
			ptr = !(c *= 0) ? phi->philosophers : ptr;
	}
	return (0);
}

/*
** function: {launch_philosophers}
**
** parameters:
** (t_philo_two *){phi} - program's structure
**
** return (int): error's code
**
** description:
** allocate and setup the lock on last_meal and
** launch all pthread on philosophers then call {wait_philosophers}
*/

int		launch_philosophers(t_philo_two *phi)
{
	t_philosopher	*ptr;

	if (!(phi->parameters->time_start = malloc(sizeof(struct timeval))))
		return (ERROR_MALLOC);
	gettimeofday(phi->parameters->time_start, NULL);
	ptr = phi->philosophers;
	while (ptr && !(ptr->nb_eat = 0))
	{
		ptr->time_last_meal->tv_sec = phi->parameters->time_start->tv_sec;
		ptr->time_last_meal->tv_usec = phi->parameters->time_start->tv_usec;
		if (!(ptr->parameters = copy_parameters(phi->parameters)))
			return (ERROR_MALLOC);
		ptr = ptr->next;
	}
	ptr = phi->philosophers;
	while (ptr)
	{
		if (pthread_create(ptr->thread, NULL, &alive, ptr))
			return (ERROR_PTHREAD);
		ptr = ptr->next;
	}
	if (wait_philosophers(phi))
		return (ERROR_SEM);
	usleep(100000);
	return (0);
}

/*
** function: {init_philosophers}
**
** parameters:
** (t_philo_two *){phi} - program's structure
**
** return (int): error's code
**
** description:
** init all philosophers
*/

int		init_philosophers(t_philo_two *phi)
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
		if (!(ptr->thread = malloc(sizeof(pthread_t))))
			return (ERROR_MALLOC);
		if (!(ptr->time_last_meal = malloc(sizeof(struct timeval))))
			return (ERROR_MALLOC);
		sem_unlink("/sem_last_meal");
		if (!(ptr->sem_last_meal = sem_open("/sem_last_meal",
O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)))
			return (ERROR_SEM);
		if (i == phi->parameters->number_of_philosophers)
			ptr->next = NULL;
		else if (!(ptr->next = malloc(sizeof(t_philosopher))))
			return (ERROR_MALLOC);
		ptr = ptr->next;
	}
	return (0);
}
