/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:40:30 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/19 12:16:41 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCR_WIDTH || y < 0 || y >= SCR_HEIGHT)
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

t_point	set_values(t_point point, t_fdf *map)
{
	//-----------ZOOM------------
	point.x *= map->zoom;
	point.y *= map->zoom;
	point.z *= map->zoom;
	
	//------------3D-------------
	point.x = (point.x - point.y) * cos(map->angle);
	point.y = (point.x + point.y) * sin(map->angle) - point.z;
	
	//-----------SHIFT-----------
	point.x += map->x_shift;
	point.y += map->y_shift;

	printf("POINT [%f, %f]\n", point.x, point.y);

	return (point);
}

void	set_color(t_point *point, t_point *point1)
{
	point->color = 0X0000CC;
	if (point->z_color > 0 || point1->z_color > 0)
		point->color = 0X00CC00;
	if (point->z_color < 0 || point1->z_color < 0)
		point->color = 0XCC0000;
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
			{
				set_color(&map->matrix[y][x], &map->matrix[y][x + 1]);
				bresenham(set_values(map->matrix[y][x], map),
					set_values(map->matrix[y][x + 1], map), map);
			}
			if (y < map->height - 1)
			{
				set_color(&map->matrix[y][x], &map->matrix[y + 1][x]);
				bresenham(set_values(map->matrix[y][x], map),
					set_values(map->matrix[y + 1][x], map), map);
			}
		}
	}
	ft_printf("    PRINTED PIXELS[%10d]\n", map->data->print);
	ft_printf("NON-PRINTED PIXELS[%10d]\n", map->data->non_print);
	ft_printf("      TOTAL PIXELS[%10d]\n", map->data->print + map->data->non_print);
	ft_printf("\n");
}

// printf("MIN X = %f | MAX X = %f | DIFF X = %f\n", map->x_min, map->x_max, map->x_max - map->x_min);
// printf("MIN Y = %f | MAX Y = %f | DIFF Y = %f\n", map->y_min, map->y_max, map->y_max - map->y_min);
// printf("SHIFT X = %d | SHIFT Y = %d\n", SCR_WIDTH / 2, SCR_HEIGHT / 2);
// printf("MIN Z = %d | MAX Z = %d | SHIFT Z = %d\n", map->z_min, map->z_max, map->z_shift);


// 	ft_printf("    PRINTED PIXELS[%10d]\n", map->data->print);
// 	ft_printf("NON-PRINTED PIXELS[%10d]\n", map->data->non_print);
// 	ft_printf("      TOTAL PIXELS[%10d]\n", map->data->print + map->data->non_print);
// 	ft_printf("\n");

// if (point.x > map->x_max)
// 	map->x_max = point.x;
// if (point.y > map->y_max)
// 	map->y_max = point.y;
// if (map->x_min == -1000)
// 	map->x_min = point.x;
// if (point.x < map->x_min)
// 	map->x_min = point.x;
// if (map->y_min == -1000)
// 	map->y_min = point.y;
// if (point.y < map->y_min)
// 	map->y_min = point.y;


//	---------ISOMETRIC---------
// 	x = (x - y) * cos(angle);
// 	y = (x + y) * sin(angle) - z;
