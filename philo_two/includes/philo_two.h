/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 13:12:39 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/19 02:52:33 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdlib.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

# include "errors.h"
# include "logs.h"
# include "utils.h"
# include "status.h"

typedef struct		s_philosopher
{
	size_t			nb;
	size_t			nb_eat;
	t_parameters	*parameters;
	pthread_t		*thread;
	struct timeval	*time_last_meal;
	sem_t			*sem_last_meal;
	void			*next;
}					t_philosopher;

typedef struct		s_philo_two
{
	char			*name;
	t_parameters	*parameters;
	t_philosopher	*philosophers;
}					t_philo_two;

#endif
