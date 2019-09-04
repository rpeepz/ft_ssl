/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:28:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/08/30 17:28:50 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

int				ft_error(int err, char *ex)
{
	if (err == 1)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", ex);
		ft_printf("usage: ft_ssl %scommand%s [command opts] [command args]\n\n",
		YEL, NOCOL);
		ft_printf("Supported %scommands%s:\n", YEL, NOCOL);
		ft_printf("%smd5\nsha224\t\tsha256\nsha384\t\tsha512\n%s", UWHT, NOCOL);
	}
	if (err == 2)
		ft_printf("%s: option requires an argument -- s\n", ex);
	if (err == 3 && ex[0] == 'm')
		ft_printf("%susage%s: md5 [-pqr] [-s string] [files ...]\n", YEL,
		NOCOL);
	else
	{
		if (err == 3)
			ft_printf("options are\n%s%s%s%s", O_P, O_Q, O_R, O_S);
	}
	if (err == 4)
		ft_printf("unknown option '-%c'\n", *ex);
	return (err);
}

int				check_for_spaces(char **input, char ***av, int *ac)
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
