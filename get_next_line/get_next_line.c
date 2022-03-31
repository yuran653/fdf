/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:48:39 by jgoldste          #+#    #+#             */
/*   Updated: 2021/12/14 02:15:29 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_end_line(char *line, char *buff)
{
	int	count_l;
	int	count_b;
	int	count_n;

	count_l = 0;
	count_b = 0;
	if (line == NULL)
		return (NULL);
	while (line[count_l] != '\n' && line[count_l] != '\0')
		count_l++;
	if (line[count_l] == '\n')
	{
		count_l++;
		count_n = count_l;
		while (line[count_l] != '\0')
			buff[count_b++] = line[count_l++];
		line[count_n] = '\0';
		while (count_b < BUFFER_SIZE)
			buff[count_b++] = '\0';
	}
	return (line);
}

char	*get_full_line(int fd, char *line, char *buff)
{
	if (line == NULL)
		return (NULL);
	while (ft_strchr_gnl(line, '\n') == 0)
	{
		if (read(fd, buff, BUFFER_SIZE) == 0)
		{
			line = get_end_line(line, buff);
			return (line);
		}
		else if (ft_strchr_gnl(line, '\n') != 1)
			line = ft_strjoin_gnl(line, buff);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char		*line;

	line = (char *)malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (BUFFER_SIZE < 0 || read(fd, buff, 0) < 0)
	{
		free(line);
		return (NULL);
	}
	line = ft_strjoin_gnl(line, buff);
	if (!ft_strlen_gnl(line))
	{
		if (read(fd, buff, BUFFER_SIZE) == 0)
		{
			free(line);
			return (NULL);
		}
		line = ft_strjoin_gnl(line, buff);
	}
	line = get_full_line(fd, line, buff);
	line = get_end_line(line, buff);
	return (line);
}
