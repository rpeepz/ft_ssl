/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 06:11:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/07/16 23:14:26 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

void			read_files(int *fd, char **input, short options, int i)
{
	while (i < 16)
		options &= ~(1 << i++);
	i = 0;
	while (input[options])
	{
		opendir(input[options]);
		if (!(ft_strncmp(strerror(errno), "No such file or directory", 26)))
			ft_printf("ft_ssl: %s: %s: %s\n", input[1], input[options],
			strerror(errno));
		else
			fd[i] = open(input[options], O_RDONLY);
		options += 1;
		i += 1;
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
				IF_RETURN(ft_printf("%s '-%c'\n", O_ER, input[i][j]), 0);
			if (input[i][j] == 'p')
				mask |= 0x1000;
			else if (input[i][j] == 'q')
				mask |= 0x2000;
			else if (input[i][j] == 'r')
				mask |= 0x4000;
			else if (input[i][j] == 's')
				mask |= 0x8000;
			j++;
		}
	}
	if (mask & 0x8)
		input[0] = input[i++];
	if (input[i])
		mask += i;
	return (mask);
}

int				main(int ac, char **av)
{
	int		fd[255];
	char	*line;
	short	options;

	IF_RETURN(ac < 2, write(1, USAGE, 53));
	if (ft_strncmp(av[1], "md5", 3) && ft_strncmp(av[1], "MD5", 3) &&
		ft_strncmp(av[1], "sha256", 6) && ft_strncmp(av[1], "SHA256", 6))
		return (ft_printf("%s%s%s\n\n%s\n%s\n%s\n", ER, av[1], ROR, S, M, C));
	if ((av[2]) && !(options = parse_av(av, (short)0, 1, 0)))
		return (ft_printf("options are\n%s%s%s%s", O_P, O_Q, O_R, O_S));
	if (ac > 2)
		read_files(fd, av, options, 12);
	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		;
	}
	else
		return (1);
	return (0);
}
