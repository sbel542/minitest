/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:43:32 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 11:30:51 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isdigit('1'));
	printf("%d\n", ft_isdigit('a'));
	printf("%d\n", ft_isdigit('3'));
	printf("%d\n", ft_isdigit('g'));
	printf("%d\n", ft_isdigit('5'));
	printf("%d\n", ft_isdigit('%'));
	printf("%d\n", ft_isdigit('7'));
	printf("%d\n", ft_isdigit('@'));
	printf("%d\n", ft_isdigit('9'));
	printf("%d\n", ft_isdigit(';'));

	return (0);
}*/
