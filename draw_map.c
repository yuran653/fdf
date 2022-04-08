/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/09 02:58:11 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ZOOM 20
#define ANGLE 0.8
#define SHIFT 330

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

void	isometric(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

// void	isometric(float x, float y, int z, float angle)
// {
// 	x = (x - z) * cos(angle);
// 	y = (x + y) * sin(angle) - z;
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// if (x < 1920 && y < 1080)
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	make_shift(t_fdf *map, t_bresenham *pixel)
// {
// 	pixel->x += map->shift * 3;
// 	pixel->y += map->shift;
// 	pixel->x1 += map->shift * 3;
// 	pixel->y1 += map->shift;
// }

// void	make_isometric(t_fdf *map, t_bresenham *pixel)
// {
// 	isometric(pixel->x, pixel->y, pixel->z, map->angle);
// 	isometric(pixel->x1, pixel->y1, pixel->z1, map->angle);
// }

// void	make_zoom(t_fdf *map, t_bresenham *pixel)
// {
// 	pixel->x *= map->zoom;
// 	pixel->y *= map->zoom;
// 	pixel->x1 *= map->zoom;
// 	pixel->y1 *= map->zoom;
// 	pixel->z *= map->zoom;
// 	pixel->z1 *= map->zoom;
// }

// t_bresenham	*init_data(float x, float y, char x_or_y, t_fdf *map)
// {
// 	t_bresenham	*pixel;

// 	pixel = (t_bresenham *)malloc(sizeof(t_bresenham));
// 	if (!pixel)
// 		error_free_map_win_exit(map, EXIT_FAILURE);
// 	pixel->color = map->color[(int)y][(int)x];
// 	pixel->x = x;
// 	pixel->x1 = x;
// 	if (x_or_y == 'x')
// 		pixel->x1++;
// 	pixel->y = y;
// 	pixel->y1 = y;
// 	if (x_or_y == 'y')
// 		pixel->y1++;
// 	pixel->z = map->z[(int)y][(int)x];
// 	pixel->z1 = map->z[(int)pixel->y1][(int)pixel->x1];
// 	make_zoom(map, pixel);
// 	make_isometric(map, pixel);
// 	make_shift(map, pixel);
// 	pixel->x_step = pixel->x1 - x;
// 	pixel->y_step = pixel->y1 - y;
// 	pixel->max = abs_max(pixel->x_step, pixel->y_step);
// 	pixel->x_step /= pixel->max;
// 	pixel->y_step /= pixel->max;
// 	return (pixel);
// }

// void	bresenham(float x, float y, char x_or_y, t_fdf *map)
// {
// 	t_bresenham	*pixel;

// 	pixel = init_data(x, y, x_or_y, map);
// 	while ((int)(pixel->x - pixel->x1) || (int)(pixel->y - pixel->y1))
// 	{
// 		my_mlx_pixel_put(map->data, pixel->x, pixel->y, pixel->color);
// 		pixel->x += pixel->x_step;
// 		pixel->y += pixel->y_step;
// 	}
// 	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
// 	free(pixel);
// }

// void	draw_map(t_fdf *map)
// {
// 	int x;
// 	int	y;

// 	map->zoom = ZOOM;
// 	map->shift = SHIFT;
// 	map->angle = ANGLE;
// 	y = 0;
// 	while (y < map->y)
// 	{
// 		x = 0;
// 		while (x < map->x)
// 		{
// 			if (x < map->x - 1)
// 				bresenham (x, y, 'x', map);
// 			if (y < map->y - 1)
// 				bresenham (x, y, 'y', map);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	bresenham(float x, float y, float x1, float y1,t_fdf *map)
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
