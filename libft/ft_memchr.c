/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:55:38 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 13:18:07 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str_point;
	unsigned char		a;

	str_point = s;
	a = (unsigned char)c;
	if (str_point == NULL)
		return (NULL);
	while (n != 0)
	{
		if (*str_point == a)
			return ((void *)str_point);
		str_point++;
		n--;
	}
	return (NULL);
}

/*int	main(void)
{
	const char str[] = "Hello.World!";
	int ch = '.';
	char	*ret;

	ret = ft_memchr(str, ch, 6);
	printf("%s\n", ret);

	return(0);
}*/
