/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:27:13 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/08 16:11:03 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
	{
		result[s1_len + j] = s2[j];
		j++;
	}
	result[s1_len + s2_len] = '\0';
	return (result);
}

/*int	main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = "Hello,";
	s2 = " World!";
	s3 = ft_strjoin(s1, s2);
	printf("%s\n", s3);
	return (0);
}*/
