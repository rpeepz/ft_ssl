/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:58:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:19:52 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	int		match;

	i = -1;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while ((haystack[++i]) && i < len)
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			tmp = i;
			match = 1;
			while (haystack[tmp] && needle[j] && j < len && tmp < len)
				if (haystack[tmp++] != needle[j++])
					match = 0;
			if (match && !needle[j])
				return ((char *)&haystack[i]);
		}
	}
	return (NULL);
}

/*
**	Inefficient sorting
**	if (needle[j] == '\0')
**		return ((char *)haystack);
**	k = ft_strlen(needle);
**	while ((haystack[i] || needle[j] == '\0') && (i < len))
**	{
**		if ((haystack[i] == needle[j]) && (j == k))
**			return ((char *)&haystack[i - j]);
**		while (haystack[i] != needle[j] && haystack[i] && i < len)
**			i++;
**		while (haystack[i] == needle[j] && needle[j] && i < len)
**		{
**			i++;
**			j++;
**		}
**		if (!haystack[i] && !needle[j] && len == i && j == k)
**			return ((char *)&haystack[i - j]);
**		if (haystack[i] && i < len && j == k)
**			return ((char *)&haystack[i - j]);
**		if (haystack[i] != needle[j] && j != k)
**			j = 0;
**		if (!needle[j] && !haystack[i] && i < k)
**			return ((char *)&needle[j]);
**	}
**	return (0);
*/
