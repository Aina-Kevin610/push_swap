/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:21:38 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/16 15:14:33 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	benchmark(t_bench *c)
{
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putfloat_fd(c->disorder * 100, 2);
	ft_putchar_fd('%', 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putstr_fd(c->strategy, 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(c->complexity, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(c->total, 2);
	ft_putchar_fd('\n', 2);
}

void	benchmark_ops(t_operations *d)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(d->sa, 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_fd(d->sb, 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_fd(d->ss, 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_fd(d->pa, 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_fd(d->pb, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] ra: ", 2);
	ft_putnbr_fd(d->ra, 2);
	ft_putstr_fd(" rb: ", 2);
	ft_putnbr_fd(d->rb, 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_fd(d->rra, 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_fd(d->rrb, 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_fd(d->rrr, 2);
	ft_putchar_fd('\n', 2);
}
