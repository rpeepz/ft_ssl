/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:29:31 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:18:33 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_intlen(int num)
{
	int		n;

	n = 1;
	while (num /= 10)
		n++;
	return (n);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str && *str)
		while (str[i])
			i++;
	return (i);
}

void	ft_striter(char *s, void (*f)(char *))
{
	int		i;

	i = 0;
	if (s && f)
		while (*(s + i))
			f(s + i++);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;

	i = -1;
	if (s && f)
		while (*(s + ++i))
			f(i, s + i);
}
