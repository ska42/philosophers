/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:17 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/16 19:10:54 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef struct		s_parameters
{
	int				number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_time_each_philosophers_must_eat;
	struct timeval	*time_start;
}					t_parameters;

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

void				unmake_pairs(t_philo_one *phi);
int					launch_philosophers(t_philo_one *phi);
int					setup_philosopher(t_philo_one *phi, int i,
t_philosopher **ptr, t_fork **r_fork);
int					init_philosophers(t_philo_one *phi);

#endif
