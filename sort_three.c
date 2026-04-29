/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:37:32 by airandri          #+#    #+#             */
/*   Updated: 2026/03/16 11:13:33 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_max(t_stack *a)
{
	int		max;
	t_stack	*tmp;

	tmp = a;
	max = tmp->index;
	while (tmp)
	{
		if (tmp->index > max)
			max = tmp->index;
		tmp = tmp->next;
	}
	return (max);
}

void	sort_three(t_stack **a, t_bench *bench)
{
	int		max;
	t_stack	*tmp;

	tmp = *a;
	max = get_max(tmp);
	if (tmp->index == max)
	{
		ra(a, bench);
		if (!is_sorted(*a))
			sa(a, bench);
	}
	else if (tmp->next->index == max)
	{
		rra(a, bench);
		if (!is_sorted(*a))
			sa(a, bench);
	}
	else
	{
		if (!is_sorted(*a))
			sa (a, bench);
	}
}
