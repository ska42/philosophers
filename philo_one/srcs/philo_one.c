/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:51:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/05 22:49:09 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*alive(void *args)
{
	t_philosopher *philosopher;

	philosopher = (t_philosopher *)args;
	while (1) // TODO: wait for others thread to die nb time each philosophers must eat 
	{
		logs(philosopher->number, MSG_SLEEPING);
		pthread_mutex_lock(philosopher->left_fork->lock);
		pthread_mutex_lock(philosopher->left_fork->lock);
		logs(philosopher->number, MSG_EATING);
		usleep(philosopher->parameters->time_to_eat);
		pthread_mutex_unlock(philosopher->right_fork->lock);
		pthread_mutex_unlock(philosopher->right_fork->lock);
		logs(philosopher->number, MSG_SLEEPING);
		usleep(philosopher->parameters->time_to_sleep);
	}
	return (NULL);
}

int			init_philosophers(t_program *phi)
{	
	size_t			number;
	t_lstforks		*fork;
	pthread_t		*ptr;
	t_philosopher	*philosopher;
	
	number = 1;
	fork = phi->forks;
	ptr = phi->philosophers;
	while (fork)
	{
		if (!(philosopher = new_philosopher(number, fork,
(fork->next) ? fork->next : phi->forks, phi->parameters)))
			return (ERR_MALLOC);
		if (pthread_create(ptr, NULL, &alive, philosopher))
			return (ERR_PTHREAD_CREATE);
		number++;
		ptr++;
		fork = fork->next;
	}
	ptr = phi->philosophers;
	while (*ptr)
	{
		pthread_join(*ptr, NULL);	
		ptr++;
	}
	// TODO: free all philosophers
	return (0);
}

int			check_args(t_program *phi) // TODO: Check args like nb philosophers or nb_eat
{
	(void)phi;
	return (0);
}

int			init_program(t_program *phi, char *argv[])
{
	int				ret;
	size_t			i;

	phi->name = argv[0];
	if (!(phi->parameters = malloc(sizeof(t_parameters))))
		return (ERR_MALLOC);
	if (ft_atos(argv[1], &phi->parameters->number_of_philosopher) < 0)
		return (ERR_WRONG_ARG);
	if (ft_atos(argv[2], &phi->parameters->time_to_die) < 0)
		return (ERR_WRONG_ARG);
	if (ft_atos(argv[3], &phi->parameters->time_to_eat) < 0)
		return (ERR_WRONG_ARG);
	if (ft_atos(argv[4], &phi->parameters->time_to_sleep) < 0)
		return (ERR_WRONG_ARG);
	if (ft_atos(argv[5], 
&phi->parameters->number_of_time_each_philosophers_must_eat) < 0)
		return (ERR_WRONG_ARG);
	i = phi->parameters->number_of_philosopher;
	while (i--)
		if ((ret = forks_add_back(&phi->forks)) < 0)
			return (ret);
	if (!(phi->philosophers = malloc(sizeof(pthread_t) *
phi->parameters->number_of_philosopher)))
		return (ERR_MALLOC);
	return (0);
}

int			main(int argc, char *argv[])
{
	int				ret;
	t_program		phi;

	if (argc != 6)
		return (throw_error(argv[0], ERR_NB_ARGS));
	if ((ret = init_program(&phi, argv)) < 0)
		return (throw_error(phi.name, ret));
	if ((ret = check_args(&phi)) < 0)
		return (throw_error(phi.name, ret));
	if ((ret = init_locks(&phi.forks)) < 0)
		return (throw_error(phi.name, ret));
	if ((ret = init_philosophers(&phi)) < 0)
		return (throw_error(phi.name, ret));	
	// TODO: free and clean
}
