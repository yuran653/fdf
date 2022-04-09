/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/09 06:48:34 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	exit(0);
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
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, 1920, 1080, "FDF");
	map->data->img = mlx_new_image(map->mlx_ptr, 1920, 1080);
	map->data->addr = mlx_get_data_addr(map->data->img,
		&map->data->bits_per_pixel, &map->data->line_length, &map->data->endian);
	draw_map(map);
	mlx_key_hook(map->win_ptr, key_hook, map);
	mlx_loop(map->mlx_ptr);
	free_map(map);
	return (0);
}

	// int y;
	// int x;
	// for (y = 0; map->z[y]; y++)
	// {
	// 	ft_printf("%3d - ", y);
	// 	for (x = 0; x < map->x; x++)
	// 		ft_printf("%3d", map->z[y][x]);
	// 	ft_printf("\n");		
	// }
	// for (y = 0; map->color[y]; y++)
	// {
	// 	ft_printf("%3d - ", y);
	// 	for (x = 0; x < map->x; x++)
	// 		ft_printf("%7X", map->color[y][x]);
	// 	ft_printf("\n");		
	// }
