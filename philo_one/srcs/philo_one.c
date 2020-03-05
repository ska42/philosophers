/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:51:31 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/20 22:02:39 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			init_philosophers(t_philosophers *phi, char *argv[])
{
	size_t			i;

	(*phi).name = argv[0];
	if (argc != 5)
		return (throw_error((*phi).name, ERR_NB_ARGS));
	if (ft_atos(argv[1], &(*phi).number_of_philosopher) < 0)
		return (throw_error((*phi).name, ERR_WRONG_ARG));
	if (ft_atos(argv[2], &(*phi).time_to_die) < 0)
		return (throw_error((*phi).name, ERR_WRONG_ARG));
	if (ft_atos(argv[3], &(*phi).time_to_sleep) < 0)
		return (throw_error((*phi).name, ERR_WRONG_ARG));
	if (ft_atos(argv[4], &(*phi).number_of_time_each_philosophers_must_eat) < 0)
		return (throw_error((*phi).name, ERR_WRONG_ARG));
	i = ((*phi).number_of_philosopher == 1) : 2 ? (*phi).number_of_philosopher;
	while (--i)
		if (forks_add_back(&(*phi).forks) < 0)
			return (ERR_MALLOC);
	return (0);
}

int			main(int argc, char *argv[])
{
	int				ret;
	t_philosophers	philos;

	if ((ret = init_philosophers(&philos, argv)) < 0)
		return (ret);
}
