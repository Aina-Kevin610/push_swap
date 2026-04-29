/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:13:58 by rivandri          #+#    #+#             */
/*   Updated: 2026/02/28 13:02:32 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int n)
{
	int		count;

	count = 0;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n < 10)
	{
		ft_putchar(n + '0');
		count++;
	}
	if (n >= 10)
	{
		count = count + ft_putunsigned(n / 10);
		count = count + ft_putunsigned(n % 10);
	}
	return (count);
}
