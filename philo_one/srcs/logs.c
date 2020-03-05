/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:07:53 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/05 23:51:37 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

// TODO: NOT PRINTF -> WRITE (need putnbr)

/*
** Return the month of the given days and year
*/

int		get_month(int days, int year)
{
	int days_in_month;
	int	month;
	
	days_in_month = 31;
	month = 0;
	while (++month < 13 && (days - days_in_month) >= 0)
	{
		days = days - days_in_month;
		if (month != 2)
			days_in_month = ((!(month % 2) && month < 7) || ((month % 2 && month > 6))) ? 31 : 30;
		else
			days_in_month = ((!(year % 4) && (year % 100)) ||(year % 400))
? 29 : 28;
	}
	return (month);
}

/*
** Print the timestamp with gettimeofday
*/

int		print_timestamp()
{
	struct	timeval tv;
	int		year;
	int		month;

	gettimeofday(&tv, NULL);
	year = tv.tv_sec / (60 * 60 * 24 * 365.25);
	month = get_month((tv.tv_sec / (60 * 60 * 24)) - (year * 365.25),
year + 1970);
	printf("%d-%d", year + 1970, month);
	return (0);	
}

/*
** Print on stdin the status of a philosopher with the number of the philosopher
** like:
** timestamp_in_ms number msg
*/

int		logs(size_t number, char *msg)
{
	int ret;

	if ((ret = print_timestamp()) < 0)
		return (ret);
	printf(" %ld %s\n", number, msg);
	return (0);
}
