/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:46:10 by sbelcher          #+#    #+#             */
/*   Updated: 2024/07/23 15:46:14 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

static int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (str[i] != '\0')
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	print_type(char specifier, va_list ap)
{
	int	i;

	i = 0;
	if (specifier == 'c')
		i = ft_putchar(va_arg(ap, int));
	else if (specifier == 's')
		i = ft_putstr(va_arg(ap, char *));
	else if (specifier == 'i')
		i = ft_putnbr(va_arg(ap, int));
	else if (specifier == 'd')
		i = ft_putnbr(va_arg(ap, int));
	else if (specifier == 'u')
		i = ft_putunint(va_arg(ap, unsigned int));
	else if (specifier == 'p')
		i = ft_putpointer(va_arg(ap, void *));
	else if (specifier == 'x')
		i = ft_puthex(va_arg(ap, unsigned int), specifier);
	else if (specifier == 'X')
		i = ft_puthex(va_arg(ap, unsigned int), specifier);
	else
		i += write(1, &specifier, 1);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	argu;
	int		count;

	va_start(argu, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_type(*(++format), argu);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(argu);
	return (count);
}
