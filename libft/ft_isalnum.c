/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:24:16 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 11:31:55 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isalnum(int argument)
{
	if ((argument >= 'a' && argument <= 'z')
		|| (argument >= 'A' && argument <= 'Z')
		|| (argument >= '0' && argument <= '9'))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isalnum('1'));
	printf("%d\n", ft_isalnum('a'));
	printf("%d\n", ft_isalnum('@'));
	printf("%d\n", ft_isalnum('g'));
	printf("%d\n", ft_isalnum('5'));
	printf("%d\n", ft_isalnum('^'));
	printf("%d\n", ft_isalnum('7'));
	printf("%d\n", ft_isalnum('A'));
	printf("%d\n", ft_isalnum('('));
	printf("%d\n", ft_isalnum('Z'));

	return (0);
}*/
