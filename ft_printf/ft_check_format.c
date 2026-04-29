/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:50:12 by rivandri          #+#    #+#             */
/*   Updated: 2026/02/28 12:26:51 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_format(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (c == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		count = ft_putptr(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		count = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count = ft_putunsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		count = ft_puthex(va_arg(args, unsigned int), 0);
	else if (c == 'X')
		count = ft_puthex(va_arg(args, unsigned int), 1);
	else if (c == '%')
		count = ft_putchar('%');
	else
		count = ft_putchar(c);
	return (count);
}
