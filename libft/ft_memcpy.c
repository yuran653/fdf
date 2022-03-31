/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:40:39 by jgoldste          #+#    #+#             */
/*   Updated: 2021/12/18 12:05:09 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*dst_r;

	dst_r = (void *)dst;
	if (!dst && !src)
		return (dst_r);
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (dst_r);
}
