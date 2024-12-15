/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:48:03 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/08 16:12:56 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_inset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_startset(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (ft_inset(s1[start], set))
		start++;
	return (start);
}

static int	ft_endset(int end, int start, char const *s1, char const *set)
{
	while (end > start && ft_inset(s1[end], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
	size_t	i;
	char	*newstr;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	start = ft_startset(s1, set);
	end = ft_endset(len -1, start, s1, set);
	len = end - start + 1;
	newstr = (char *)malloc(len + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = s1[start + i];
		i++;
	}
	newstr[len] = '\0';
	return (newstr);
}

/*int	main()
{
	const char	*s1 = "nbnbnbnnbnnnnb    nbnbhello worldnb b n b n b n";
	const char	*set = " bn";

	char	*s2 = ft_strtrim(s1, set);
	printf("%s\n", s2);
	free(s2);
	return (0);
}*/
