/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2023/08/07 12:28:18 by jgoldste         ###   ########.fr       */
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
	steps.i = 0;
	while (steps.i < steps.max)
	{
		my_mlx_pixel_put(map->data, point.x + steps.x_step * steps.i,
			point.y + steps.y_step * steps.i,
			get_gradient(point.color, point1.color, steps.max, steps.i));
		steps.i++;
	}
}

static t_point	set_values(t_point point, t_fdf *map)
{
	rotate_abscissa(&point, map);
	rotate_ordinate(&point, map);
	rotate_altitude(&point, map);
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
		set_color(point, map);
		set_color(point1, map);
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
	print_how_to_use(map, 0);
}
