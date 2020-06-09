/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 00:07:09 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/09 01:50:46 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** function: {fill_msg}
**
** parameters:
** (char *){msg} - msg to add,
** (char **){ptr} - pointer to the char * to fill
**
** return (void)
**
** description:
** Put the {msg} into {ptr}
*/

void	fill_msg(char *msg, char **ptr)
{
	while (msg)
		*(*ptr)++ = *msg++;
}

/*
** function: {fill_nbr}
**
** parameters:
** (size_t){nbr} - number to add,
** (char **){ptr} - pointer to the char * to fill
**
** return (void)
**
** description:
** Convert the number {nbr} into a (char *) and fill it into {ptr}
*/

void	fill_nbr(size_t nbr, char **ptr)
{
	char			c;
	size_t			nnbr;
	long long int	pow;

	if (nbr <= 9 && (c = '0'))
		*(*ptr)++ = c;
	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + '0';
		*(*ptr)++ = c;
	}
}

/*
** function: {ft_strlen}
**
** parameters:
** (const char *){s} - String to count the length
**
** return (size_t): length of the string
**
** description:
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
** function {ft_atos}
** 
** parameters:
** (char *){str} - the string to parse,
** (size_t *){nb} - a pointer to the size_t to fill
**
** return (int): return -1 if str is empty or str didn't finished by a number
**
** description: 
** transform ascii to size_t and put it in {nb}
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
