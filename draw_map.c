/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/21 20:15:20 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCR_WIDTH || y < 0 || y >= SCR_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	bresenham(t_point point, t_point point1, t_fdf *map)
{
	t_steps	steps;

	steps.x_step = point1.x - point.x;
	steps.y_step = point1.y - point.y;
	steps.max = abs_max(steps.x_step, steps.y_step);
	steps.x_step /= steps.max;
	steps.y_step /= steps.max;
	while ((int)(point.x - point1.x) || (int)(point.y - point1.y))
	{
		my_mlx_pixel_put(map->data, point.x, point.y, point.color);
		point.x += steps.x_step;
		point.y += steps.y_step;
	}
}

t_point	set_values(t_point point, t_fdf *map)
{
	rotate_abscissa(&point, map);
	if (map->projection == ISO)
	{
		map->tmp.x = (point.x * map->zoom - point.y * map->zoom)
			* cos(map->angle) + map->x_shift;
		point.y = (point.x * map->zoom + point.y * map->zoom)
			* sin(map->angle) + map->y_shift - point.z * map->zoom;
		point.x = map->tmp.x;
		return (point);
	}
	else if (map->projection == PARALLEL)
	{
		map->tmp.x = point.x * map->zoom * cos(map->angle)
			- point.y * map->zoom * sin(map->angle) + map->x_shift;
		point.y = point.x * map->zoom * sin(map->angle)
			+ point.y * map->zoom * cos(map->angle) + map->y_shift;
		point.x = map->tmp.x;
		return (point);
	}
	return (point);
}

static void	set_color_draw_line(t_fdf *map, t_color color,
	t_point *point, t_point *point1)
{
	if (color == DEFAULT)
	{
		point->color = point->color_default;
		point1->color = point1->color_default;
	}
	if (color == RGB)
	{
		point->color = 0XCC0000;
		if (point->z_default == 0 && point1->z_default == 0)
			point->color = 0X0000CC;
		if (point->z_default > 0 || point1->z_default > 0)
			point->color = 0X00CC00;
	}
	bresenham(set_values(*point, map), set_values(*point1, map), map);
}

void	draw_map(t_fdf *map)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (x < map->width - 1)
				set_color_draw_line(map, map->color,
					&map->matrix[y][x], &map->matrix[y][x + 1]);
			if (y < map->height - 1)
				set_color_draw_line(map, map->color,
					&map->matrix[y][x], &map->matrix[y + 1][x]);
		}
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
}

// ---------ISOMETRIC---------
// x = (x - y) * cos(angle);
// y = (x + y) * sin(angle) - z;
// point.x = (point.x * map->zoom - point.y * map->zoom)
//	* cos(map->angle) + map->x_shift;
// point.y = (point.x - map->x_shift + point.y * map->zoom)
// 	* sin(map->angle) - point.z * map->zoom + map->y_shift;