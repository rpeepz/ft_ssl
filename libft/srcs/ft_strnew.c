/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:55:58 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/12 12:08:51 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char	*ft_strcnew(size_t len, char c)
{
	char	*new;
	size_t	i;

	if (len)
		if (!(new = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
	i = -1;
	while (++i < len)
		new[i] = c;
	new[i] = '\0';
	return (new);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	if (!s)
		return (NULL);
	if (!(new_str = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len && *s)
		new_str[i++] = s[start++];
	return (new_str);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1) + 1;
	if (!(dup = (char *)malloc(i)))
		return (NULL);
	dup[i] = '\0';
	while (i-- > 0)
		dup[i] = s1[i];
	return (dup);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*dup;

	if (!s)
		return (NULL);
	if (!(dup = (char *)malloc(++len)))
		return (NULL);
	dup[len] = '\0';
	while (len-- > 0)
		dup[len] = s[len];
	return (dup);
}
