/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:39:55 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/15 07:24:26 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_array_2(void **array1, void **array2)
{
	free_array(array1);
	free_array(array2);
}

void	free_map(t_fdf *map)
{
	if (map->matrix)
		free_array((void **)map->matrix);
	if (map->data)
		free(map->data);
	free(map);
}
