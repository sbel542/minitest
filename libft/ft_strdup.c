/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:54:48 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/08 16:07:15 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*str2;

	str2 = malloc(ft_strlen(s) + 1);
	ft_strcpy(str2, s);
	return (str2);
}

/*int	main()
{
	char	*str1;
	char	*str2;

	str1 = "Hello, World!";
	str2 = ft_strdup(str1);
	printf("%s\n", str2);

	return (0);
}*/
