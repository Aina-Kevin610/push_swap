/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:05:26 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/16 09:39:56 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack **node)
{
	t_stack	*first;
	t_stack	*second;

	first = NULL;
	second = NULL;
	if (!node || !*node || !(*node)->next)
		return ;
	first = *node;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*node = second;
}

void	sa(t_stack **a, t_bench *bench)
{
	if (!a || !*a || !(*a)->next)
		return ;
	swap(a);
	if (bench)
	{
		bench->ops.sa++;
		bench->total++;
	}
	ft_printf("sa\n");
}

void	sb(t_stack **b, t_bench *bench)
{
	if (!b || !*b || !(*b)->next)
		return ;
	swap(b);
	if (bench)
	{
		bench->ops.sb++;
		bench->total++;
	}
	ft_printf("sb\n");
}

void	ss(t_stack **a, t_stack **b, t_bench *bench)
{
	swap(a);
	swap(b);
	if (bench)
	{
		bench->ops.ss++;
		bench->total++;
	}
	ft_printf("ss\n");
}
