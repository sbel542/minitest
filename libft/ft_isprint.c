/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:10:00 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 11:37:18 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isprint('a'));
	printf("%d\n", ft_isprint('n'));
	printf("%d\n", ft_isprint('%'));
	printf("%d\n", ft_isprint('t'));
	printf("%d\n", ft_isprint(' '));
	printf("%d\n", ft_isprint('9'));

	return (0);
}*/
