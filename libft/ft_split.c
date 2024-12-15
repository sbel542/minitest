/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:00:06 by sbelcher          #+#    #+#             */
/*   Updated: 2023/12/08 12:44:34 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	ft_count(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (len < n && s[len] != '\0')
		len++;
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

static void	ft_free_array(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(result[i++]);
	free(result);
}

static char	**ft_populate(char const *s, char c, char **result)
{
	const char	*start;
	int			i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			result[i] = ft_strndup(start, s - start);
			if (!result[i])
			{
				ft_free_array(result, i);
				return (NULL);
			}
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = ft_count(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_populate(s, c, result);
	if (!result)
		return (NULL);
	return (result);
}

/*void	free_split_result(char **result)
{
    for (int i = 0; result[i] != NULL; i++)
    {
        free(result[i]);
    }
    free(result);
}

int	main(void)
{
 
    char const *test_string = "Hello,World,This,Is,A,Test";

    char delimiter = ',';

    char **result = ft_split(test_string, delimiter);

    if (result != NULL)
    {
        for (int i = 0; result[i] != NULL; i++)
        {
            printf("%s\n", result[i]);
        }

        free_split_result(result);
    }
    return 0;
}*/
