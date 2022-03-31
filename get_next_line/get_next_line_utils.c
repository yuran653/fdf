/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 04:42:33 by jgoldste          #+#    #+#             */
/*   Updated: 2021/12/17 13:01:44 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (*str++ != '\0')
		i++;
	return (i);
}

int	ft_strchr_gnl(char *str, int c)
{
	if (str == NULL)
		return (0);
	while (*str != c)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return (1);
}

void	ft_strlcpy_gnl(char *dst, char *src)
{
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
}

void	ft_strlcat_gnl(char *dst, char *src)
{
	while (*dst != '\0')
		dst++;
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char)
			* (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy_gnl(str, s1);
	ft_strlcat_gnl(str, s2);
	while (*s2)
		*s2++ = '\0';
	free(s1);
	return (str);
}
