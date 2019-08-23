/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:47:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/22 07:13:49 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

char			*ft_tolower_str(char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char			*ft_toupper_str(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

int				valid_hashable(char *input)
{
	if (!ft_strcmp(input, "md5"))
		return (0);
	else if (!ft_strcmp(input, "sha256"))
		return (0);
	else if (!ft_strcmp(input, "sha512"))
		return (0);
	else if (!ft_strcmp(input, "basic"))
		return (0);
	return (1);
}

void			mask_hashable(char *input, short *mask)
{
	if (!input)
		return ;
	if (!ft_strcmp(input, "md5"))
		*mask |= 0x100;
	else if (!ft_strcmp(input, "sha256"))
		*mask |= 0x200;
	else if (!ft_strcmp(input, "sha512"))
		*mask |= 0x400;
	else if (!ft_strcmp(input, "basic"))
		*mask |= 0x800;
}

short			loopdown(short mask, int i)
{
	while (i < 16)
		mask &= ~(1 << i++);
	return (mask);
}
