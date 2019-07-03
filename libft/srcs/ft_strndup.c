/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:27:11 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 20:27:23 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	i;

	if (!(dup = (char *)malloc(n + 1)))
		return (NULL);
	i = -1;
	while (s1[++i] && i < n)
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}
