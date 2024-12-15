/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:57:17 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/08 16:04:20 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	totalsize;
	char	*ptr1;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	totalsize = nmemb * size;
	ptr1 = (char *)malloc(totalsize);
	if (ptr1 != NULL)
		ft_memset(ptr1, 0, totalsize);
	return (ptr1);
}

/*int	main() 
{
	size_t	num_elements = 5;
	size_t	element_size = sizeof(int);
	int	*arr = (int*)ft_calloc(num_elements, element_size);
	size_t	i = 0;

 	while (i < num_elements) 
	{
 		arr[i] = i + 1;
 		++i;
	}

	printf("Array elements: ");
 	i = 0;
	while (i < num_elements)
	{
 		printf("%d ", arr[i]);
 		++i;
 	}
	free(arr);
	return 0;
}*/
