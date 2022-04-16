/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/16 06:20:25 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./get_next_line/get_next_line.h"
# include <mlx.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# ifndef BASE16
#  define BASE16 "0123456789ABCDEF"
# endif

typedef struct s_steps
{
	float	x_step;
	float	y_step;
	int		max;
}	t_steps;

typedef struct s_point
{
	float	x;
	float	y;
	int		z;
	int		color;
}	t_point;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		non_print;
	int		print;
}	t_data;

typedef struct s_fdf
{
	t_point	**matrix;
	int		width;
	int		height;
	int		zoom;
	// int		shift_x;
	// int		shift_y;
	float	angle;
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*data;
}	t_fdf;

t_fdf	*validation(char *argv);
void	valid_file_name(char *argv);
char	*get_height(t_fdf *map, int fd);
void	get_width(t_fdf *map, char *map_str);
void	get_values(t_fdf *map, char **map_split, char **str_split, int height);
int		fill_values(t_fdf *map, char **str_split, int x, int y);
int		get_color(char *hex, int i);
int		array_len(char **array);
int		check_digit(char *arg);
int		check_hex(char hex, char *base);
void	free_array(void **array);
void	free_array_2(void **array1, void **array2);
void	free_map(t_fdf *map);
void	error_free_exit(void *value);
void	error_free_map_exit(t_fdf *map);
void	error_free_str_exit(t_fdf *map, char *str);
void	error_free_array_exit(t_fdf *map, void **array);
void	error_free_all_exit(t_fdf *map, void **arr1, void **arr2, int is_map);
void	error_common(void);
void	error_map(void);
int		error_map_return(void **array, int is_map);
void	error_file(char *file_name, int fd);

int		key_hook(int keycode, t_fdf *map);
void	draw_map(t_fdf *map);
void	error_free_map_win_exit(t_fdf *map, int err);

void	check_leak(void);

#endif
