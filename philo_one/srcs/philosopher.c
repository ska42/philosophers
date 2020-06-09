/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:36:42 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/11 00:09:12 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Check if a philosopher has died
*/

#include <stdio.h>

int			check_die(t_philosopher *philosophers, t_program *phi)
{
	
	struct timeval	tv;
	t_philosopher	*philosopher;

	(void)phi;
	philosopher = philosophers;
	while (philosopher)
	{
		gettimeofday(&tv, NULL);
		pthread_mutex_lock(philosopher->lock_last_meal);
		if (philosopher->last_meal)
		{
			printf("%lf\n", philosopher->last_meal->tv_sec + philosopher->last_meal->tv_usec * 0.000001);
			printf("%lf\n", phi->parameters->time_to_die * 0.001);
			logs(&tv, philosopher->number, MSG_DEATH);
			philosopher->last_meal = NULL;
			pthread_mutex_unlock(philosopher->lock_last_meal);
			philosopher = philosophers;
			while (philosopher)
			{
				pthread_mutex_lock(philosopher->lock_last_meal);
				philosopher->last_meal = NULL;
				pthread_mutex_unlock(philosopher->lock_last_meal);
				philosopher = philosopher->next;
			}
			return (0);
		}
		pthread_mutex_unlock(philosopher->lock_last_meal);
		philosopher = (!philosopher->next) ? philosophers : philosopher->next;
	}
	return (0);
}

/*
** Launch all pthread on phi->philosophers with parameters that are
** t_philosopher
*/

int			launch_philosophers(t_philosopher *philosophers, t_program *phi)
{
	pthread_t		*ptr;
	t_philosopher	*philosopher;
	
	ptr = phi->philosophers;
	philosopher = philosophers;
	while (philosopher)
	{		
		if (pthread_mutex_init(philosopher->lock_last_meal, NULL))
			return (ERR_MUTEX_INIT);
		if (pthread_create(ptr, NULL, &alive, philosopher))
			return (ERR_PTHREAD_CREATE);
		ptr++;
		philosopher = philosopher->next;
	}
	return (check_die(philosophers, phi));
}

/*
** Init all philosophers by creating with number, their forks and
** phi->parameters then launch all pthread on launch_philosophers
*/

int			init_philosophers(t_program *phi)
{	
	size_t			number;
	t_lstforks		*fork;
	t_philosopher	*first;
	t_philosopher	*philosopher;
	t_philosopher	*prev;
	
	number = 0;
	fork = phi->forks;
	prev = NULL;
	while (fork && ++number)
	{
		if (!(philosopher = new_philosopher(number, fork,
(fork->next) ? fork->next : phi->forks, phi->parameters)))
			return (ERR_MALLOC);
		first = (!prev) ? philosopher : first;
		if (prev)
			prev->next = philosopher;
		prev = philosopher;
		fork = fork->next;
	}
		/*	
	while (*ptr)
	{
		pthread_join(*ptr, NULL);	
		ptr++;
	}*/
	// TODO: free all philosophers
	return (launch_philosophers(first, phi));
}

/*
** Create a new philosopher and return it
*/

t_philosopher	*new_philosopher(size_t number, t_lstforks *left_fork,
t_lstforks *right_fork, t_parameters *parameters)
{
	t_philosopher	*philosopher;

	if (!(philosopher = malloc(sizeof(t_philosopher))))
		return (NULL);
	philosopher->number = number;
	philosopher->left_fork = left_fork;
	philosopher->right_fork = right_fork;
	philosopher->parameters = parameters;
	philosopher->last_meal = NULL;
	if (!(philosopher->lock_last_meal = malloc(sizeof(pthread_mutex_t))))
	{
		free(philosopher);
		return (NULL);
	}
	philosopher->next = NULL;
	return (philosopher);
}
