/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/09 07:25:05 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ZOOM 20
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
		data->count++;
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	ft_putchar_fd('+', 1);
}

void	bresenham(float x, float y, float x1, float y1, t_fdf *map)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;
	int		color;

	//-----------SET_Z-----------
	z = map->z[(int)y][(int)x];
	z1 = map->z[(int)y1][(int)x1];

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
	int x;
	int	y;

	map->data->count = 0;
	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (x < map->x - 1)
				bresenham(x, y, x + 1, y, map);
			if (y < map->y - 1)
				bresenham(x, y, x, y + 1, map);
			x++;
		}
		y++;
	}
	ft_putchar_fd('\n', 1);
	printf("count = %d\n", map->data->count);
}

// void	isometric(float *x, float *y, int z, float angle)
// {
// 	*x = (*x - *y) * cos(angle);
// 	*y = (*x + *y) * sin(angle) - z;
// }

// isometric(&x, &y, z, map->angle);
// isometric(&x1, &y1, z1, map->angle);
