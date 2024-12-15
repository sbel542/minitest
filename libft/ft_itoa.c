/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:26:24 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/09 11:01:18 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int	ft_sign(int n)
{
	int	sign;

	if (n < 0)
		sign = 1;
	else
		sign = 0;
	return (sign);
}

static int	ft_nlen(int n)
{
	int	ndigits;
	int	sign;
	int	ncpy;

	ncpy = n;
	sign = ft_sign(ncpy);
	if (sign == 1)
		ncpy = -n;
	ndigits = 0;
	while (ncpy > 0)
	{
		ncpy /= 10;
		ndigits++;
	}
	return (ndigits + sign + 1);
}

static char	*regular(int n)
{
	char	*str;
	int		i;
	int		slen;
	int		sign;

	sign = ft_sign(n);
	slen = ft_nlen(n);
	str = (char *)malloc(ft_nlen(n));
	i = ft_nlen(n) - 2;
	if (str == NULL)
		return (NULL);
	if (sign == 1)
		n = -n;
	while (i >= sign)
	{
		str[i--] = '0' + (n % 10);
		n /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	str[slen - 1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	if (n == INT_MIN)
	{
		n++;
		str = regular(n);
		str[10] = '8';
		return (str);
	}
	if (n == 0)
	{
		str = (char *)malloc(2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n != 0)
	{
		str = regular(n);
		return (str);
	}
	return (NULL);
}

/*int	main(void)
{
	char	*test;

	test = ft_itoa(INT_MIN);
	printf("%s", test);
	free(test);
	return (0);
}*/
