/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 21:41:58 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 02:07:53 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORKS_H
# define FORKS_H

typedef struct		s_lstforks
{
	pthread_mutex_t	*lock;
	void			*next;
}					t_lstforks;

int					init_locks(t_lstforks **forks);
t_lstforks			*new_fork();
int					forks_add_back(t_lstforks **forks);

#endif
