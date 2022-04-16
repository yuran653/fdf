/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/16 06:56:20 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	exit(0);
}

void	set_default(t_fdf *map)
{
	float	x_min;
	float	x_max;
	float	x;
	float	y;
	
	x = map->width;
	y = map->height;
	x_min = -y * cos(map->angle);
	x_max = x * cos(map->angle);
	printf("X_MIN = %f | X_MAX = %f\n", x_min, x_max);
	map->angle = 0.8;
	map->zoom = (x_max - x_min) * 0.8;
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
	map->win_ptr = mlx_new_window(map->mlx_ptr, 1920, 1080, "FDF");
	map->data->print = 0;
	map->data->non_print = 0;
	map->data->img = mlx_new_image(map->mlx_ptr, 1920, 1080);
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
