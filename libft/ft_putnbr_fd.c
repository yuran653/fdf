/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 23:20:03 by jgoldste          #+#    #+#             */
/*   Updated: 2021/12/18 12:05:25 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_recurs(long num, int fd)
{
	long	num_w;

	if (num > 0)
	{
		ft_recurs(num / 10, fd);
		num_w = num % 10 + 48;
		write(fd, &num_w, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (num == 0)
		write(fd, "0", 1);
	if (num > 0)
		ft_recurs(num, fd);
	if (num < 0)
	{
		write(fd, "-", 1);
		num = num * -1;
		ft_recurs(num, fd);
	}
}
