/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:15:52 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/20 14:37:13 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

float	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_abs(float a)
{
	if (a < 0)
		a *= -1;
	return (a);
}

float	abs_max(float a, float b)
{
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (a > b)
		return (a);
	return (b);
}
