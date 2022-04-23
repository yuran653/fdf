/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:00:41 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/24 00:59:05 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	spectrum(int color, int mask, int shift)
{
	return ((color & mask) >> shift);
}

int	get_gradient(int start, int end, int len, int i)
{
	int	color;
	int	r;
	int	g;
	int	b;

	r = spectrum(end, R_MASK, R_SHIFT) - spectrum(start, R_MASK, R_SHIFT);
	g = spectrum(end, G_MASK, G_SHIFT) - spectrum(start, G_MASK, G_SHIFT);
	b = spectrum(end, B_MASK, B_SHIFT) - spectrum(start, B_MASK, B_SHIFT);
	color = create_rgb(
			(int)(spectrum(start, R_MASK, R_SHIFT) + (double)r / len * i),
			(int)(spectrum(start, G_MASK, G_SHIFT) + (double)g / len * i),
			(int)(spectrum(start, B_MASK, B_SHIFT) + (double)b / len * i));
	return (color);
}

void	set_color(t_point *point, t_fdf *map)
{
	point->color = 0X00CC66;
	if (point->z_default < 0)
	{
		point->color = 0X66CC00;
		if (point->z_default <= 0.2 * map->z_min)
			point->color = 0X00CCCC;
		if (point->z_default <= 0.4 * map->z_min)
			point->color = 0X0066CC;
		if (point->z_default <= 0.6 * map->z_min)
			point->color = 0X0000CC;
		if (point->z_default <= 0.8 * map->z_min)
			point->color = 0X6600CC;
	}
	if (point->z_default > 0)
	{
		point->color = 0X00CC00;
		if (point->z_default >= 0.25 * map->z_max)
			point->color = 0X66CC00;
		if (point->z_default >= 0.50 * map->z_max)
			point->color = 0XCCCC00;
		if (point->z_default >= 0.75 * map->z_max)
			point->color = 0XCC6600;
		if (point->z_default >= 0.75 * map->z_max)
			point->color = 0XCC0000;
	}
}
