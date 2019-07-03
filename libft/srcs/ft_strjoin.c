/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 00:13:27 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/03 00:47:00 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(new_str = ft_strnew(s1_len + s2_len)))
		return (NULL);
	i = -1;
	while (++i < s1_len)
		new_str[i] = s1[i];
	j = -1;
	while (++j < s2_len)
		new_str[i++] = s2[j];
	return (new_str);
}

char	*str_3join(char const *s1, char const *s2, char const *s3)
{
	char	*new_str;
	size_t	i[3];
	size_t	len[3];

	if (!s1 || !s2 || !s3)
		return (NULL);
	len[0] = LEN(s1);
	len[1] = LEN(s2);
	len[2] = LEN(s3);
	if (!(new_str = ft_strnew(len[0] + len[1] + len[2])))
		return (NULL);
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (++i[0] < len[0])
		new_str[i[0]] = s1[i[0]];
	while (++i[1] < len[1])
		new_str[i[0]++] = s2[i[1]];
	while (++i[2] < len[2])
		new_str[i[0]++] = s3[i[2]];
	new_str[i[0]] = '\0';
	return (new_str);
}
