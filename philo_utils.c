/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:56:54 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/26 21:07:42 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Everything is fine
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

static int	check_overflow(long ret, int sign)
{
	long	maxint;
	long	minint;

	maxint = 2147483647;
	minint = 2147483648;
	if (sign == 1 && ret > maxint)
		return (1);
	if (sign == -1 && ret > minint)
		return (1);
	return (0);
}

static int	check_string_and_init_vars(char *s, int *i, int *sign, long *ret)
{
	if (s == NULL)
		return (1);
	*i = 0;
	while ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32)
		*i += 1;
	if (s[*i] == '\0')
		return (1);
	*sign = 1;
	*ret = 0;
	return (0);
}

int	ft_atoi(char *s)
{
	int		i;
	int		sign;
	long	ret;

	if (check_string_and_init_vars(s, &i, &sign, &ret))
		return (-1);
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = (ret * 10) + (long)(s[i] - '0');
		if (check_overflow(ret, sign))
			return (-1);
		i++;
	}
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i])
		return (-1);
	return ((int)(ret * sign));
}
