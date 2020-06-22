/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 00:10:25 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/23 00:46:50 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>

# include "errors.h"
# include "logs.h"
# include "utils.h"
# include "status.h"

typedef struct		s_philosopher
{
	int				pid;
	size_t			nb;
	size_t			nb_eat;
	t_parameters	*parameters;
	struct timeval	*time_last_meal;
	sem_t			*sem_last_meal;
	void			*next;
}					t_philosopher;

typedef struct		s_philo_three
{
	char			*name;
	t_parameters	*parameters;
	t_philosopher	*philosophers;
}					t_philo_three;

#endif
