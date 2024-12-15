/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:20:37 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/07 15:39:41 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				x;
	const unsigned char	*str1_point;
	const unsigned char	*str2_point;

	str1_point = s1;
	str2_point = s2;
	x = 0;
	while (x < n)
	{
		if (str1_point[x] != str2_point[x])
		{
			return (str1_point[x] - str2_point[x]);
		}
		x++;
	}
	return (0);
}

/*int     main()
{
	char	f[] = {0, 0, 127, 0};
	char	y[] = {0, 0, 42, 0};

	int	f1[] = {0, 0, 127, 0};
        int	y1[] = {0, 0, 42, 0};

        printf("%d\n", ft_memcmp(f, y, 3));
        printf("%d\n", memcmp(f1, y1, 3));
        return (0);
}*/
