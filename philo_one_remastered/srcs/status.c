/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 03:18:32 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/09 04:35:49 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			eating(struct timeval *start, t_philosopher *phi)
{
	pthread_mutex_lock(phi->left_fork);
	pthread_mutex_lock(phi->right_fork);	
	pthread_mutex_lock(phi->parameters->lock_last_meal);
	free(time_last_meal);
	gettimeofday(&time_last_meal);
	logs(start, phi->time_last_meal, phi->nb, "is eating\n");
	pthread_mutex_unlock(phi->parameters->lock_last_meal);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
}

void		alive(void *args)
{
	struct timeval	start;
	t_philosopher	*phi;

	phi = (t_philosopher *)args;
	while (1)
	pthread_mutex_lock(phi->parameters->lock_start);
	start.tv_sec = phi->parameters->time_start->tv_sec;
	start.tv_usec = phi->parameters->time_start->tv_usec;
	pthread_mutex_unlock(phi->parameters->lock_start);
	eat(&start, phi);
	//TODO: alive
}
