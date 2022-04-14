/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/14 05:25:46 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ZOOM 10
#define ANGLE 0.8
#define SHIFT_X 1000
#define SHIFT_Y 200

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
		ft_putchar_fd('-', 1);
		data->non_print++;
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	(void) color;
	ft_putchar_fd('+', 1);
	data->print++;
}

// void	bresenham(t_fdf *map, t_pixel point, t_pixel point1)
// {
// 	float	x_step;
// 	float	y_step;
// 	int		max;
	
// 	//-----------SET_Z-----------
// 	// z = map->z[(int)y][(int)x];
// 	// z1 = map->z[(int)y1][(int)x1];

// 	//-----------COLOR-----------
// 	point.color = 0X0000CC;
// 	if (point.z > 0 || point1.z > 0)
// 		point.color = 0X00CC00;
// 	if (point.z < 0 || point1.z < 0)
// 		point.color = 0XCC0000;
// 	// color = map->color[(int)y][(int)x];

// 	//-----------ZOOM------------
// 	map->zoom = ZOOM;
// 	point.x *= map->zoom;
// 	point.y *= map->zoom;
// 	point1.x *= map->zoom;
// 	point1.y *= map->zoom;
// 	point.z *= map->zoom;
// 	point1.z *= map->zoom;

// 	//------------3D-------------
// 	map->angle = ANGLE;
// 	point.x = (point.x - point.y) * cos(map->angle);
// 	point.y = (point.x + point.y) * sin(map->angle) - point.z;
// 	point1.x = (point1.x - point1.y) * cos(map->angle);
// 	point1.y = (point1.x + point1.y) * sin(map->angle) - point1.z;

// 	//-----------SHIFT-----------
// 	map->shift_x = SHIFT_X;
// 	map->shift_y = SHIFT_Y;
// 	point.x += map->shift_x; //map->shift * 3;
// 	point.y += map->shift_y; //map->shift;
// 	point1.x += map->shift_x; //map->shift * 3;
// 	point1.y += map->shift_y; //map->shift;

// 	x_step = point1.x - point.x;
// 	y_step = point1.y - point.y;
// 	max = abs_max(x_step, y_step);
// 	x_step /= max;
// 	y_step /= max;

// 	while ((int)(point.x - point1.x) || (int)(point.y - point1.y))
// 	{
// 		// mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, color);
// 		my_mlx_pixel_put(map->data, point.x, point.y, point.color);
// 		point.x += x_step;
// 		point.y += y_step;
// 	}
// 	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
// }

// t_pixel	set_point(t_point *point)
// {
// 	t_pixel	pixel;

// 	pixel.x = (float)point->x;
// 	pixel.y = (float)point->y;
// 	pixel.z = point->z;
// 	pixel.color = point->color;
// 	// printf("LINE -> [%2d|%2d|%2d]->[%2f|%2f|%2d]\n",
// 	// 			point->x, point->y, point->z, pixel.x, pixel.y, pixel.z);
// 	return (pixel);
// }

// void	draw_map(t_fdf *map)
// {
// 	t_point *fix;
// 	// t_pixel	pixel;
// 	// t_pixel	pixel1;

// 	fix = map->head;
// 	while (map->head->next)
// 	{
// 		if (map->head->x1)//(map->head->x < map->width - 1)
// 		{
// 			// printf("LINE_X1 [%2d|%2d|%2d]->[%2d|%2d|%2d]\n",
// 			// 	map->head->x, map->head->y, map->head->z, map->head->x1->x, map->head->x1->y, map->head->x1->z);
// 			// pixel = set_point(map->head);
// 			// pixel1 = set_point(map->head->x1);
// 			// printf("LINE_X2 [%2f|%2f|%2d]->[%2f|%2f|%2d]\n",
// 			// 	pixel.x, pixel.y, pixel.z, pixel1.x, pixel1.y, pixel1.z);
// 			bresenham(map, set_point(map->head), set_point(map->head->x1));
// 		}
// 		if (map->head->y1)//(map->head->y < map->width - 1)
// 		{
// 			// printf("LINE_Y1 [%2d|%2d|%2d]->[%2d|%2d|%2d]\n",
// 			// 	map->head->x, map->head->y, map->head->z, map->head->y1->x, map->head->y1->y, map->head->y1->z);
// 			// pixel = set_point(map->head);
// 			// pixel1 = set_point(map->head->y1);
// 			// printf("LINE_Y2 [%2f|%2f|%2d]->[%2f|%2f|%2d]\n",
// 			// 	pixel.x, pixel.y, pixel.z, pixel1.x, pixel1.y, pixel1.z);
// 			bresenham(map, set_point(map->head), set_point(map->head->y1));
// 		}
// 		// printf("\n");
// 		map->head = map->head->next;
// 	}
// 	map->head = fix;
// 	ft_printf("    PRINTED PIXELS[%10d]\n", map->data->print);
// 	ft_printf("NON-PRINTED PIXELS[%10d]\n", map->data->non_print);
// 	ft_printf("      TOTAL PIXELS[%10d]\n", map->data->print + map->data->non_print);
// 	ft_printf("\n");
// }

// #define ZOOM 20
// #define ANGLE 0.8
// #define SHIFT_X 1000
// #define SHIFT_Y 200

void	bresenham(float x, float y, int z, float x1, float y1, int z1, t_fdf *map)
{
	float	x_step;
	float	y_step;
	int		max;
	// int		z;
	// int		z1;
	int		color;

	//-----------SET_Z-----------
	// z = map->z[(int)y][(int)x];
	// z1 = map->z[(int)y1][(int)x1];

	//-----------COLOR-----------
	color = 0X0000CC;
	if (z > 0|| z1 > 0)
		color = 0X00CC00;
	if (z < 0 || z1 < 0)
		color = 0XCC0000;
	// color = map->color[(int)y][(int)x];

	//-----------ZOOM------------
	map->zoom = ZOOM;
	x *= map->zoom;
	y *= map->zoom;
	x1 *= map->zoom;
	y1 *= map->zoom;
	z *= map->zoom;// / (int)(angle * 10);
	z1 *= map->zoom;// / (int)(angle * 10);

	//------------3D-------------
	map->angle = ANGLE;
	x = (x - y) * cos(map->angle);
	y = (x + y) * sin(map->angle) - z;
	x1 = (x1 - y1) * cos(map->angle);
	y1 = (x1 + y1) * sin(map->angle) - z1;

	//-----------SHIFT-----------
	map->shift_x = SHIFT_X;
	map->shift_y = SHIFT_Y;
	x += map->shift_x; //map->shift * 3;
	y += map->shift_y; //map->shift;
	x1 += map->shift_x; //map->shift * 3;
	y1 += map->shift_y; //map->shift;

	x_step = x1 - x;
	y_step = y1 - y;
	max = abs_max(x_step, y_step);
	x_step /= max;
	y_step /= max;

	while ((int)(x - x1) || (int)(y - y1))
	{
		// mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, color);
		my_mlx_pixel_put(map->data, x, y, color);
		x += x_step;
		y += y_step;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
}

void	draw_map(t_fdf *map)
{
	t_point *fix;

	fix = map->head;	
	while (map->head->next)
	{
		if (map->head->x1)
			bresenham(map->head->x, map->head->y, map->head->z,
				map->head->x1->x, map->head->x1->y, map->head->x1->z, map);
		if (map->head->y1)
			bresenham(map->head->x, map->head->y, map->head->z,
				map->head->y1->x, map->head->y1->y, map->head->y1->z, map);
		map->head = map->head->next;
	}
	map->head = fix;
	ft_printf("    PRINTED PIXELS[%10d]\n", map->data->print);
	ft_printf("NON-PRINTED PIXELS[%10d]\n", map->data->non_print);
	ft_printf("      TOTAL PIXELS[%10d]\n", map->data->print + map->data->non_print);
	ft_printf("\n");
}

// void	draw_map(t_fdf *map)
// {
// 	int x;
// 	int	y;

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
// 	ft_printf("    PRINTED PIXELS[%10d]\n", map->data->print);
// 	ft_printf("NON-PRINTED PIXELS[%10d]\n", map->data->non_print);
// 	ft_printf("      TOTAL PIXELS[%10d]\n", map->data->print + map->data->non_print);
// 	ft_printf("\n");
// }

// void	isometric(float *x, float *y, int z, float angle)
// {
// 	*x = (*x - *y) * cos(angle);
// 	*y = (*x + *y) * sin(angle) - z;
// }

// isometric(&x, &y, z, map->angle);
// isometric(&x1, &y1, z1, map->angle);
