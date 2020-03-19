#include "philo_one.h"

int		init_args(int argc, char *argv, t_philo_one *phi)
{
	if (argc < 5 || argc > 6)
		return (TOO_MANY_ARGS);	
	return (0);
}

int		main(int argc, char *argv)
{
	int				ret;
	t_philo_one		phi;

	if ((ret = init_args(argc, argv, &phi))
		return ();	
}
