/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:45:11 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/05 00:13:37 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calloc_arrays(t_fdf *map, char *str)
{
	int	y;

	y = 0;
	map->z = (int **)malloc(sizeof(int *) * (map->y + 1));
	if (!map->z)
		error_free_str_exit(map, str);
	while (y <= map->y)
		map->z[y++] = NULL;
	y = 0;
	map->color = (int **)malloc(sizeof(int *) * (map->y + 1));
	if (!map->color)
		error_free_str_exit(map, str);
	while (y <= map->y)
		map->color[y++] = NULL;
}