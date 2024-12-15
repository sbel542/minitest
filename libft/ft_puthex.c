/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:47:22 by sbelcher          #+#    #+#             */
/*   Updated: 2024/07/23 15:47:27 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_hexlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (len + 1);
	else
	{
		while (n > 0)
		{
			len++;
			n /= 16;
		}
		return (len);
	}
}

static void	ft_printhex(unsigned int n, const char specifier)
{
	if (n >= 16)
	{
		ft_printhex(n / 16, specifier);
		ft_printhex(n % 16, specifier);
	}
	else
	{
		if (specifier == 'x')
		{
			if (n <= 9)
				ft_putchar(n + '0');
			else
				ft_putchar(n - 10 + 'a');
		}
		if (specifier == 'X')
		{
			if (n <= 9)
				ft_putchar(n + '0');
			else
				ft_putchar(n - 10 + 'A');
		}
	}
}

int	ft_puthex(unsigned int n, const char specifier)
{
	if (n == 0)
		write(1, "0", 1);
	else
		ft_printhex(n, specifier);
	return (ft_hexlen(n));
}
