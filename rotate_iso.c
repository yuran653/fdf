/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_iso.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:28:00 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/22 16:08:19 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_abscissa(t_point *point, t_fdf *map)
{
	map->tmp.y = point->y * cos(map->rotate->alpha) + point->z
		* sin(map->rotate->alpha);
	point->z = -point->y * sin(map->rotate->alpha) + point->z
		* cos(map->rotate->alpha);
	point->y = map->tmp.y;
}

// void	rotate_ordinate(t_point *point, t_fdf *map)
// {
// 	map->tmp.x = point->x * cos(map->rotate->beta) + point->z
// 		* sin(map->rotate->beta);
// 	point->z = -point->x * sin(map->rotate->beta) + point->z
// 		* cos(map->rotate->beta);
// 	point->x = map->tmp.x;
// }
