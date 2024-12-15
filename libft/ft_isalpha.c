/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:56:17 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 11:29:28 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("%d\n", ft_isalpha('0'));
	printf("%d\n", ft_isalpha('1'));
	printf("%d\n", ft_isalpha('q'));
	printf("%d\n", ft_isalpha('$'));
	printf("%d\n", ft_isalpha('&'));

	return (0);
}*/
