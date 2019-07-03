/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:00:05 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/29 05:22:37 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strchri(const char *s, int c)
{
	int		i;
	int		z;

	i = -1;
	z = 0;
	while (s[++i])
	{
		if (s[i] == (char)c)
			z = i;
	}
	return (z);
}
