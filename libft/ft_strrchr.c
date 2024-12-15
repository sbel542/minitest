/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:50:16 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/07 15:34:16 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char			*result;
	unsigned char	uc;

	uc = (unsigned char)c;
	result = NULL;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if ((unsigned char)*s == uc)
			result = (char *)s;
		s++;
	}
	if ((unsigned char)*s == uc)
		result = (char *)s;
	return (result);
}

/*int	main(void)
{
        const char str[] = "Hello Wo rld!";
        const char ch = ' ';
        char    *ret;

        ret = ft_strrchr(str, ch);
        printf("%s\n", ret);

        return(0);
}*/
