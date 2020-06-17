/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 00:07:02 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/17 12:49:29 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** function: {clean_all}
**
** parameters:
** (t_philo_one *){phi} - pointer to the program's structure
**
** return (int) - return 0 to permit to call the function on a return
**
** description:
** free all philosophers and parameters
*/

int		clean_all(t_philo_one *phi)
{
	void			*temp;
	t_philosopher	*ptr;

	ptr = phi->philosophers;
	while (ptr)
	{
		temp = ptr->next;
		free(ptr->parameters->time_start);
		free(ptr->parameters);
		pthread_mutex_destroy(ptr->left_fork->fork);
		pthread_mutex_destroy(ptr->lock_last_meal);
		free(ptr->left_fork);
		free(ptr->lock_last_meal);
		free(ptr->thread);
		free(ptr->time_last_meal);
		free(ptr);
		ptr = temp;
	}
	free(phi->parameters->time_start);
	free(phi->parameters);
	return (0);
}

/*
** function: {init_args}
**
** parameters:
** (int){argc} - number of arguments {argv},
** (char **){argv} - array of (char *) arguments,
** (t_philo_one *){phi} - pointer to stucture to fill
**
** return (int): too many arguments, wrong argument or others...
**
** description:
** init all arguments from {argv}
*/

int		init_args(int argc, char *argv[], t_philo_one *phi)
{
	if (!(phi->parameters = malloc(sizeof(t_parameters))))
		return (ERROR_MALLOC);
	if (argc < 5 || argc > 6)
		return (TOO_MANY_ARGS);
	if (ft_atos(argv[1], (size_t *)&phi->parameters->number_of_philosophers))
		return (WRONG_ARG);
	if (phi->parameters->number_of_philosophers < 2)
		return (WRONG_ARG);
	if ((ft_atos(argv[2], &phi->parameters->time_to_die)))
		return (WRONG_ARG);
	if ((ft_atos(argv[3], &phi->parameters->time_to_eat)))
		return (WRONG_ARG);
	if ((ft_atos(argv[4], &phi->parameters->time_to_sleep)))
		return (WRONG_ARG);
	if (argc == 6 && (ft_atos(argv[5],
(size_t *)&phi->parameters->number_of_time_each_philosophers_must_eat)))
		return (WRONG_ARG);
	else if (argc == 5)
		phi->parameters->number_of_time_each_philosophers_must_eat = -1;
	return (0);
}

/*
** PHILO_ONE
**
** description:
** philosopher with threads and mutex.
**
** special rules:
** 1. One fork between each philosopher, therefore there will be a fork at the
** right and at the left of each philosopher.
** 2. To avoid philosophers duplicating forks, you should protect the forks
** state with a mutex for each of them.
** 3. Each philosopher should be a thread.
*/

int		main(int argc, char *argv[])
{
	int				ret;
	t_philo_one		phi;

	phi.name = argv[0];
	if ((ret = init_args(argc, argv, &phi)))
		return (throw_error(phi.name, ret) + clean_all(&phi));
	if ((ret = init_philosophers(&phi)))
		return (throw_error(phi.name, ret) + clean_all(&phi));
	unmake_pairs(&phi);
	if ((ret = launch_philosophers(&phi)))
		return (throw_error(phi.name, ret) + clean_all(&phi));
	clean_all(&phi);
}
