/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:52:04 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 12:05:09 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n-- > 0)
	{
		*p++ = '\0';
	}
}

/*int	main()
{
	char	*s1;

	s1 = "Hello, World!";
	ft_bzero(s1, 4);
	printf("%s\n", s1);

	return (0);
}*/
