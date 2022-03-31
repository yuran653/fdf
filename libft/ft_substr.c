/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 06:47:38 by jgoldste          #+#    #+#             */
/*   Updated: 2021/12/18 12:06:19 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	start_str;
	size_t	len_s;
	size_t	len_str;

	start_str = 0;
	if (!s)
		return (ft_calloc(1, 1));
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_calloc(1, 1));
	len_str = len_s - (size_t)start + 1;
	if (len_str > len + 1)
		len_str = len + 1;
	str = (char *)malloc(sizeof(char) * len_str);
	if (!str)
		return (NULL);
	while (len && len_str - 1)
	{
		str[start_str++] = s[start++];
		len--;
		len_str--;
	}
	str[start_str] = '\0';
	return (str);
}
