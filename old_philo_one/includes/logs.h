/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:08:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 04:23:35 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_H
# define LOGS_H

# define MSG_FORK "has taken a fork"
# define MSG_EATING "is eating"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_DEATH "died"

typedef struct	s_date
{
	int			year;
	int			month;
	int			day;
	int			hour;
	int			minute;
	int			second;
	int			millisecond;
}				t_date;

int				logs(struct timeval *tv, size_t number, char *msg);

#endif
