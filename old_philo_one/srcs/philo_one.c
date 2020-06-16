/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:51:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 21:38:57 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Check for arguments (like too few philosophers)
*/

int			check_args(t_program *phi) // TODO: Check args like nb philosophers or nb_eat
{
	(void)phi;
	return (0);
}

/*
** init program parameters:
** program number_of_philosopher time_to_die time_to_eattime_to_sleep
** [number_of_time_each_philosophers_must_eat]
** and put it in t_program *phi
*/

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

/*
** PHILOSOPHERS PHILO_ONE
*/

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
