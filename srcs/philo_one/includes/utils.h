/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 00:07:39 by lmartin           #+#    #+#             */
/*   Updated: 2020/06/16 19:08:16 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

t_parameters		*copy_parameters(t_parameters *parameters);
void				fill_msg(char *msg, char **ptr);
void				fill_nbr(size_t nbr, char **timestamp);
size_t				ft_strlen(const char *s);
int					ft_atos(char *str, size_t *nb);

#endif
