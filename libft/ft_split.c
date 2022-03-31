/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:21:29 by jgoldste          #+#    #+#             */
/*   Updated: 2022/02/02 01:32:45 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_count(char const *str, char delim_c)
{
	size_t	word_count;
	size_t	flag;

	word_count = 0;
	flag = 0;
	while (*str != '\0')
	{
		if (*str == delim_c)
			flag = 0;
		else
		{
			if (flag == 0)
				word_count++;
			flag = 1;
		}
		str++;
	}
	return (word_count);
}

size_t	ft_word_len(char const *word, char delim_w)
{
	size_t	count;

	count = 0;
	while (*word != '\0' && *word != delim_w)
	{
		count++;
		word++;
	}
	return (count);
}

void	*ft_free(char **array, size_t j)
{
	while (j >= 0)
	{
		free(array[j - 1]);
		j--;
	}
	free(array);
	return (NULL);
}

static char	**ft_array(char const *s, char c, char **array)
{
	size_t	i;
	size_t	j;
	size_t	word_len;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			word_len = ft_word_len((char *)(s + i), c);
			array[j] = ft_substr(&s[i], 0, word_len);
			if (array[j] == NULL)
				return (ft_free(array, j));
			i += (word_len - 1);
			j++;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (ft_word_count((char *)s, c) + 1));
	if (array == NULL)
		return (NULL);
	return (ft_array(s, c, array));
}
