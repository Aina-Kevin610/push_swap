/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_index_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:29:02 by airandri          #+#    #+#             */
/*   Updated: 2026/03/08 06:39:46 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *a)
{
	int		i;
	int		result;
	t_stack	*tmp;

	tmp = a;
	i = 0;
	result = 1;
	while (tmp && tmp->next)
	{
		if (tmp->index > tmp->next->index)
		{
			result = 0;
			return (result);
		}
		tmp = tmp->next;
		i++;
	}
	return (result);
}
