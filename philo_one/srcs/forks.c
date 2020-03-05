/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 21:22:55 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/20 21:47:35 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers"

/*
** Create a new t_lstforks with her fork
*/

t_lstforks	*new_fork()
{
	t_lstforks	*fork;

	if (!(fork = malloc(sizeof(t_lstforks))))
		return (NULL);
	if (!(fork->fork = malloc(sizeof(pthread_mutex_t))))
	{
		free(fork);
		return (NULL);
	}
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

}
