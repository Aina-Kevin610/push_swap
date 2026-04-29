/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 06:01:52 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/16 11:16:46 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_index(t_stack *a)
{
	t_stack	*temp;
	int		min_index;
	int		min_pos;
	int		pos;

	temp = a;
	min_index = temp->index;
	min_pos = 0;
	pos = 0;
	while (temp)
	{
		if (min_index > temp->index)
		{
			min_index = temp->index;
			min_pos = pos;
		}
		pos++;
		temp = temp->next;
	}
	return (min_pos);
}

void	put_min_top(t_stack **a, t_bench *bench)
{
	int	min_index;
	int	size;
	int	reverse;

	min_index = find_min_index(*a);
	size = ft_lst_size(*a);
	if (min_index < (size / 2))
	{
		while (min_index > 0)
		{
			ra(a, bench);
			min_index--;
		}
		return ;
	}
	reverse = size - min_index;
	while (reverse > 0)
	{
		rra(a, bench);
		reverse--;
	}
}

void	handle_min(t_stack	**a, t_stack **b, t_bench *bench)
{
	int	index;
	int	size;

	size = ft_lst_size(*a);
	index = (size - 1) / 2;
	while (index > 0)
	{
		put_min_top(a, bench);
		if (is_sorted(*a) && ft_lst_size(*a) == size)
			return ;
		pb(a, b, bench);
		index--;
	}
	sort_three(a, bench);
	if (*b && (*b)->next)
	{
		if (((*b)->value) < ((*b)->next->value))
			sb(b, bench);
	}
	index = (size - 1) / 2;
	while (index > 0)
	{
		pa(a, b, bench);
		index--;
	}
}
