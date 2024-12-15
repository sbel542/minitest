/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:58:45 by sbelcher          #+#    #+#             */
/*   Updated: 2024/07/23 15:58:48 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

char	*ft_seperate_line(char *left_over)
{
	int		i;
	char	*line;

	i = 0;
	if (!left_over[i])
		return (NULL);
	while (left_over[i] && left_over[i] != '\n')
		i++;
	line = (char *)ft_calloc((sizeof(char)), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (left_over[i] && left_over[i] != '\n')
	{
		line[i] = left_over[i];
		i++;
	}
	if (left_over[i] == '\n')
	{
		line[i] = left_over[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_free_left_over(char *left_over)
{
	char			*remaining;
	size_t			i;
	size_t			j;

	i = 0;
	while (left_over[i] && left_over[i] != '\n')
		i++;
	if (!left_over[i])
	{
		free(left_over);
		return (NULL);
	}
	remaining = (char *)ft_calloc((ft_strlen(left_over) - i + 1), sizeof(char));
	if (!remaining)
		return (NULL);
	i++;
	j = 0;
	while (left_over[i])
		remaining[j++] = left_over[i++];
	remaining[j] = '\0';
	free(left_over);
	return (remaining);
}
