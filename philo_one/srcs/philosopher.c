/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:36:42 by lmartin           #+#    #+#             */
/*   Updated: 2020/03/10 05:12:28 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Create a new philosopher and return it
*/

t_philosopher	*new_philosopher(size_t number, t_lstforks *left_fork,
t_lstforks *right_fork, t_parameters *parameters)
{
	t_philosopher	*philosopher;

	if (!(philosopher = malloc(sizeof(t_philosopher))))
		return (NULL);
	philosopher->number = number;
	philosopher->left_fork = left_fork;
	philosopher->right_fork = right_fork;
	philosopher->parameters = parameters;
	philosopher->last_meal = NULL;
	philosopher->next = NULL;
	return (philosopher);
}
