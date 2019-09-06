/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:01:13 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:16:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = (int)ft_strlen(s1);
	while (s2[i] != '\0')
		s1[j++] = s2[i++];
	s1[j] = '\0';
	return (s1);
}

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int i;
	int j;

	i = 0;
	j = (int)ft_strlen(s1);
	while (s2[i] && i < (int)n)
		s1[j++] = s2[i++];
	s1[j] = '\0';
	return (s1);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	i = ft_strlen(dst);
	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize < dst_len + 1)
		return (src_len + dstsize);
	if (dstsize > i + 1)
	{
		while (i < dstsize - 1)
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (dst_len + src_len);
}
