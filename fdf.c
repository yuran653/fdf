/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/03/31 23:24:38 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*map;

	map = NULL;
	if (argc == 2)
		map = validation(argv[1]);
	if (!map)
		return (0);
	ft_printf("y = [%3d]\n", map->y);
	free(map);
	return (0);
}