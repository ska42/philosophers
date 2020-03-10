/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:03:03 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 02:06:51 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** fill a nbr on timestamp, if it's digit add 0 before
*/

void	fill_nbr(size_t nbr, char **timestamp)
{
	char			c;
	size_t			nnbr;
	long long int	pow;

	if (nbr <= 9 && (c = '0'))
		*(*timestamp)++ = c;
	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + '0';
		*(*timestamp)++ = c;
	}
}

/*
** Fill the date with given seconds of the actual day
*/

void	get_time(int seconds, t_date *date)
{
	date->hour = seconds / (60 * 60);
	date->minute = (seconds / 60) - (date->hour * 60);
	date->second = seconds - (int)(date->minute * 60 + date->hour * 60 * 60);
}

/*
** Fill the date with given days since 1970
** (We add 1 at days because there isn't a 0 day in a month)
*/

void	get_date(int days, t_date *date)
{
	int days_in_year;
	int days_in_month;
	int year;
	int	month;

	year = 1970;
	days_in_year = 365;
	while (days - days_in_year >= 0 && year++ && ((days -= days_in_year) >= 0))
		days_in_year = ((!(year % 4) && (year % 100)) || !(year % 400)) ?
366 : 365;
	days_in_month = 31;
	month = 1;
	while (month < 13 && (days - days_in_month) >= 0)
	{
		days -= days_in_month;
		if (++month != 2)
			days_in_month = ((!(month % 2) && month < 7) ||
((month % 2 && month > 6))) ? 31 : 30;
		else
			days_in_month = ((!(year % 4) && (year % 100)) || !(year % 400)) ?
29 : 28;
	}
	date->year = year;
	date->month = month;
	date->day = days + 1;
}

/*
** Print the timestamp with gettimeofday
*/

int		fill_timestamp(char **timestamp)
{
	struct timeval	tv;
	t_date			date;

	gettimeofday(&tv, NULL);
	get_date(tv.tv_sec / (60 * 60 * 24), &date);
	get_time(tv.tv_sec - ((int)(tv.tv_sec / (60 * 60 * 24)) * 60 * 60 * 24),
&date);
	date.millisecond = tv.tv_usec / 1000;
	fill_nbr(date.year, timestamp);
	*(*timestamp)++ = '-';
	fill_nbr(date.month, timestamp);
	*(*timestamp)++ = '-';
	fill_nbr(date.day, timestamp);
	*(*timestamp)++ = ' ';
	fill_nbr(date.hour, timestamp);
	*(*timestamp)++ = ':';
	fill_nbr(date.minute, timestamp);
	*(*timestamp)++ = ':';
	fill_nbr(date.second, timestamp);
	*(*timestamp)++ = '.';
	if (date.millisecond < 100)
		*(*timestamp)++ = '0';
	fill_nbr(date.millisecond, timestamp);
	return (0);
}

/*
** Print on stdin the status of a philosopher with the number of the philosopher
** like:
** timestamp_in_ms number msg
*/

int		logs(size_t number, char *msg)
{
	int		ret;
	char	*ptr;
	char	*log;
	size_t	size_nb;
	size_t	nnumber;

	nnumber = number * 10;
	size_nb = (nnumber <= 9) ? (28 + ft_strlen(msg)) : (27 + ft_strlen(msg));
	while (nnumber /= 10)
		size_nb++;
	if (!(log = malloc(sizeof(char) * (size_nb))))
		return (ERR_MALLOC);
	ptr = log;
	if ((ret = fill_timestamp(&ptr)) < 0)
		return (ret);
	*ptr++ = ' ';
	fill_nbr(number, &ptr);
	*ptr++ = ' ';
	while (*msg)
		*ptr++ = *msg++;
	*ptr = '\n';
	write(STDIN_FILENO, log, size_nb);
	free(log);
	return (0);
}
