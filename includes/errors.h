/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 23:47:06 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/20 13:46:26 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_MALLOC -3
# define ERR_WRITE -4
# define ERR_NB_ARGS -10
# define ERR_WRONG_ARG -11

# define MSG_ERR_NB_ARGS "Wrong number of arguments"
# define MSG_ERR_WRONG_ARG "Wrong argument"

int		throw_error(char *name, int nb_error);
int		write_msg_error(char *prg_name, char *msg);

#endif
