/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:57:19 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 11:34:21 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isascii(' '));
	printf("%d\n", ft_isascii('('));
	printf("%d\n", ft_isascii('4'));
	printf("%d\n", ft_isascii('7'));
	printf("%d\n", ft_isascii('%'));
	printf("%d\n", ft_isascii('`'));
	printf("%d\n", ft_isascii(':'));
	printf("%d\n", ft_isascii('p'));
	printf("%d\n", ft_isascii('q'));

	return (0);
}*/
