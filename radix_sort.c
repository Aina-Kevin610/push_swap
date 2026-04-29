/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:08:35 by airandri          #+#    #+#             */
/*   Updated: 2026/03/16 11:12:13 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(t_stack *a)
{
	int	max;
	int	bits;

	max = get_max(a);
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	radix_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	int	bits;
	int	i;
	int	j;
	int	size;

	bits = get_max_bits(*a);
	size = ft_lst_size(*a);
	i = 0;
	j = 0;
	while (i < bits)
	{
		size = ft_lst_size(*a);
		j = 0;
		while (j < size)
		{
			if ((((*a)->index >> i) & 1) == 0)
				pb(a, b, bench);
			else
				ra(a, bench);
			j++;
		}
		while (*b)
			pa(a, b, bench);
		i++;
	}
}
