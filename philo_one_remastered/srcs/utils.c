#include "philo_one.h"

/*
** Calculate the len of string s
*/

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s && ++i)
		s++;
	return (i);
}

/*
** ascii to size_t
*/

int		ft_atos(char *str, size_t *nb)
{
	if (*str == '\0')
		return (-1);
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (0);
}
