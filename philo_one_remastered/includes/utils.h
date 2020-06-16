/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 00:07:39 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/16 02:15:37 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct		s_parameters
{
	int				number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_time_each_philosophers_must_eat;
	struct timeval	*time_start;
}					t_parameters;

t_parameters		*copy_parameters(t_parameters *parameters);
void				fill_msg(char *msg, char **ptr);
void				fill_nbr(size_t nbr, char **timestamp);
size_t				ft_strlen(const char *s);
int					ft_atos(char *str, size_t *nb);

#endif
