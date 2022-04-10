/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:37:06 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/10 01:27:47 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *map)
{
	if (keycode == 53)
		error_free_map_win_exit(map, EXIT_SUCCESS);
	// if (keycode == 69)
	// {
	// 	map->zoom += 10;
	// 	map->data->img = mlx_new_image(map->mlx_ptr, 1920, 1080);
	// 	map->data->addr = mlx_get_data_addr(map->data->img,
	// 		&map->data->bits_per_pixel, &map->data->line_length, &map->data->endian);
	// 	draw_map(map);
	// 	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	// 	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->data->img, 0, 0);
	// }
	// ft_printf("keycode = [%d]\n", keycode);
	return (0);
}

// + -> 69
// - -> 78