/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/22 05:54:28 by rpapagna         ###   ########.fr       */
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
				IF_RETURN(ft_printf("unknown option '-%c'\n", input[i][j]), 0);
			IF_THEN(input[i][j] == 'p', mask |= 0x1000);
			IF_THEN(input[i][j] == 'q', mask |= 0x2000);
			IF_THEN(input[i][j] == 'r', mask |= 0x4000);
			if (input[i][j] == 's')
			{
				if (dash_s(input, &i, &j, &mask))
					break ;
				if (input[1][0] == 'm' ? ft_printf("%s", SFLAG, SFLAG1) : 1)
					return (0);
			}
			j++;
		}
	}
	return (input[i] ? mask += i : mask);
}

int				main(int ac, char **av)
{
	int		fd[255];
	int		i;
	char	*line;
	short	mask;

	IF_RETURN(!(mask = 0) && ac < 2, write(1, USAGE, 53));
	IF_RETURN((i = -1) && valid_hashable(av[1]),
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n%s\n%s\n%s\n",
		av[1], SC, MC, CC));
	IF_RETURN(((av[2]) && !(mask = parse_av(av, 0, 1, 0))),
		(!ft_strncmp(av[1], "md5", 3) ? ft_printf("%s", USAGEMD5) :
		ft_printf("options are\n%s%s%s%s", O_P, O_Q, O_R, O_S)));
	IF_THEN((!(line = NULL) && ac > 2), read_files(fd, av, mask, 8));
	if ((!mask || mask & 0x3000) && get_next_line(0, &line) > -1)
	{
		mask &= ~0x8000;
		hash(av[1], line, 0, !mask || mask & 0x2000 ? mask : (mask |= 0x1000));
		free(line);
		mask &= ~0x1000;
	}
	while (fd[++i])
		hash(av[1], !av[fd[i]] ? av[i + fd[i] - 1] : av[loopdown(mask, 4)],
		fd[i], mask &= ~0x8000);
	return (0);
}
