/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 01:07:33 by lmartin           #+#    #+#             */
/*   Updated: 2020/07/17 04:22:08 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_H
# define LOGS_H

int		throw_error(int error);
void	ft_usleep(unsigned int n);
int		logs(struct timeval *st, struct timeval *tv, size_t number, char *msg);

#endif
