/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 01:06:47 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/09 01:38:52 by lmartin          ###   ########.fr       */
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

typedef struct		s_parameters
{
	int				number_of_philosopher;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_time_each_philosophers_must_eat;
}					t_parameters;

typedef struct		s_philosopher
{
	size_t			nb;
	t_parameters	*parameters;
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
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
