/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:05:01 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:33:12 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_isupper(int c)
{
	return (c <= 'Z' && c >= 'A');
}

int		ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 32);
	return (c);
}

char	*ft_strtoupper(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}
