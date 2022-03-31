/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:02:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/01 00:46:42 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_common(void)
{
	perror("\e[1;31mERROR\e[0m");
	exit(EXIT_FAILURE);
}

void	error_malloc(void)
{
	perror("\e[1;31mERROR:\e[0m malloc allocation failure");
	exit(EXIT_FAILURE);
}

void	error_file(char *file_name, int fd)
{
	char	*tmp;
	int		rd;
	
	tmp = NULL;
	rd = read(fd, tmp, 0);
	if (rd  == -1)
		fd = -1;
	if (fd == -1)
	{
		ft_putstr_fd("\e[1;31mERROR:\e[0m ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(file_name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		if (rd  == -1)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
}

void	error_malloc_free_fdf(t_fdf *map)
{
	free(map);
	error_malloc();
}

void	error_close_free(t_fdf *map, char *str)
{
	free(map);
	free(str);
	error_common();
}
