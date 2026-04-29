/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunck_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:01:33 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/16 11:21:26 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_chunk(t_stack **a, t_stack **b, t_bench *bench)
{
	int	size;
	int	chunk_size;
	int	start;
	int	end;

	size = ft_lst_size(*a);
	if (size <= 100)
		chunk_size = 20;
	else
		chunk_size = 45;
	start = 0;
	end = chunk_size - 1;
	while (*a)
	{
		if ((*a)->index <= end)
		{
			pb(a, b, bench);
			if ((*b)->index <= start)
				rb(b, bench);
			start++;
			end++;
		}
		else
			ra(a, bench);
	}
}

static void	put_max_top(t_stack **b, t_bench *bench)
{
	int		max;
	int		pos;
	int		size;
	t_stack	*tmp;

	size = ft_lst_size(*b);
	max = get_max(*b);
	pos = 0;
	tmp = *b;
	while (tmp && tmp->index != max)
	{
		tmp = tmp->next;
		pos++;
	}
	if (pos <= size / 2)
	{
		while ((*b)->index != max)
			rb(b, bench);
	}
	else
	{
		while ((*b)->index != max)
			rrb(b, bench);
	}
}

static void	push_b_to_a(t_stack **a, t_stack **b, t_bench *bench)
{
	while (*b)
	{
		put_max_top(b, bench);
		pa(a, b, bench);
	}
}

void	chunk_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	push_chunk(a, b, bench);
	push_b_to_a(a, b, bench);
}
