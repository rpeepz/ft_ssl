/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 00:13:27 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/20 00:13:27 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	has_whitespace(char *str, size_t *i, size_t *j)
{
	while (IS_SPACE(str[*i]) || str[*i] == '\n' || *i > ft_strlen(str))
		(*i)++;
	while (IS_SPACE(str[*j]) || str[*j] == '\n')
		(*j)--;
	if (*i || *j < ft_strlen(str))
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*new;
	size_t	start;
	size_t	end;
	size_t	new_len;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	if (!has_whitespace((char *)s, &start, &end))
		return (ft_strdup(s));
	new_len = (start == ft_strlen(s)) ? 0 : ft_strlen(s) - start - \
											(ft_strlen(s) - end);
	if (!(new = ft_strnew(new_len + 1)))
		return (NULL);
	ft_strncpy(new, &s[start], new_len + 1);
	return (new);
}
