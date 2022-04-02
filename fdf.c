/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:27 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 07:32:54 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak()
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
	free_map(map);
	return (0);
}