/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 23:47:06 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 02:07:34 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_MALLOC -3
# define ERR_WRITE -4
# define ERR_NB_ARGS -10
# define ERR_WRONG_ARG -11
# define ERR_MUTEX_INIT -12
# define ERR_PTHREAD_CREATE -13

# define MSG_ERR_MALLOC "malloc error"
# define MSG_ERR_WRITE "write error"
# define MSG_ERR_NB_ARGS "Wrong number of arguments"
# define MSG_ERR_WRONG_ARG "Wrong argument"
# define MSG_ERR_MUTEX_INIT "pthread_mutex_init failed"
# define MSG_ERR_PTHREAD_CREATE "pthread_create failed"

int		throw_error(char *name, int nb_error);
int		write_msg_error(char *prg_name, char *msg);

#endif
