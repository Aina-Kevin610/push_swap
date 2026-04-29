/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:51:24 by rivandri          #+#    #+#             */
/*   Updated: 2026/02/28 11:37:34 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex_long(unsigned long n)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count = count + ft_puthex_long(n / 16);
	count = count + ft_putchar(base[n % 16]);
	return (count);
}

int	ft_putptr(void *ptr)
{
	int				count;
	unsigned long	n;

	if (!ptr)
	{
		count = ft_putstr("(nil)");
		return (count);
	}
	count = 0;
	n = (unsigned long)ptr;
	count = count + ft_putstr("0x");
	count = count + ft_puthex_long(n);
	return (count);
}
