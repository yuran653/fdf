/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/16 06:20:03 by jgoldste         ###   ########.fr       */
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

	if ((x < 0 && x >= 1920) || (y < 0 && y >= 1080))
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

void	bresenham(t_point point, t_point point1, t_fdf *map)
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
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
}

t_point	set_values(t_point point,t_fdf *map)
{
	int	print;
	
	print = 0;
	if ((point.x == 0 && point.y == 0) ||
		(point.x == map->width - 1 && point.y == 0) ||
		(point.x == 0 && point.y == map->height - 1) ||
		(point.x == map->width - 1 && point.y == map->height - 1))
	{
		print++;
		printf("POINT [%f, %f] -> ", point.x, point.y);
	}
	
	//-----------COLOR-----------
	point.color = 0X0000CC;
	if (point.z > 0)//|| point1.z > 0)
		point.color = 0X00CC00;
	if (point.z < 0)// || point1.z < 0)
		point.color = 0XCC0000;
	
	//-----------ZOOM------------
	point.x *= map->zoom;
	point.y *= map->zoom;
	point.z *= map->zoom;
	
	//------------3D-------------
	point.x = (point.x - point.y) * cos(map->angle);
	point.y = (point.x + point.y) * sin(map->angle) - point.z;
	
	//-----------SHIFT-----------
	// point.x += SHIFT_X;
	// point.y += SHIFT_Y;


	// printf("->");
	if (print)
		printf("[%f, %f]\n", point.x, point.y);
	
	// printf("->");

	(void) map;	
	return (point);
}

void	draw_map(t_fdf *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
				bresenham(set_values(map->matrix[y][x], map), set_values(map->matrix[y][x + 1], map), map);
			if (y < map->height - 1)
				bresenham(set_values(map->matrix[y][x], map), set_values(map->matrix[y + 1][x], map), map);
			x++;
		}
		y++;
	}
	ft_printf("    PRINTED PIXELS[%10d]\n", map->data->print);
	ft_printf("NON-PRINTED PIXELS[%10d]\n", map->data->non_print);
	ft_printf("      TOTAL PIXELS[%10d]\n", map->data->print + map->data->non_print);
	ft_printf("\n");
}

// 	ft_printf("    PRINTED PIXELS[%10d]\n", map->data->print);
// 	ft_printf("NON-PRINTED PIXELS[%10d]\n", map->data->non_print);
// 	ft_printf("      TOTAL PIXELS[%10d]\n", map->data->print + map->data->non_print);
// 	ft_printf("\n");

//	---------ISOMETRIC---------
// 	x = (x - y) * cos(angle);
// 	y = (x + y) * sin(angle) - z;
