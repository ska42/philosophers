/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 03:42:11 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/24 03:44:54 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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

int		launch_philosophers(t_philo_two *phi);
int		init_philosophers(t_philo_two *phi);

#endif
