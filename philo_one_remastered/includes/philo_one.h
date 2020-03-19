#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# include "error.h"
# include "logs.h"

typedef struct		s_parameters
{
	size_t			number_of_philosopher;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_time_each_philosophers_must_eat;
}					t_parameters;

typedef struct		s_philosopher
{
	size_t			number;
	t_parameters	*parameters;
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
	struct timeval	*time_last_meal;
	void			*next;
}					t_philosopher;

typedef struct		s_philo_one
{
	char			*name;
	t_parameters	*parameters;
	s_philosopher	*philosophers;
}					t_philo_one;

#endif
