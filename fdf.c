/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/23 19:45:45 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_default_zoom_rotate(t_fdf *map)
{
	map->zoom = ft_max(map->width / 2, map->height / 2);
	map->zoom = ft_max(map->zoom, map->z_zoom);
	map->zoom = (ft_min(SCR_WIDTH, SCR_HEIGHT)) / 3.75 / map->zoom;
	map->rotate->alpha = 0;
	map->rotate->alpha_rt = 0;
	map->rotate->beta = 0;
	map->rotate->beta_rt = 0;
	map->rotate->gamma = 0;
	map->rotate->gamma_rt = 0;
	map->rotate_save->alpha = 0;
	map->rotate_save->alpha_rt = 0;
	map->rotate_save->beta = 0;
	map->rotate_save->beta_rt = 0;
	map->rotate_save->gamma = 0;
	map->rotate_save->gamma_rt = 0;
}

static void	set_z_shift_zoom(t_fdf *map)
{
	if (map->z_min >= 0 && map->z_max >= 0)
	{
		map->z_shift = (map->z_max - map->z_min) / 2;
		map->z_zoom = map->z_shift;
	}
	else if (map->z_min < 0 && map->z_max < 0)
	{
		map->z_shift = (map->z_min - map->z_max) / 2;
		map->z_zoom = map->z_shift;
	}
	else
	{
		map->z_shift = (map->z_min + map->z_max) / 2;
		map->z_zoom = (ft_abs(map->z_min) + ft_abs(map->z_max)) / 2;
	}
}

void	set_default(t_fdf *map)
{
	int	x;
	int	y;

	map->angle_rt = 0.175;
	map->angle = M_PI * map->angle_rt;
	map->projection = ISO;
	set_z_shift_zoom(map);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			map->matrix[y][x].color = map->matrix[y][x].color_default;
			map->matrix[y][x].z = map->matrix[y][x].z_default - map->z_shift;
		}
	}
	map->x_shift = SCR_WIDTH / 2 + 150;
	map->y_shift = SCR_HEIGHT / 2;
	map->color = DEFAULT;
	set_default_zoom_rotate(map);
}

static void	malloc_variables(t_fdf *map)
{
	map->data = (t_data *)malloc(sizeof(t_data));
	if (!map->data)
		error_free_map_exit(map);
	map->rotate = (t_rotate *)malloc(sizeof(t_rotate));
	if (!map->rotate)
		error_free_map_exit(map);
	map->rotate_save = (t_rotate *)malloc(sizeof(t_rotate));
	if (!map->rotate)
		error_free_map_exit(map);
}

int	main(int argc, char **argv)
{
	t_fdf	*map;

	map = NULL;
	if (argc != 2)
		return (0);
	map = validation(argv[1]);
	if (!map)
		return (0);
	malloc_variables(map);
	set_default(map);
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, SCR_WIDTH, SCR_HEIGHT, "FDF");
	map->data->img = mlx_new_image(map->mlx_ptr, SCR_WIDTH, SCR_HEIGHT);
	map->data->addr = mlx_get_data_addr(map->data->img,
			&map->data->bits_per_pixel, &map->data->line_length,
			&map->data->endian);
	draw_map(map);
	mlx_hook(map->win_ptr, 2, 0L, key_hook, map);
	mlx_loop(map->mlx_ptr);
	free_map(map);
	return (0);
}
