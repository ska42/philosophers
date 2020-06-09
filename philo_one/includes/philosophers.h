/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:52:03 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 23:07:16 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# include "action.h"
# include "errors.h"
# include "utils.h"
# include "forks.h"
# include "logs.h"

typedef struct		s_parameters
{
	size_t			number_of_philosopher;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_time_each_philosophers_must_eat;
}					t_parameters;

typedef struct		s_philosopher
{
	size_t			number;
	t_parameters	*parameters;
	t_lstforks		*left_fork;
	t_lstforks		*right_fork;
	struct timeval	*last_meal;
	pthread_mutex_t	*lock_last_meal;
	void			*next;	
}					t_philosopher;

typedef struct		s_program
{
	char			*name;
	t_parameters	*parameters;
	pthread_t		*philosophers;
	t_lstforks		*forks;
}					t_program;


int					check_die(t_philosopher *philosophers, t_program *phi);
int					launch_philosophers(t_philosopher *philosophers,
t_program *phi);
int					init_philosophers(t_program *phi);
t_philosopher		*new_philosopher(size_t number, t_lstforks *left_fork,
t_lstforks			*right_fork, t_parameters *parameters);

#endif
