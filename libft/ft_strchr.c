/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:04:35 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 13:03:27 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if ((unsigned char)*s == uc)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)*s == uc)
		return ((char *)s);
	return (NULL);
}

/*int	main(void)
{
	const char str[] = "Hello.World!";
	const char ch = '.';
	char	*ret;

	ret = ft_strchr(str, ch);
	printf("%s\n", ret);

	return(0);
}*/
