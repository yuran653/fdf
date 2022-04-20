/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:20:04 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/20 20:50:03 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_simple(int keycode, t_fdf *map)
{
	if (keycode == 14)
	{
		if (map->rotate_smpl < 2)
			map->rotate_smpl += 0.025;
		else
			map->rotate_smpl = 0.025;
	}
	map->angle = M_PI * map->rotate_smpl;
	printf("KEY = %d | ANGLE = %f | PI = %f\n", keycode, map->angle, M_PI);
}

// e -> 14
// q -> 12
