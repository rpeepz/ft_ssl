/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:47:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/28 05:30:57 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

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

int				get_stdin(char **line, char *str, int x, int i)
{
	char	buf[16];
	char	*tmp;

	while (((i = read(0, buf, 15))))
	{
		IF_THEN(!str, (str = ft_strdup("")));
		if (buf[0] == 10)
			break ;
		buf[i] = 0;
		tmp = ft_strjoin(str, buf);
		ft_strdel(&str);
		if (!x && ft_strchr(buf, 10))
		{
			i = ft_strlen(tmp);
			tmp[i - 1] = 0;
			str = ft_strdup(tmp);
			break ;
		}
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	*line = ft_strdup(str);
	ft_strdel(&str);
	IF_THEN(!x, ft_strdel(&tmp));
	return (x);
}

int				ft_error(int err, char *ex)
{
	if (err == 1)
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n%s\n",
		ex, MC);
	if (err == 2)
		ft_printf("%s%s", ex, SFLAG);
	if (err == 3 && ex[0] == 'm')
		ft_printf("%s", USAGEMD5);
	else
	{
		if (err == 3)
			ft_printf("options are\n%s%s%s%s", O_P, O_Q, O_R, O_S);
	}
	return (err);
}