/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:31:16 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/10 03:49:36 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ZOOM 1
#define ANGLE 0.8
#define SHIFT_X 1000
#define SHIFT_Y 200

void	set_shift(t_pixel *pixel, t_fdf *map)
{
	map->shift_x = SHIFT_X;
	map->shift_y = SHIFT_Y;
	pixel->x += map->shift_x;
	pixel->y += map->shift_y;
	pixel->x1 += map->shift_x;
	pixel->y1 += map->shift_y;
}

void	set_isometric(t_pixel *pixel, t_fdf *map)
{
	map->angle = ANGLE;
	pixel->x = (pixel->x - pixel->y) * cos(map->angle);
	pixel->y = (pixel->x + pixel->y) * sin(map->angle) - pixel->z;
	pixel->x1 = (pixel->x1 - pixel->y1) * cos(map->angle);
	pixel->y1 = (pixel->x1 + pixel->y1) * sin(map->angle) - pixel->z1;
}

void	set_zoom(t_pixel *pixel, t_fdf *map)
{
	map->zoom = ZOOM;
	pixel->x *= map->zoom;
	pixel->y *= map->zoom;
	pixel->x1 *= map->zoom;
	pixel->y1 *= map->zoom;
	pixel->z *= map->zoom;
	pixel->z1 *= map->zoom;
}

void	set_color(t_pixel *pixel, t_fdf *map)
{
	if (pixel->z > 0 || pixel->z1 > 0)
		pixel->color = 0X00CC00;
	else if (pixel->z < 0 || pixel->z1 < 0)
		pixel->color = 0XCC0000;
	else
		pixel->color = 0X0000CC;
	(void) map;
	// pixel->color = map->color[(int)pixel->y][(int)pixel->x];
}

void	bresenham(t_pixel pixel, t_fdf *map)
{
	t_steps	steps;

	pixel.z = map->z[(int)pixel.y][(int)pixel.x];
	pixel.z1 = map->z[(int)pixel.y1][(int)pixel.x1];
	set_color(&pixel, map);
	set_zoom(&pixel, map);
	set_isometric(&pixel, map);
	set_shift(&pixel, map);
	steps.x_step = pixel.x1 - pixel.x;
	steps.y_step = pixel.y1 - pixel.y;
	steps.max = abs_max(steps.x_step, steps.y_step);
	steps.x_step /= steps.max;
	steps.y_step /= steps.max;
	while ((int)(pixel.x - pixel.x1) || (int)(pixel.y - pixel.y1))
	{
		// mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, color);
		my_mlx_pixel_put(map->data, pixel.x, pixel.y, pixel.color);
		pixel.x += steps.x_step;
		pixel.y += steps.y_step;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
}
