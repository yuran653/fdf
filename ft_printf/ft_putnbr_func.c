/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:54:15 by jgoldste          #+#    #+#             */
/*   Updated: 2021/11/14 13:54:19 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_recurs_nbr(long long num, int *c)
{
	long long	num_write;

	if (num > 0)
	{
		ft_recurs_nbr(num / 10, c);
		num_write = num % 10 + 48;
		*c += write(1, &num_write, 1);
	}
}

void	ft_recurs_hex(unsigned long long num, const char **type, int *c)
{
	unsigned long long	num_write;
	int					type_hex;

	if (**type == 'X')
		type_hex = 55;
	if (**type == 'x' || **type == 'p')
		type_hex = 87;
	if (num > 0)
	{
		ft_recurs_hex(num / 16, type, c);
		num_write = num % 16;
		if (num_write <= 9)
			num_write = num_write + 48;
		else
			num_write = num_write + type_hex;
		*c += write(1, &num_write, 1);
	}
}

void	ft_putnbrhex_pf(long long num, const char **type, int *c)
{
	if (**type == 'd' || **type == 'i' || **type == 'u')
	{
		if (num == 0)
			*c += write(1, "0", 1);
		if (num > 0)
			ft_recurs_nbr(num, c);
		if (num < 0)
		{
			num *= -1;
			ft_recurs_nbr(num, c);
		}
	}
	if (**type == 'p')
		num = (unsigned long long)num;
	if (**type == 'x' || **type == 'X' || **type == 'p')
	{
		if (**type == 'p')
			*c += write(1, "0x", 2);
		if (num == 0 && **type != 'p')
			*c += write(1, "0", 1);
		else
			ft_recurs_hex(num, type, c);
	}
}

int	ft_nbrlen_pf(long long nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len++;
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

int	ft_hexlen_pf(unsigned long long hex)
{
	int	len;

	len = 0;
	if (hex == 0)
		len++;
	while (hex)
	{
		hex = hex / 16;
		len++;
	}
	return (len);
}
