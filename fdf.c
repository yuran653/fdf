/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/05 18:42:35 by jgoldste         ###   ########.fr       */
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
	int y;
	int x;
	for (y = 0; map->z[y]; y++)
	{
		ft_printf("%3d - ", y);
		for (x = 0; x < map->x; x++)
			ft_printf("%3d", map->z[y][x]);
		ft_printf("\n");		
	}
	for (y = 0; map->color[y]; y++)
	{
		ft_printf("%3d - ", y);
		for (x = 0; x < map->x; x++)
			ft_printf("%7X", map->color[y][x]);
		ft_printf("\n");		
	}
	free_map(map);
	return (0);
}