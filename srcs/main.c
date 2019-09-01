/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/28 05:27:34 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void			read_files(int *fd, char **input, short mask, int i)
{
	while (i < 16)
		mask &= ~(1 << i++);
	i = 0;
	while (mask && input[mask])
	{
		opendir(input[mask]);
		if (!(ft_strncmp(strerror(errno), "No such file or directory", 26)))
			ft_printf("%s: %s: %s\n", input[1], input[mask],
			strerror(errno));
		else
			fd[i] = open(input[mask], O_RDONLY);
		i++;
		mask++;
	}
	return ;
}

char			dash_s(char **input, int *i, int *j, short *mask)
{
	char	p_flag;
	int		fd[255];

	read_files(fd, input, *mask, 8);
	p_flag = 0;
	if (*mask & 0x1000)
		p_flag = 1;
	if (!(*mask & 0x4000))
		*mask |= 0x8000;
	if (input[*i][++(*j)])
	{
		hash(input[1], &input[*i][*j], *(fd) ? *(fd) : 0, (*mask &= ~0x1000));
		if (p_flag)
			*mask |= 0x1000;
		return (1);
	}
	if (input[++(*i)] && input[*i][0])
	{
		hash(input[1], &input[*i][0], *(fd) ? *fd : 0, (*mask &= ~0x1000));
		if (p_flag)
			*mask |= 0x1000;
		return (1);
	}
	return (0);
}

short			parse_av(char **input, short mask, int i, int j)
{
	while ((input[++i]) && input[i][0] == '-' && (j = 1))
	{
		while (input[i][j])
		{
			if (input[i][j] != 'p' && input[i][j] != 'q' &&
				input[i][j] != 'r' && input[i][j] != 's')
				IF_RETURN(ft_error(4, &input[i][j]), 0);
			IF_THEN(input[i][j] == 'p', mask |= 0x1000);
			IF_THEN(input[i][j] == 'q', mask |= 0x2000);
			IF_THEN(input[i][j] == 'r', mask |= 0x4000);
			if (input[i][j] == 's')
			{
				if (dash_s(input, &i, &j, &mask))
					break ;
				ft_error(2, input[1]);
				return (0);
			}
			j++;
		}
	}
	return (input[i] ? mask += i : mask);
}

static int		inputs(int *ac, char ***av)
{
	char	**replace;

	*ac += 1;
	replace = malloc(sizeof(*replace) * *ac + 1);
	replace[0] = ft_strdup(**av);
	replace[1] = ft_strdup("\0");
	while (replace[1][0] == '\n' || replace[1][0] == '\0')
	{
		ft_printf("ft_ssl> ");
		ft_strdel(&replace[1]);
		get_stdin(&(replace[1]), 0, 0, 0);
		if (!replace[1])
		{
			ft_strdel(&replace[0]);
			free(replace);
			return (1);
		}
		if (check_for_spaces(replace, av, ac))
			return (0);
	}
	replace[*ac] = 0;
	*av = replace;
	return (0);
}

int				main(int ac, char **av)
{
	int		fd[255];
	int		i;
	char	*line;
	short	mask;

	IF_RETURN(!(mask = 0) && ac < 2 && inputs(&ac, &av), 0);
	IF_RETURN((i = -1) && valid_hashable(av[1]), ft_error(1, av[1]));
	IF_RETURN(((av[2]) && !(mask = parse_av(av, 0, 1, 0))),
		ft_error(3, av[1]));
	IF_THEN(((line = "") && ac > 2), read_files(fd, av, mask, 8));
	if ((!mask || mask & 0x1000 || (!*fd && mask & 0x4000))
		&& get_stdin(&line, 0, 1, 0))
	{
		IF_THEN(!line, (line = ft_strdup("")));
		mask &= ~0x8000;
		hash(av[1], line, 0, !mask || mask & 0x2000 ? mask : (mask |= 0x1000));
		IF_THEN(ft_pipewrench("-s", line), mask &= ~0x1000);
	}
	while (fd[++i])
	{
		mask &= ~0x8000;
		hash(av[1], loopdown(mask, 4) < 3 ?
		av[fd[i] - 1] : av[loopdown(mask, 4) + i], fd[i], mask);
	}
	return (0);
}
