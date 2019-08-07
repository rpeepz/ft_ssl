/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/06 18:19:15 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void			read_files(int *fd, char **input, short options, int i)
{
	while (i < 16)
		options &= ~(1 << i++);
	i = 0;
	while (options && input[options])
	{
		opendir(input[options]);
		if (!(ft_strncmp(strerror(errno), "No such file or directory", 26)))
			ft_printf("ft_ssl: %s: %s: %s\n", input[1], input[options],
			strerror(errno));
		else
			fd[i] = open(input[options], O_RDONLY);
		i++;
		options++;
	}
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
			if (input[i][j] == 'p')
				mask |= 0x1000;
			else if (input[i][j] == 'q')
				mask |= 0x2000;
			else if (input[i][j] == 'r')
				mask |= 0x4000;
			else if (input[i][j] == 's')
				mask |= 0x8000; //do something with teh next word
			j++;
		}
	}
	return (input[i] ? mask += i : mask);
}

int				main(int ac, char **av)
{
	int		fd[255];
	char	*line;
	short	options;

	IF_RETURN(!(options = 0) && ac < 2, write(1, USAGE, 53));
	IF_RETURN((ft_strncmp(av[1], "md5", 3) && ft_strncmp(av[1], "sha256", 6)),
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n%s\n%s\n%s\n",
		av[1], S, M, C));
	if ((av[2]) && !(options = parse_av(av, 0, 1, 0)))
	{
		if (!ft_strncmp(av[1], "md5", 3) || !ft_strncmp(av[1], "MD5", 3))
			return (ft_printf("%s", USAGEMD5));
		return (ft_printf("options are\n%s%s%s%s", O_P, O_Q, O_R, O_S));
	}
	IF_THEN(!(line = NULL) && ac > 2, read_files(fd, av, options, 12));
	if ((!options || options & 0x1000) && get_next_line(0, &line) > -1)
	{
		ft_putstr(line);
		free(line);
	}
	else
		return (1);
	return (0);
}
