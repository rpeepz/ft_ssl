/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:05:39 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:20:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	int		match;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = -1;
	match = 0;
	while (haystack[++i] && !match)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			tmp = i;
			match = 1;
			while (needle[j])
				if (needle[j++] != (haystack[tmp++]))
					match = 0;
			if (match)
				return ((char *)&haystack[i]);
		}
	}
	return (NULL);
}
