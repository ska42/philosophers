/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 01:06:47 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/16 01:18:32 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# include "errors.h"
# include "logs.h"
# include "utils.h"
# include "status.h"

typedef struct		s_fork
{
	pthread_mutex_t	*fork;
	size_t			nb_last;
}					t_fork;

typedef struct		s_philosopher
{
	size_t			nb;
	size_t			nb_eat;
	t_parameters	*parameters;
	pthread_t		*thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t *lock_last_meal;
	struct timeval	*time_last_meal;
	void			*next;
}					t_philosopher;

typedef struct		s_philo_one
{
	char			*name;
	t_parameters	*parameters;
	t_philosopher	*philosophers;
}					t_philo_one;

#endif
