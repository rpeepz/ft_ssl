/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:59:42 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:57:12 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int					ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		neg;

	res = 0;
	if (!str)
		return (res);
	i = 0;
	neg = 1;
	while (IS_SPACE(str[i]) || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

unsigned long long	ft_atoull(const char *str)
{
	int					i;
	unsigned long long	n;

	n = 0;
	if (!str)
		return (n);
	i = 0;
	while (IS_SPACE(str[i]) || str[i] == '\n' || str[i] == '\v')
		i++;
	while (ft_isdigit(str[i]))
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n);
}
