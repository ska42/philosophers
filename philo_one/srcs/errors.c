/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 23:44:34 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/20 13:52:40 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Throw a error by calling write_msg_error
*/

int		throw_error(char *name, int nb_error)
{
	if (nb_error == ERR_NB_ARGS)
		if (write_msg_error(name, MSG_ERR_NB_ARGS) < 0)
			return (ERR_WRITE);
	if (nb_error == ERR_WRONG_ARG)
		if (write_msg_error(name, MSG_ERR_WRONG_ARG) < 0)
			return (ERR_WRITE);
	return (nb_error);
}

/*
** Write a message error
*/

int		write_msg_error(char *prg_name, char *msg)
{
	if (write(STDERR_FILENO, prg_name, ft_strlen(prg_name)) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, ": ", 2) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return (ERR_WRITE);
	return (0);
}
