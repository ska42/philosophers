#include "philo_one.h"

/*
** init all philosophers
*/

int		init_philosophers(t_philo_one *phi)
{
	int				i;
	t_philosopher	*ptr;
	pthread_mutex_t	*right_fork;
	
	if (!(phi->philosophers = malloc(sizeof(t_philosopher))))
		return (ERROR_MALLOC);
	if (!(right_fork = malloc(sizeof(pthread_mutex_t))))
		return (ERROR_MALLOC);
	ptr = phi->philosophers;
	i = 0;
	while (i < phi->parameters->number_of_philosopher && (!i || (ptr = ptr->next)))
	{
		ptr->number = ++i;
		ptr->parameters = phi->parameters;
		if (!(ptr->thread = malloc(sizeof(pthread_t))))
			return (ERROR_MALLOC);
		ptr->left_fork = right_fork;
		ptr->right_fork = (i == phi->parameters->number_of_philosopher) ?
phi->philosophers->left_fork : malloc(sizeof(pthread_mutex_t));
		if (!(right_fork = ptr->right_fork))
			return (ERROR_MALLOC);
		if (i != phi->parameters->number_of_philosopher &&
!(ptr->next = malloc(sizeof(t_philosopher))))
			return (ERROR_MALLOC);	
	}
	return ((ptr->next = NULL));
}

/*
** init all arguments
*/

int		init_args(int argc, char *argv, t_philo_one *phi)
{
	if (!(phi->parameters = malloc(sizeof(t_parameters))))
		return (ERROR_MALLOC);
	if (argc < 5 || argc > 6)
		return (TOO_MANY_ARGS);
	if (ft_atos(argv[1], &phi->parameters->number_of_philosopher))
		return (WRONG_ARG);
	if (phi->parameters->number_of_philosopher < 2)
		return (WRONG_ARG);
	if (ft_atos(argv[2], &phi->parameters->time_to_die))
		return (WRONG_ARG);
	if (ft_atos(argv[3], &phi->parameters->time_to_eat))
		return (WRONG_ARG);
	if (ft_atos(argv[4], &phi->parameters->time_to_sleep))
		return (WRONG_ARG);
	if (argc == 6 && ft_atos(argv[5], 
&phi->parameters->number_of_time_each_philosophers_must_eat))
		return (WRONG_ARG);
	else if (argc == 5)
		phi->parameters->number_of_time_each_philosophers_must_eat = -1;
	return (0);
}

int		main(int argc, char *argv)
{
	int				ret;
	t_philo_one		phi;

	phi.name = argv[0];
	if ((ret = init_args(argc, argv, &phi))
		return (throw_error(phi.name, ret));
	if ((ret = init_philosophers(&phi)))
		return (throw_error(phi.name, ret));
}
