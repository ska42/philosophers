/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 00:08:05 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/23 00:52:02 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** function: {wait_philosophers}
**
** parameters:
** (t_philo_three *){phi} - program's structure
**
** return (void)
**
** description:
** wait for a philosopher to finish, then kill all if one has died.
*/

#include <stdio.h>

void	wait_philosophers(t_philo_three *phi)
{
	t_philosopher	*ptr;

	ptr = phi->philosophers;
	printf("ok\n");
	wait(NULL);
	/*
	while (ptr) // TODO: All sem error handler
	{
		if (sem_wait(ptr->sem_last_meal))
			printf("OHOHOHOHOH\n");
		//TODO: NB_EAT EN SEMAPHORE POUR CHAQUE PHILOSOPHE
		if (ptr->nb_eat != phi->parameters->number_of_time_each_philosophers_must_eat
	&& sem_wait(ptr->sem_last_meal))
			break ;
		else if (ptr->nb_eat !=
phi->parameters->number_of_time_each_philosophers_must_eat && !ptr->next &&
!sem_post(ptr->sem_last_meal) && (ptr = phi->philosophers))
			continue ;
		ptr = (!sem_post(ptr->sem_last_meal)) ? ptr->next : ptr;
	}*/
	printf("ALLOOOOOOO\n");
	ptr = phi->philosophers;
	while (ptr)
	{
		kill(ptr->pid, SIGINT);
		if (!sem_wait(ptr->sem_last_meal))
		{
			sem_post(ptr->sem_last_meal);
			sem_close(ptr->sem_last_meal);//TODO: CHECK
		}	
		ptr = ptr->next;
	}
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
	gettimeofday(phi->parameters->time_start, NULL);
	ptr = phi->philosophers;
	while (ptr)
	{
		ptr->time_last_meal->tv_sec = phi->parameters->time_start->tv_sec;
		ptr->time_last_meal->tv_usec = phi->parameters->time_start->tv_usec;
		ptr->nb_eat = 0;
		ptr->parameters = copy_parameters(phi->parameters);
		if (!(pid = fork()))
		{
			alive((void *)ptr);
			exit(0);	
		}
		ptr->pid = pid;
		ptr = ptr->next;
	}
	wait_philosophers(phi);
	return (0);
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
		sem_unlink("/sem_last_meal");
		if (!(ptr->sem_last_meal = sem_open("/sem_last_meal", O_CREAT, S_IRWXU, 1)))
			return (ERROR_SEM);	
		if (i < phi->parameters->number_of_philosophers &&
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
** (t_philo_three *){phi} - pointer to stucture to fill
**
** return (int): too many arguments, wrong argument or others...
**
** description:
** init all arguments from {argv}
*/

int		init_args(int argc, char *argv[], t_philo_three *phi)
{
	if (!(phi->parameters = malloc(sizeof(t_parameters))))
		return (ERROR_MALLOC);
	if (argc < 5 || argc > 6)
		return (TOO_MANY_ARGS);
	if (ft_atos(argv[1], (size_t *)&phi->parameters->number_of_philosophers))
		return (WRONG_ARG);
	if (phi->parameters->number_of_philosophers < 2)
		return (WRONG_ARG);
	sem_unlink("/forks");
	if (!(phi->parameters->forks = sem_open("/forks", O_CREAT, S_IRWXU,
phi->parameters->number_of_philosophers)))
		return (ERROR_SEM);
	sem_unlink("/a_eat");
	if (!(phi->parameters->available_eat = sem_open("/a_eat", O_CREAT, S_IRWXU,
(int)(phi->parameters->number_of_philosophers / 2))))
		return (ERROR_SEM);
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
** PHILO_THREE
*/

int		main(int argc, char *argv[])
{
	int				ret;
	t_philo_three	phi;

	phi.name = argv[0];
	if ((ret = init_args(argc, argv, &phi)))
		return (throw_error(phi.name, ret));
	if ((ret = init_philosophers(&phi)))
		return (throw_error(phi.name, ret));
	if ((ret = launch_philosophers(&phi)))
		return (throw_error(phi.name, ret));
	//TODO : clear all and close sem
	return (0);
}
