/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:39:55 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/10 07:04:19 by jgoldste         ###   ########.fr       */
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
	t_point	*to_free;
	
	if (map->head)
	{
		int i = -1;
		while (map->head)
		{
			to_free = map->head;
			map->head = map->head->next;
			free(to_free);
			ft_printf("x = %d y = %d z = %d color = %X\n",
				map->head->x, map->head->y,map->head->z, map->head->color);
			ft_printf("FREED [%3d]\n", ++i);
		}
	}
	if (map->data)
		free(map->data);
	free(map);
}
