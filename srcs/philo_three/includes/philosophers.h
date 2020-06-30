/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:17:59 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/29 21:46:46 by lmartin          ###   ########.fr       */
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
	sem_t			*forks;
	sem_t			*available_eat;
	struct timeval	*time_start;
}					t_parameters;

typedef struct		s_philosopher
{
	int				pid;
	size_t			nb;
	size_t			nb_eat;
	t_parameters	*parameters;
	struct timeval	*time_last_meal;
	void			*next;
}					t_philosopher;

typedef struct		s_philo_three
{
	char			*name;
	t_parameters	*parameters;
	t_philosopher	*philosophers;
}					t_philo_three;

int					launch_philosophers(t_philo_three *phi);
int					init_philosophers(t_philo_three *phi);

#endif
