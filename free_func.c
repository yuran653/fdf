/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:39:55 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 07:34:52 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_char_array_2(char **array1, char **array2)
{
	free_char_array(array1);
	free_char_array(array2);
}

void	free_int_array(int **array, int x)
{
	while (x)
		free(array[x--]);
	free(array);
}

void	free_map(t_fdf *map)
{
	if (map->z)
		free_int_array(map->z, map->x);
	free(map);
}
