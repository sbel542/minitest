/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:33:16 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/08 15:59:33 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	copy_len;

	src_len = ft_strlen(src);
	copy_len = size - 1;
	if (size == 0)
		return (src_len);
	if (src_len < copy_len)
		copy_len = src_len;
	ft_memcpy(dst, src, copy_len);
	dst[copy_len] = '\0';
	return (src_len);
}

/*int	main()
{
const char	src[16] = "PPPPPPPhdtsgyeft";
char	dest[50];

ft_strlcpy(dest, src, 9);
printf("%s\n", dest);
	return(0);
}*/
