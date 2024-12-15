/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:28:27 by sbelcher          #+#    #+#             */
/*   Updated: 2023/11/24 13:30:49 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

static int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	x;

	x = 0;
	while ((s1[x] != '\0' || s2[x] != '\0') && x < n)
	{
		if (s1[x] > s2[x])
		{
			return (1);
		}
		else if (s1[x] < s2[x])
		{
			return (-1);
		}
		x++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_length;

	little_length = ft_strlen(little);
	if (little_length == 0)
		return ((char *)big);
	while (len >= little_length && *big)
	{
		if (ft_strncmp(big, little, little_length) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

/*int	main()
{
	const char *string1 = "hello the world";
	const char *string2 = "the";

	printf("%s\n", ft_strnstr(string1, string2, 9));
}*/
