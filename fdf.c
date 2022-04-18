/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/18 18:57:37 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	exit(0);
}

float	ft_abs(float a)
{
	if (a < 0)
		a *= -1;
	return (a);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	set_default(t_fdf *map)
{
	int	x;
	int	y;
	
	map->angle = 0.8;
	map->zoom = 1;//30 * 0.7;
	if (map->z_min >= 0 && map->z_max >= 0)
		map->z_shift = (map->z_max - map->z_min) / 2;
	else if (map->z_min < 0 && map->z_max < 0)
		map->z_shift = ft_abs((map->z_min - map->z_max) / 2);
	else
		map->z_shift = (ft_abs(map->z_min) + ft_abs(map->z_max)) / 2;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
			map->matrix[y][x].z -= map->z_shift;
	}
	map->x_shift = SCR_WIDTH / 2;
	map->y_shift = SCR_HEIGHT / 2;
	// map->zoom = ft_max(map->width / 2, map->height / 2);
	// map->zoom = ft_max(map->zoom_check, map->z_shift);
	// map->zoom = (ft_min(SCR_WIDTH, SCR_HEIGHT)) / 5 / map->zoom;
	map->x_min = -1000;
	map->x_max = 0;
	map->y_min = -1000;
	map->y_max = 0;
}

int	main(int argc, char **argv)
{
	t_fdf	*map;

	map = NULL;
	if (argc == 2)
		map = validation(argv[1]);
	if (!map)
		return (0);
	map->data = (t_data *)malloc(sizeof(t_data));
	if (!map->data)
		error_free_map_exit(map);
	set_default(map);
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, SCR_WIDTH, SCR_HEIGHT, "FDF");
	map->data->print = 0;
	map->data->non_print = 0;
	map->data->img = mlx_new_image(map->mlx_ptr, SCR_WIDTH, SCR_HEIGHT);
	map->data->addr = mlx_get_data_addr(map->data->img,
		&map->data->bits_per_pixel, &map->data->line_length, &map->data->endian);
	draw_map(map);
	mlx_key_hook(map->win_ptr, key_hook, map);
	mlx_loop(map->mlx_ptr);
	free_map(map);
	return (0);
}

	// int	x;
	// int	y;
	// for (y = 0; y < map->height; y++)
	// {
	// 	for (x = 0; x < map->width; x++)
	// 		ft_printf("%3d ",map->matrix[y][x].z);
	// 	ft_printf("\n");
	// }
	// for (y = 0; y < map->height; y++)
	// {
	// 	for (x = 0; x < map->width; x++)
	// 		ft_printf("%7X ", map->matrix[y][x].color);
	// 	ft_printf("\n");
	// }

	// int	x;
	// int	y;
	// for (y = 0; y < map->height; y++)
	// {
	// 	for (x = 0; x < map->width; x++)
	// 	{
	// 		if (!map->matrix[y][x].x)
	// 			ft_printf("\n");
	// 		ft_printf("[%2d |%2d |%2d |%7X] ",
	// 			map->matrix[y][x].x, map->matrix[y][x].y, map->matrix[y][x].z, map->matrix[y][x].color);
	// 	}
	// 	ft_printf("\n\n");
	// }
