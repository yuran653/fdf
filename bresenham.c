/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:31:16 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/14 02:19:59 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ZOOM 20
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
	if (pixel->z > 0)
		pixel->color = 0X00CC00;
	else if (pixel->z < 0)
		pixel->color = 0XCC0000;
	else
		pixel->color = 0X0000CC;
	(void) map;
	// pixel->color = map->color[(int)pixel->y][(int)pixel->x];
}

void	init_pixel(t_pixel *pixel, t_fdf *map, char x_or_y)
{
	pixel->z = map->head->z;
	pixel->z1 = map->head->z;
	pixel->x = (float)map->head->x;
	pixel->x1 = (float)map->head->x;
	if (map->head->x1 && x_or_y == 'x')
	{
		pixel->x1 = (float)map->head->x1->x;
		pixel->z1 = map->head->x1->z;
	}
	pixel->y = (float)map->head->y;
	pixel->y1 = (float)map->head->y;
	if (map->head->y1 && x_or_y == 'y')
	{
			pixel->y1 = (float)map->head->y1->y;
			pixel->z1 = map->head->y1->z;
	}
	pixel->color = map->head->color;
}

void	bresenham(t_fdf *map, char x_or_y)
{
	t_steps	steps;
	t_pixel pixel;

	init_pixel(&pixel, map, x_or_y);
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
		my_mlx_pixel_put(map->data, pixel.x, pixel.y, pixel.color);
		pixel.x += steps.x_step;
		pixel.y += steps.y_step;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
}

// void	set_shift(t_pixel *pixel, t_fdf *map)
// {
// 	map->shift_x = SHIFT_X;
// 	map->shift_y = SHIFT_Y;
// 	pixel->x += map->shift_x;
// 	pixel->y += map->shift_y;
// 	pixel->x1 += map->shift_x;
// 	pixel->y1 += map->shift_y;
// }

// void	set_isometric(t_pixel *pixel, t_fdf *map)
// {
// 	map->angle = ANGLE;
// 	pixel->x = (pixel->x - pixel->y) * cos(map->angle);
// 	pixel->y = (pixel->x + pixel->y) * sin(map->angle) - pixel->z;
// 	pixel->x1 = (pixel->x1 - pixel->y1) * cos(map->angle);
// 	pixel->y1 = (pixel->x1 + pixel->y1) * sin(map->angle) - pixel->z1;
// }

// void	set_zoom(t_pixel *pixel, t_fdf *map)
// {
// 	map->zoom = ZOOM;
// 	pixel->x *= map->zoom;
// 	pixel->y *= map->zoom;
// 	pixel->x1 *= map->zoom;
// 	pixel->y1 *= map->zoom;
// 	pixel->z *= map->zoom;
// 	pixel->z1 *= map->zoom;
// }

// void	set_color(t_pixel *pixel, t_fdf *map)
// {
// 	if (pixel->z > 0 || pixel->z1 > 0)
// 		pixel->color = 0X00CC00;
// 	else if (pixel->z < 0 || pixel->z1 < 0)
// 		pixel->color = 0XCC0000;
// 	else
// 		pixel->color = 0X0000CC;
// 	(void) map;
// 	// pixel->color = map->color[(int)pixel->y][(int)pixel->x];
// }

// void	bresenham(t_fdf *map, int x1, int y1, int z1)
// {
// 	t_steps	steps;


// 	// pixel.z = map->z[(int)pixel.y][(int)pixel.x];
// 	// pixel.z1 = map->z[(int)pixel.y1][(int)pixel.x1];
// 	set_color(&pixel, map);
// 	set_zoom(&pixel, map);
// 	set_isometric(&pixel, map);
// 	set_shift(&pixel, map);
// 	steps.x_step = pixel.x1 - pixel.x;
// 	steps.y_step = pixel.y1 - pixel.y;
// 	steps.max = abs_max(steps.x_step, steps.y_step);
// 	steps.x_step /= steps.max;
// 	steps.y_step /= steps.max;
// 	while ((int)(pixel.x - pixel.x1) || (int)(pixel.y - pixel.y1))
// 	{
// 		my_mlx_pixel_put(map->data, pixel.x, pixel.y, pixel.color);
// 		pixel.x += steps.x_step;
// 		pixel.y += steps.y_step;
// 	}
// 	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
// 	// ft_printf("x = %2d x1 = %2d y = %2d y1 = %2d z = %2d z1 = %2d\n",
// 	// 	map->head->x, x1, map->head->y, y1, map->head->z, z1);
// }
