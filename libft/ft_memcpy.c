/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:01:28 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/07 15:40:27 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_point;
	unsigned char		*dest_point;

	dest_point = dest;
	src_point = src;
	while (n--)
	{
		*dest_point++ = *src_point++;
	}
	return (dest);
}

/*int   main()
{
        char s[] = "abcdefghijklmnopqrstuvwxyz";
        char d[50];

        char s1[] = "jopjeojo";
        char d1[50];
	
	char s2[] = "abcdefghijklmnopqrstuvwxyz";
        char d2[50];

        ft_memcpy(d, s, 8);
        printf("%s\n", d);

        memcpy(d1, s1, 16);
        printf("%s\n", d1);

	memmove(d2, s2, 16);
        printf("%s\n", d2);
}*/
