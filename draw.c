/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/08 03:54:21 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	abs_max(double a, double b)
{
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (a > b)
		return (a);
	else
		return (b);
}

void	isometric(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

#define ZOOM 20
#define ANGLE 0.8
#define SHIFT 330

void	bresenham(float x, float y, float x1, float y1, t_fdf *map)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;
	int		color;
	float	angle;

	z = map->z[(int)y][(int)x];
	z1 = map->z[(int)y1][(int)x1];

	//-----------COLOR-----------
	// color = 0XFFFFFF;
	// if (z || z1)
	// 	color = 0X00FF00;
	color = map->color[(int)y][(int)x];

	angle = ANGLE;
	
	//-----------ZOOM------------
	map->zoom = ZOOM;
	x *= map->zoom;
	y *= map->zoom;
	x1 *= map->zoom;
	y1 *= map->zoom;
	z *= map->zoom;// / (int)(angle * 10);
	z1 *= map->zoom;// / (int)(angle * 10);

	//------------3D-------------
	isometric(&x, &y, z, angle);
	isometric(&x1, &y1, z1, angle);

	//-----------SHIFT-----------
	map->shift = SHIFT;
	x += map->shift * 3;
	y += map->shift;
	x1 += map->shift * 3;
	y1 += map->shift;

	x_step = x1 - x;
	y_step = y1 - y;
	max = abs_max(x_step, y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		my_mlx_pixel_put(map->data, x, y, color);
		x += x_step;
		y += y_step;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
}

void	draw_map(t_fdf *map)
{
	int x;
	int	y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (x < map->x - 1)
				bresenham (x, y, x + 1, y, map);
			if (y < map->y - 1)
				bresenham (x, y, x, y + 1, map);
			x++;
		}
		y++;
	}
}
