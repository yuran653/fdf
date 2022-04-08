/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:39:15 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/09 02:03:38 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_free_map_win_exit(t_fdf *map, int err)
{
	mlx_destroy_image(map->mlx_ptr, map->data->img);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	free_map(map);
	if (!err)
		exit(EXIT_SUCCESS);
	error_common();
}