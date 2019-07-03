/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:13:49 by rpapagna          #+#    #+#             */
/*   Updated: 2019/03/20 17:13:51 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char			*ft_strcnew(size_t len, char c)
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
