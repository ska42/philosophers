/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 00:08:05 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/29 21:31:09 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** function: {clean_philosopher}
**
** parameters:
** (t_philosopher *){phi} - a philosopher
**
** return (void)
**
** description:
** free a philosopher and his parameters
*/

void	clean_philosopher(t_philosopher *phi)
{
	if (phi->parameters)
		free(phi->parameters->time_start);
	free(phi->parameters);
	free(phi->time_last_meal);
	free(phi);
}

/*
** function: {clean_all}
**
** parameters:
** (t_philo_three *){phi} - pointer to the program's structure
**
** return (int) - return 0 to permit to call the function on a return
**
** description:
** free all philosophers and parameters
*/

int		clean_all(t_philo_three *phi)
{
	void			*temp;
	t_philosopher	*ptr;

	ptr = (phi) ? phi->philosophers : NULL;
	while (ptr)
	{
		temp = ptr->next;
		clean_philosopher(ptr);
		ptr = temp;
	}
	if (phi && phi->parameters)
	{
		if (phi->parameters->forks && sem_close(phi->parameters->forks))
			throw_error(ERROR_SEM);
		if (phi->parameters->available_eat &&
sem_close(phi->parameters->available_eat))
			throw_error(ERROR_SEM);
		free(phi->parameters->time_start);
	}
	if (phi)
		free(phi->parameters);
	return (0);
}

/*
** function: {init_args}
**
** parameters:
** (int){argc} - number of arguments {argv},
** (char **){argv} - array of (char *) arguments,
** (t_philo_three *){phi} - pointer to stucture to fill
**
** return (int): too many arguments, wrong argument or others...
**
** description:
** init all arguments from {argv}
*/

int		init_args(int argc, char *argv[], t_philo_three *phi)
{
	if (!(phi->parameters = malloc(sizeof(t_parameters))))
		return (ERROR_MALLOC);
	if (argc < 5 || argc > 6)
		return (TOO_MANY_ARGS);
	if (ft_atos(argv[1], (size_t *)&phi->parameters->number_of_philosophers))
		return (WRONG_ARG);
	if (phi->parameters->number_of_philosophers < 2)
		return (WRONG_ARG);
	sem_unlink("/forks");
	if (!(phi->parameters->forks = sem_open("/forks", O_CREAT, S_IRWXU,
phi->parameters->number_of_philosophers)))
		return (ERROR_SEM);
	sem_unlink("/a_eat");
	if (!(phi->parameters->available_eat = sem_open("/a_eat", O_CREAT, S_IRWXU,
(int)(phi->parameters->number_of_philosophers / 2))))
		return (ERROR_SEM);
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
** PHILO_THREE
*/

int		main(int argc, char *argv[])
{
	int				ret;
	t_philo_three	phi;

	phi.name = argv[0];
	if ((ret = init_args(argc, argv, &phi)))
		return (throw_error(ret) + clean_all(&phi));
	if ((ret = init_philosophers(&phi)))
		return (throw_error(ret) + clean_all(&phi));
	if ((ret = launch_philosophers(&phi)))
		return (throw_error(ret) + clean_all(&phi));
	clean_all(&phi);
	return (0);
}
