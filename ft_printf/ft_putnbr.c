/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 09:47:22 by rivandri          #+#    #+#             */
/*   Updated: 2026/02/28 13:02:23 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		count;
	long	nb;

	count = 0;
	nb = (long)n;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
		count++;
	}
	if (nb < 10)
		count = count + ft_putchar(nb + '0');
	if (nb >= 10)
	{
		count = count + ft_putnbr(nb / 10);
		count = count + ft_putnbr(nb % 10);
	}
	return (count);
}
