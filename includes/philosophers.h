/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:52:03 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/19 23:20:35 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

typedef struct		s_philosophers
{
	size_t			number_of_philosopher;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			number_of_time_each_philosophers_must_eat;
}					t_philosophers;

#endif
