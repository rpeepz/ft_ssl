/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 00:13:27 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/20 00:13:27 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	word_len(char const *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i])
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	if (!s || !(arr = (char **)malloc(sizeof(*arr) * ft_countwords(s, c) + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_countwords(s, c))
	{
		while (s[j] == c)
			j++;
		if (!(arr[i] = ft_strsub(s, j, word_len(&s[j], c))))
			arr[i] = NULL;
		j += (int)word_len(&s[j], c);
	}
	arr[i] = 0;
	return (arr);
}
