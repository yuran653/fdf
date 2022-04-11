/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/11 21:37:12 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 1920 || y >= 1080)
	{
		// ft_putchar_fd('-', 1);
		data->non_print++;
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	(void) color;
	// ft_putchar_fd('+', 1);
	data->print++;
}

void	init_pixel(t_pixel *pixel, char x_or_y, t_fdf *map)
{
	pixel->x = (float)map->head->x;
	pixel->x1 = (float)map->head->x;
	if (x_or_y == 'x')
	{
		pixel->x1++;
		pixel->z1 = map->head->zx;
	}
	pixel->y = (float)map->head->y;
	pixel->y1 = (float)map->head->y;
	if (x_or_y == 'y')
	{
		pixel->y1++;
		pixel->z1 = map->head->zy;
	}
	pixel->z = map->head->z;
	pixel->color = map->head->color;
}

void	draw_map(t_fdf *map)
{
	t_point	*fix;
	t_pixel	pixel;

	fix = map->head;
	while (map->head)
	{
		init_pixel(&pixel, 'x', map);
		if (pixel.x < map->width - 1)
			bresenham(pixel, map);
		init_pixel(&pixel, 'y', map);
		if (pixel.y < map->height - 1)
			bresenham(pixel, map);
		map->head = map->head->next;
	}
	map->head = fix;
	ft_putchar_fd('\n', 1);
	ft_printf("  PRINTED PIXELS AMOUNT [%d]\n", map->data->print);
	ft_printf("NON PRINT PIXELS AMOUNT [%d]\n", map->data->non_print);
}

// void	draw_map(t_fdf *map)
// {
// 	t_pixel	pixel;

// 	map->data->non_print = 0;
// 	pixel.y = -1;
// 	while (++pixel.y < map->y)
// 	{
// 		pixel.x = -1;
// 		while (++pixel.x < map->x)
// 		{
// 			pixel.x1 = pixel.x;
// 			pixel.y1 = pixel.y;
// 			if (pixel.x < map->x - 1)
// 				set_value_draw_line(&pixel, map, &pixel.x, &pixel.x1);
// 			if (pixel.y < map->y - 1)
// 				set_value_draw_line(&pixel, map, &pixel.y, &pixel.y1);
// 		}
// 	}
// 	ft_putchar_fd('\n', 1);
// 	printf("NON PRINT PIXELS AMOUNT [%d]\n", map->data->non_print);
// }

// #define ZOOM 20
// #define ANGLE 0.8
// #define SHIFT_X 1000
// #define SHIFT_Y 200

// void	bresenham(float x, float y, float x1, float y1, t_fdf *map)
// {
// 	float	x_step;
// 	float	y_step;
// 	int		max;
// 	int		z;
// 	int		z1;
// 	int		color;

// 	//-----------SET_Z-----------
// 	z = map->z[(int)y][(int)x];
// 	z1 = map->z[(int)y1][(int)x1];

// 	//-----------COLOR-----------
// 	color = 0X0000CC;
// 	if (z > 0|| z1 > 0)
// 		color = 0X00CC00;
// 	if (z < 0 || z1 < 0)
// 		color = 0XCC0000;
// 	// color = map->color[(int)y][(int)x];

// 	//-----------ZOOM------------
// 	map->zoom = ZOOM;
// 	x *= map->zoom;
// 	y *= map->zoom;
// 	x1 *= map->zoom;
// 	y1 *= map->zoom;
// 	z *= map->zoom;// / (int)(angle * 10);
// 	z1 *= map->zoom;// / (int)(angle * 10);

// 	//------------3D-------------
// 	map->angle = ANGLE;
// 	x = (x - y) * cos(map->angle);
// 	y = (x + y) * sin(map->angle) - z;
// 	x1 = (x1 - y1) * cos(map->angle);
// 	y1 = (x1 + y1) * sin(map->angle) - z1;

// 	//-----------SHIFT-----------
// 	map->shift_x = SHIFT_X;
// 	map->shift_y = SHIFT_Y;
// 	x += map->shift_x; //map->shift * 3;
// 	y += map->shift_y; //map->shift;
// 	x1 += map->shift_x; //map->shift * 3;
// 	y1 += map->shift_y; //map->shift;

// 	x_step = x1 - x;
// 	y_step = y1 - y;
// 	max = abs_max(x_step, y_step);
// 	x_step /= max;
// 	y_step /= max;

// 	while ((int)(x - x1) || (int)(y - y1))
// 	{
// 		// mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, color);
// 		my_mlx_pixel_put(map->data, x, y, color);
// 		x += x_step;
// 		y += y_step;
// 	}
// 	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
// }

// void	draw_map(t_fdf *map)
// {
// 	int x;
// 	int	y;

// 	map->data->count = 0;
// 	y = 0;
// 	while (y < map->y)
// 	{
// 		x = 0;
// 		while (x < map->x)
// 		{
// 			if (x < map->x - 1)
// 				bresenham(x, y, x + 1, y, map);
// 			if (y < map->y - 1)
// 				bresenham(x, y, x, y + 1, map);
// 			x++;
// 		}
// 		y++;
// 	}
// 	ft_putchar_fd('\n', 1);
// 	printf("count = %d\n", map->data->count);
// }

// void	isometric(float *x, float *y, int z, float angle)
// {
// 	*x = (*x - *y) * cos(angle);
// 	*y = (*x + *y) * sin(angle) - z;
// }

// isometric(&x, &y, z, map->angle);
// isometric(&x1, &y1, z1, map->angle);
