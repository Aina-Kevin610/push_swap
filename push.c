/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:02:37 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/16 09:48:25 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack **src, t_stack **dest)
{
	t_stack	*tmp;

	if (!src || !*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dest;
	*dest = tmp;
}

void	pa(t_stack **a, t_stack **b, t_bench *bench)
{
	if (!b || !*b)
		return ;
	push(b, a);
	if (bench)
	{
		bench->ops.pa++;
		bench->total++;
	}
	ft_printf("pa\n");
}

void	pb(t_stack **a, t_stack **b, t_bench *bench)
{
	if (!a || !*a)
		return ;
	push(a, b);
	if (bench)
	{
		bench->ops.pb++;
		bench->total++;
	}
	ft_printf("pb\n");
}
