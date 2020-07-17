/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 18:58:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/07/16 14:48:36 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** function {unmake_pairs}
**
** parameters:
** (t_philo_one *){phi} - philosopher's structure
**
** return (void)
**
** description:
** sort the philosophers by odd or even to avoid invoking 2 philosopher close to
** each other & avoid death that shouldn't happen.
*/

void	unmake_pairs(t_philo_one *phi)
{
	t_philosopher	*temp;
	t_philosopher	*ptr;
	t_philosopher	*odd;
	t_philosopher	*even;

	ptr = phi->philosophers;
	odd = phi->philosophers;
	temp = phi->philosophers->next;
	even = phi->philosophers->next;
	while (ptr)
	{
		if (ptr->nb % 2 && ptr->nb != 1)
		{
			odd->next = ptr;
			odd = odd->next;
		}
		else if (!(ptr->nb % 2) && ptr->nb != 2)
		{
			even->next = ptr;
			even = even->next;
		}
		ptr = ptr->next;
	}
	odd->next = temp;
	even->next = NULL;
}

/*
** function: {wait_philosophers}
**
** parameters:
** (t_philo_one *){phi} - program's structure
**
** return (int) - error's code
**
** description:
** wait for a philosopher to finish, then kill all if one has died.
*/

int		wait_philosophers(t_philo_one *phi)
{
	int				c;
	size_t			nb;
	t_philosopher	*ptr;

	nb = phi->parameters->number_of_time_each_philosophers_must_eat;
	ptr = phi->philosophers;
	while (ptr && !usleep(1000) && (c = (ptr->nb_eat < nb) ? 0 : c + 1) > -2)
		if (!ptr->time_last_meal || !ptr->next)
			ptr = (ptr->time_last_meal &&
c < phi->parameters->number_of_philosophers) ? phi->philosophers : NULL;
		else
			ptr = ptr->next;
	c = 0;
	ptr = phi->philosophers;
	while (c < phi->parameters->number_of_philosophers)
	{
		if (pthread_mutex_lock(ptr->lock_last_meal))
			return (ERROR_MUTEX);
		c += (!ptr->time_last_meal) ? 1 : !!(ptr->time_last_meal = NULL) + 0;
		if (pthread_mutex_unlock(ptr->lock_last_meal))
			return (ERROR_MUTEX);
		if (!(ptr = ptr->next) && c != phi->parameters->number_of_philosophers)
			ptr = !(c *= 0) ? phi->philosophers : NULL;
	}
	return (0);
}

/*
** function: {launch_philosophers}
**
** parameters:
** (t_philo_one *){phi} - program's structure
**
** return (int): error's code
**
** description:
** allocate and setup the lock on last_meal and
** launch all pthread on philosophers then call {wait_philosophers}
*/

int		launch_philosophers(t_philo_one *phi)
{
	t_philosopher *ptr;

	if (!(phi->parameters->time_start = malloc(sizeof(struct timeval))))
		return (ERROR_MALLOC);
	gettimeofday(phi->parameters->time_start, NULL);
	ptr = phi->philosophers;
	while (ptr && !(ptr->left_fork->nb_last = 0))
	{
		ptr->right_fork->nb_last = 0;
		if (!(ptr->time_last_meal = malloc(sizeof(struct timeval))))
			return (ERROR_MALLOC);
		ptr->time_last_meal->tv_sec = phi->parameters->time_start->tv_sec;
		ptr->time_last_meal->tv_usec = phi->parameters->time_start->tv_usec;
		ptr->nb_eat = 0;
		ptr->parameters = copy_parameters(phi->parameters);
		if (!(ptr->lock_last_meal = malloc(sizeof(pthread_mutex_t))))
			return (ERROR_MALLOC);
		if (pthread_mutex_init(ptr->lock_last_meal, NULL))
			return (ERROR_MUTEX);
		if (pthread_create(ptr->thread, NULL, &alive, ptr))
			return (ERROR_PTHREAD);
		ptr = ptr->next;
	}
	return ((wait_philosophers(phi) ? ERROR_MUTEX : 0) + usleep(100000));
}

/*
** function: {setup_philosopher}
**
** parameters:
** (t_philo_one *){phi} - program's structure,
** (int){i} - iterator of while in {init_philosophers},
** (t_philosopher **){ptr} - a pointer to a philosopher,
** (t_fork **){r_fork} - a pointer to a fork
**
** return (int): error's code
**
** description:
** setup a philosopher (splited version of {init_philosophers})
*/

int		setup_philosopher(t_philo_one *phi, int i, t_philosopher **ptr,
t_fork **r_fork)
{
	if (!((*ptr)->thread = malloc(sizeof(pthread_t))))
		return (ERROR_MALLOC);
	(*ptr)->right_fork = (i == phi->parameters->number_of_philosophers) ?
phi->philosophers->left_fork : malloc(sizeof(t_fork));
	if (!((*r_fork) = (*ptr)->right_fork) ||
((i != phi->parameters->number_of_philosophers) &&
!((*ptr)->right_fork->fork = malloc(sizeof(pthread_mutex_t)))))
		return (ERROR_MALLOC);
	if (pthread_mutex_init((*r_fork)->fork, NULL))
		return (ERROR_MUTEX);
	if (i != phi->parameters->number_of_philosophers &&
!((*ptr)->next = malloc(sizeof(t_philosopher))))
		return (ERROR_MALLOC);
	else if (i == phi->parameters->number_of_philosophers)
		(*ptr)->next = NULL;
	return (0);
}

/*
** function: {init_philosophers}
**
** parameters:
** (t_philo_one *){phi} - program's structure
**
** return (int): error's code
**
** description:
** init all philosophers
*/

int		init_philosophers(t_philo_one *phi)
{
	int				ret;
	int				i;
	t_philosopher	*ptr;
	t_fork			*r_fork;

	if (!(phi->philosophers = malloc(sizeof(t_philosopher))) ||
!(r_fork = malloc(sizeof(t_fork))) ||
!(r_fork->fork = malloc(sizeof(pthread_mutex_t))))
		return (ERROR_MALLOC);
	if (!(i = 0) && pthread_mutex_init(r_fork->fork, NULL))
		return (ERROR_MUTEX);
	ptr = phi->philosophers;
	while (ptr && (ptr->nb = i + 1) &&
i++ < phi->parameters->number_of_philosophers && (ptr->left_fork = r_fork))
	{
		if ((ret = setup_philosopher(phi, i, &ptr, &r_fork)))
			return (ret);
		ptr = ptr->next;
	}
	return (0);
}
