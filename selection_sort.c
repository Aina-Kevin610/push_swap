/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:00:55 by airandri          #+#    #+#             */
/*   Updated: 2026/03/16 11:17:52 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	selection_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	while ((*a)->next)
	{
		put_min_top(a, bench);
		pb(a, b, bench);
	}
	while (*b)
	{
		pa(a, b, bench);
	}
}
