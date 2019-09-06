/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:05:05 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:16:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		if (s[i++] == (char)c)
			return ((char*)&s[i]);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s) + 1;
	while (i--)
		if (s[i] == (char)c)
			return ((char*)&s[i]);
	return (NULL);
}

int		ft_strchri(const char *s, int c)
{
	size_t		i;
	int			z;

	i = 0;
	z = 0;
	if (!s)
		return (0);
	while (s[i])
		if (s[i++] == (char)c)
			return (--i);
	return (z);
}

int		ft_strrchri(const char *s, int c)
{
	size_t		i;
	int			z;

	i = 0;
	z = 0;
	if (!s)
		return (0);
	while (s[i])
		if (s[i++] == (char)c)
			z = i;
	return (z);
}
