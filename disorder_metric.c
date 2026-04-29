/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder_metric.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 04:36:24 by airandri          #+#    #+#             */
/*   Updated: 2026/03/14 23:38:00 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	disorder(t_stack *a)
{
	t_stack		*tmp;
	t_stack		*tmp1;
	int			mistakes;
	int			size;

	mistakes = 0;
	size = 0;
	tmp = a;
	while (tmp && tmp->next)
	{
		tmp1 = tmp->next;
		while (tmp1)
		{
			size++;
			if (tmp->index > tmp1->index)
				mistakes++;
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
	if (size == 0)
		return (0.0f);
	return ((float)mistakes / size);
}
