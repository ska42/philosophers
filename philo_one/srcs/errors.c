/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 23:44:34 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/05 03:25:43 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Throw a error by calling write_msg_error
*/

int		throw_error(char *name, int nb_error)
{
	if (nb_error == ERR_MALLOC)
		nb_error = write_msg_error(name, MSG_ERR_MALLOC);
	else if (nb_error == ERR_WRITE)
		nb_error = write_msg_error(name, MSG_ERR_WRITE);
	else if (nb_error == ERR_NB_ARGS)
		nb_error = write_msg_error(name, MSG_ERR_NB_ARGS);
	else if (nb_error == ERR_WRONG_ARG)
		nb_error = write_msg_error(name, MSG_ERR_WRONG_ARG);
	else if (nb_error == ERR_MUTEX_INIT)
		nb_error = write_msg_error(name, MSG_ERR_MUTEX_INIT);
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
