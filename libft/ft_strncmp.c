/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:47:53 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/08 15:24:27 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n && s1[x]
		&& s2[x] && s1[x] == s2[x])
		x++;
	if (x == n)
		return (0);
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

/*int	main()
{
	printf("%d\n", ft_strncmp("jjj", "jjtt", 3));
	printf("%d\n", strncmp("jjj", "jjtt", 3));
	return (0);
}*/
