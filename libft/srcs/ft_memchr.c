/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:38:24 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:09:45 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	asc;
	size_t			i;

	str = (unsigned char*)s;
	asc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (asc == str[i])
			return (&str[i]);
		i++;
	}
	return (NULL);
}
