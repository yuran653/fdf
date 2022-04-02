/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:02:54 by jgoldste          #+#    #+#             */
/*   Updated: 2022/04/02 04:10:15 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_common(void)
{
	perror("\e[1;31mERROR\e[0m");
	exit(EXIT_FAILURE);
}

void	error_map(void)
{
	ft_putstr_fd("\e[1;31mERROR:\e[0m map is not valid\n", STDERR_FILENO);
	exit(0);
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

void	valid_file_name(char *argv)
{
	int		i;
	char	*fdf;
	
	fdf = ".fdf";
	i = ft_strlen(argv) - 4;
	while (argv[i])
	{
		if (*fdf++ != argv[i++])
		{
			ft_putstr_fd("\e[1;31mERROR:\e[0m file name is not valid: ",
				STDERR_FILENO);
			ft_putstr_fd(argv, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			exit(EXIT_SUCCESS);
		}
	}
}
