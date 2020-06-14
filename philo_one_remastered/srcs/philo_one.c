/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 00:07:02 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/14 03:33:46 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** function: {wait_philosophers}
**
** parameters:
** (t_philo_one *){phi} - program's structure
**
** return (void)
**
** description:
** wait for a philosopher to finish, then kill all if one has died.
*/

void	wait_philosophers(t_philo_one *phi)
{
	int				count;
	t_philosopher	*ptr;

	ptr = phi->philosophers;
	while (!(count = 0) && ptr && !pthread_mutex_lock(ptr->lock_last_meal))
	{
		if (!ptr->time_last_meal &&
(int)ptr->nb_eat != phi->parameters->number_of_time_each_philosophers_must_eat
	&& !pthread_mutex_unlock(ptr->lock_last_meal))
			break ;
		else if ((int)ptr->nb_eat !=
phi->parameters->number_of_time_each_philosophers_must_eat && !ptr->next &&
!pthread_mutex_unlock(ptr->lock_last_meal) && (ptr = phi->philosophers))
			continue ;
		ptr = (!pthread_mutex_unlock(ptr->lock_last_meal)) ? ptr->next : ptr;
	}
	ptr = phi->philosophers;
	while (count < phi->parameters->number_of_philosophers &&
!pthread_mutex_lock(ptr->lock_last_meal))
	{
		count += (!ptr->time_last_meal) ? !(ptr->time_last_meal = NULL) + 1 : 0;
		ptr = (!pthread_mutex_unlock(ptr->lock_last_meal)) ? ptr->next : ptr;
		if (!ptr && count != phi->parameters->number_of_philosophers)
			ptr = !(count *= 0) ? phi->philosophers : ptr;
	}
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
	while (ptr)
	{
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
	wait_philosophers(phi);
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
	int				i;
	t_philosopher	*ptr;
	pthread_mutex_t	*r_fork;

	if (!(phi->philosophers = malloc(sizeof(t_philosopher))) ||
(!(r_fork = malloc(sizeof(pthread_mutex_t)))))
		return (ERROR_MALLOC);
	if (!(i = 0) && pthread_mutex_init(r_fork, NULL))
		return (ERROR_MUTEX);
	ptr = phi->philosophers;
	while (ptr && (ptr->nb = i + 1) &&
i++ < phi->parameters->number_of_philosophers && (ptr->left_fork = r_fork))
	{
		if (!(ptr->thread = malloc(sizeof(pthread_t))))
			return (ERROR_MALLOC);
		ptr->right_fork = (i == phi->parameters->number_of_philosophers) ?
phi->philosophers->left_fork : malloc(sizeof(pthread_mutex_t));
		if (!(r_fork = ptr->right_fork) || pthread_mutex_init(r_fork, NULL))
			return ((!r_fork) ? ERROR_MALLOC : ERROR_MUTEX);
		if (i != phi->parameters->number_of_philosophers &&
!(ptr->next = malloc(sizeof(t_philosopher))))
			return (ERROR_MALLOC);
		ptr = ptr->next;
	}
	return (0);
}

/*
** function: {init_args}
**
** parameters:
** (int){argc} - number of arguments {argv},
** (char **){argv} - array of (char *) arguments,
** (t_philo_one){phi} - pointer to stucture to fill
**
** return (int): too many arguments, wrong argument or others...
**
** description:
** init all arguments from {argv}
*/

int		init_args(int argc, char *argv[], t_philo_one *phi)
{
	if (!(phi->parameters = malloc(sizeof(t_parameters))))
		return (ERROR_MALLOC);
	if (argc < 5 || argc > 6)
		return (TOO_MANY_ARGS);
	if (ft_atos(argv[1], (size_t *)&phi->parameters->number_of_philosophers))
		return (WRONG_ARG);
	if (phi->parameters->number_of_philosophers < 2)
		return (WRONG_ARG);
	if ((ft_atos(argv[2], &phi->parameters->time_to_die)))
		return (WRONG_ARG);
	if ((ft_atos(argv[3], &phi->parameters->time_to_eat)))
		return (WRONG_ARG);
	if ((ft_atos(argv[4], &phi->parameters->time_to_sleep)))
		return (WRONG_ARG);
	if (argc == 6 && (ft_atos(argv[5],
(size_t *)&phi->parameters->number_of_time_each_philosophers_must_eat)))
		return (WRONG_ARG);
	else if (argc == 5)
		phi->parameters->number_of_time_each_philosophers_must_eat = -1;
	return (0);
}

/*
** PHILO_ONE
**
** description:
** philosopher with threads and mutex.
**
** special rules:
** 1. One fork between each philosopher, therefore there will be a fork at the
** right and at the left of each philosopher.
** 2. To avoid philosophers duplicating forks, you should protect the forks
** state with a mutex for each of them.
** 3. Each philosopher should be a thread.
*/

int		main(int argc, char *argv[])
{
	int				ret;
	t_philo_one		phi;

	phi.name = argv[0];
	if ((ret = init_args(argc, argv, &phi)))
		return (throw_error(phi.name, ret));
	if ((ret = init_philosophers(&phi)))
		return (throw_error(phi.name, ret));
	if ((ret = launch_philosophers(&phi)))
		return (throw_error(phi.name, ret));
}
