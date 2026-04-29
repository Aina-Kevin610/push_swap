/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 07:16:55 by airandri          #+#    #+#             */
/*   Updated: 2026/03/28 17:28:31 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <string.h>

static void	small(t_stack **a, t_stack **b, t_bench *bench, int size)
{
	if (size <= 3)
	{
		bench->strategy = "adaptive";
		bench->complexity = "O(1)";
		sort_three(a, bench);
	}
	else
	{
		bench->strategy = "adaptive";
		bench->complexity = "O(n)";
		handle_min(a, b, bench);
	}
}

static void	large(t_stack **a, t_stack **b, t_bench *bench, float dis)
{
	if (dis < 0.2)
	{
		bench->strategy = "simple";
		bench->complexity = "O(n²)";
		selection_sort(a, b, bench);
	}
	else if (dis < 0.5)
	{
		bench->strategy = "medium";
		bench->complexity = "O(n√n)";
		chunk_sort(a, b, bench);
	}
	else
	{
		bench->strategy = "complex";
		bench->complexity = "O(n log n)";
		radix_sort(a, b, bench);
	}
}

static void	adaptive(t_stack **a, t_stack **b, t_bench *bench)
{
	int		size;
	float	dis;

	size = ft_lst_size(*a);
	dis = disorder(*a);
	bench->disorder = dis;
	if (size <= 5)
		small(a, b, bench, size);
	else
		large(a, b, bench, dis);
}

void	decision(t_stack **a, t_stack **b, char *selector, t_bench *bench)
{
	bench->disorder = disorder(*a);
	if (selector && strcmp(selector, "--simple") == 0)
	{
		selection_sort(a, b, bench);
		bench->strategy = "simple";
		bench->complexity = "O(n²)";
	}
	else if (selector && strcmp(selector, "--medium") == 0)
	{
		chunk_sort(a, b, bench);
		bench->strategy = "medium";
		bench->complexity = "O(n√n)";
	}
	else if (selector && strcmp(selector, "--complex") == 0)
	{
		radix_sort(a, b, bench);
		bench->strategy = "complex";
		bench->complexity = "O(n log n)";
	}
	else if (!selector || strcmp(selector, "--adaptive") == 0)
	{
		adaptive(a, b, bench);
		bench->strategy = "adaptive";
	}
}
