/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:55:30 by sbelcher          #+#    #+#             */
/*   Updated: 2024/07/23 15:55:33 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	ft_printptr(unsigned long long address)
{
	if (address >= 16)
	{
		ft_printptr(address / 16);
		ft_printptr(address % 16);
	}
	else
	{
		if (address <= 9)
			ft_putchar(address + '0');
		else
			ft_putchar(address - 10 + 'a');
	}
}

static int	ft_ptrlen(unsigned long long address)
{
	int	count;

	count = 0;
	while (address != 0)
	{
		count++;
		address /= 16;
	}
	return (count);
}

int	ft_putpointer(void *ptr)
{
	unsigned long long	address;
	int					length;

	length = 0;
	if (ptr == 0)
		return (length += ft_printf("(nil)"));
	else
	{
		length = 2;
		write(1, "0x", 2);
		address = (unsigned long long)ptr;
		length += ft_ptrlen(address);
		ft_printptr(address);
		return (length);
	}
}
