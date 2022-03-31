/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:21:10 by jgoldste          #+#    #+#             */
/*   Updated: 2021/12/18 12:04:19 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long long int	number;
	int						sign;

	sign = 1;
	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str != '\0' && *str >= 48 && *str <= 57)
	{
		number = number * 10 + *str - 48;
		str++;
	}
	if (sign == 1 && number >= 9223372036854775807u)
		return (-1);
	if (sign == -1 && number >= 9223372036854775807u)
		return (0);
	return (sign * number);
}
