/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 21:22:55 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/05 21:54:49 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Init locks (pthread_mutex) on every forks
*/

int			init_locks(t_lstforks **forks)
{
	t_lstforks	*ptr;

	ptr = *forks;	
	while (ptr->next)
	{
		if (pthread_mutex_init(ptr->lock, NULL))
			return (ERR_MUTEX_INIT);
		ptr = ptr->next;
	}
	return (0);
}

/*
** Create a new t_lstforks with her fork
*/

t_lstforks	*new_fork()
{
	t_lstforks	*fork;

	if (!(fork = malloc(sizeof(t_lstforks))))
		return (NULL);
	if (!(fork->lock = malloc(sizeof(pthread_mutex_t))))
	{
		free(fork);
		return (NULL);
	}
	fork->next = NULL;
	return (fork);
}

/*
** Add a t_lstforks at the end of forks
*/

int		forks_add_back(t_lstforks **forks)
{
	t_lstforks	*ptr;

	if (!(*forks))
	{
		if (!((*forks) = new_fork()))
			return (ERR_MALLOC);
		return (0);
	}
	ptr = *forks;
	while (ptr->next)
		ptr = ptr->next;
	if (!(ptr->next = new_fork()))
		return (ERR_MALLOC);
	return (0);
}
