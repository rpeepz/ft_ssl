/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:47:06 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/22 21:32:16 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				read_files(char **av, t_ssl *ssl, int i, int j)
{
	DIR		*dir;

	if (!i)
		return (0);
	while (av[i])
	{
		dir = opendir(av[i]);
		if (!(ft_strncmp(strerror(errno), "No such file or directory", 26)))
			ft_printf("%s: %s: %s\n", av[1], av[i], strerror(errno));
		else if (dir)
			ft_printf("%s: %s: %s\n", av[1], av[i], "Is a directory");
		else
		{
			ssl->fd[j] = open(av[i], O_RDONLY);
			ssl->file_index[j] = i;
			j++;
		}
		if (dir)
			closedir(dir);
		errno = 0;
		i++;
	}
	return (j ? j : j);
}

int				get_stdin(char **line, char *str, int x, int i)
{
	char	buf[PAGESIZE + 1];
	char	*tmp;

	tmp = NULL;
	while (((i = read(0, buf, PAGESIZE))))
	{
		IF_THEN(!str, (str = ft_strdup("")));
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
	ft_strdel(&tmp);
	*line = i == 1 ? ft_strjoin(str, "\n") : ft_strdup(str);
	ft_strdel(&str);
	IF_THEN(!x && tmp && *line && *line[0] != '\n', ft_strdel(&tmp));
	return (x);
}

void			free_message(int count, uint64_t **ptr)
{
	int		i;

	i = -1;
	while (++i < count)
	{
		free(ptr[i]);
	}
}
