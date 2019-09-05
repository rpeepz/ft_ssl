/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:05:23 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/05 01:40:42 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static int		check_for_spaces(char **input, char ***av, int *ac)
{
	char		**replace;
	char		**split;
	int			i;

	if (ft_countwords(input[1], ' ') > 1)
	{
		*ac += (ft_countwords(input[1], ' ') - 1);
		replace = (char **)malloc(sizeof(*replace) * (*ac + 1));
		split = ft_strsplit(input[1], ' ');
		replace[0] = ft_strdup(input[0]);
		ft_pipewrench("-s-s", input[0], input[1]);
		free(input);
		i = -1;
		while (++i < (*ac) - 1)
		{
			replace[i + 1] = ft_strdup(split[i]);
			free(split[i]);
		}
		free(split);
		replace[*ac] = 0;
		*av = replace;
		return (1);
	}
	return (0);
}

int				get_inputs(int *ac, char ***av)
{
	char	**replace;

	*ac += 1;
	replace = malloc(sizeof(*replace) * (*ac + 1));
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

int				parse_av(char **av, t_ssl *ssl, int i, int j)
{
	if ((ssl->type > 10 && ssl->type < 20) && !av[2])
		return (ft_error(5, "base64"));
	while ((av[++i]) && av[i][0] == '-' && (j = 1))
	{
		while (av[i][j])
		{
			if (valid_flags(ssl, av[i][j]))
				return (1);
			if (ssl->type < 10 && av[i][j] == 's')
			{
				if (dash_s(av, &i, &j, ssl))
					break ;
				return (ft_error(2, av[1]));
			}
			if (ssl->type > 20 && (av[i][j] == 'p' || av[i][j] == 'k'))
			{//-p, password in ascii is the next argument//-k, key in hex is the next arguement.
				if (dash_p_or_k(av[i][j]))
					break ;
				return (ft_error(2, av[1]));
			}
			j++;
		}
	}
	av[i] ? ssl->file_index += i : 0;
	return (0);
}

int				handle_inputs(int *ac, char ***av, t_ssl *ssl)
{
	static void	(*choose[2])(char **, t_ssl *) = {
				ssl_md5, ssl_des};
	char		**pv;

	if (*ac < 2)
		if (get_inputs(ac, av))
			return (1);
	pv = *av;
	if (valid_command(pv[1], ssl))
		return (ft_error(1, pv[1]));
	if (parse_av(*(av), ssl, 1, 0))
		return (ft_error(3, pv[1]));
	if (!read_files(pv, ssl, ssl->file_index, 0))
		if (!(ssl->flag & 0x38000))
			return (1);
	choose[ssl->type < 10 ? 0 : 1](pv, ssl);
	return (1);
}
