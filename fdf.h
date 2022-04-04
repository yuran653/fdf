/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/05 00:12:02 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_fdf
{
	int		x;
	int		y;
	int		**z;
	int		**color;
}	t_fdf;

t_fdf	*validation(char *argv);
void	valid_file_name(char *argv);
void	calloc_arrays(t_fdf *map, char *str);
char	*get_y(t_fdf *map, int fd);
void	get_x(t_fdf *map, char *map_str);
void	get_z(t_fdf *map, char **map_split, char **str_split, int i);
int		get_color(t_fdf *map, char **str_split, int x, int y);
int		check_digit(char *arg);
int		array_len(char **array);
void	free_array(void **array);
void	free_array_2(void **array1, void **array2);
void	free_map(t_fdf *map);
void	error_common(void);
void	error_map(void);
void	error_file(char *file_name, int fd);
void	error_free_exit(void *value);
void	error_free_map_exit(t_fdf *map);
void	error_free_str_exit(t_fdf *map, char *str);
void	error_free_array_exit(t_fdf *map, void **array);
void	error_free_all_exit(t_fdf *map, void **arr1, void **arr2, int is_map);

void	check_leak(void);

#endif