/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 03:55:42 by jgoldste          #+#    #+#             */
/*   Updated: 2021/12/18 12:05:02 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_digit(long n)
{
	size_t	digit;

	digit = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

char	ft_put_digit(char *str, long n, int sign, size_t digits)
{
	str[digits - 1] = '\0';
	digits--;
	while (digits > 0)
	{
		str[digits - 1] = (n % 10) + 48;
		n = n / 10;
		digits--;
	}
	if (sign == 2)
		str[digits] = '-';
	return (*str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	size_t	digits;
	long	long_n;

	sign = 1;
	long_n = (long)n;
	if (long_n < 0)
	{
		sign = 2;
		long_n = long_n * -1;
	}
	digits = ft_count_digit(long_n) + sign;
	str = (char *)malloc(sizeof(char) * digits);
	if (str == NULL)
		return (NULL);
	*str = ft_put_digit(str, long_n, sign, digits);
	return (str);
}
