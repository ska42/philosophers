/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:52:03 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 02:09:29 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

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
}					t_philosopher;

typedef struct		s_program
{
	char			*name;
	t_parameters	*parameters;
	pthread_t		*philosophers;
	t_lstforks		*forks;
}					t_program;

t_philosopher		*new_philosopher(size_t number, t_lstforks *left_fork,
t_lstforks			*right_fork, t_parameters *parameters);

#endif
