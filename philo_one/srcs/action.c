/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 23:01:13 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 23:10:42 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			eat(t_philosopher *philosopher)
{
	struct timeval	last_meal;

	pthread_mutex_lock(philosopher->left_fork->lock);
	pthread_mutex_lock(philosopher->right_fork->lock);
	if (!philosopher->last_meal) //dead
		return (-1);
	gettimeofday(&last_meal, NULL);
	logs(&last_meal, philosopher->number, MSG_EATING);
	pthread_mutex_lock(philosopher->lock_last_meal);
	philosopher->last_meal = &last_meal;
	pthread_mutex_unlock(philosopher->lock_last_meal);
	usleep(philosopher->parameters->time_to_eat);
	pthread_mutex_unlock(philosopher->left_fork->lock);
	pthread_mutex_unlock(philosopher->right_fork->lock);
	return (0);
}

/*
 ** pthread function while a philosopher is alive and running
 */

void		*alive(void *args)
{	
	struct timeval	tv;
	struct timeval	last_meal;
	t_philosopher	*philosopher;
	//size_t			has_eat;

	philosopher = (t_philosopher *)args;
	gettimeofday(&last_meal, NULL);
	pthread_mutex_lock(philosopher->lock_last_meal);
	philosopher->last_meal = &last_meal;
	pthread_mutex_unlock(philosopher->lock_last_meal);
	//has_eat = 0;
	while (1) // has_eat < philosopher->parameters->number_of_time_each_philosophers_must_eat) // TODO: wait for others thread to die nb time each philosophers must eat 
	{
			gettimeofday(&tv, NULL);
			logs(&tv, philosopher->number, MSG_THINKING);
			if (eat(philosopher))
				return (NULL);	
			gettimeofday(&tv, NULL);
			logs(&tv, philosopher->number, MSG_SLEEPING);
			usleep(philosopher->parameters->time_to_sleep);
	}
	return (NULL);
}
