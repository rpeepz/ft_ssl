/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipewrench.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:27:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:31:14 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		teflon_tape(va_list ap)
{
	char	**p_string;
	int		i;
	int		freed;

	i = 0;
	freed = 0;
	p_string = va_arg(ap, char **);
	while (p_string[i])
		i++;
	while (freed < i && p_string[freed])
	{
		free(p_string[freed++]);
	}
	free(p_string);
	return (i + 1);
}

static int		screwdriver(va_list ap)
{
	int		**p_ints;
	int		i;
	int		freed;

	i = 0;
	freed = 0;
	p_ints = va_arg(ap, int **);
	while (p_ints[i])
		i++;
	while (freed < i && p_ints[freed])
	{
		free(p_ints[freed++]);
	}
	free(p_ints);
	return (i + 1);
}

static int		plunger(va_list ap, int depth, char sig)
{
	if (depth > 2)
		return (1);
	if (sig == 's')
	{
		if (depth > 1)
			return (teflon_tape(ap));
		else
			free(va_arg(ap, char*));
	}
	if (sig == 'i')
	{
		if (depth > 1)
			return (screwdriver(ap));
		else
			free(va_arg(ap, int*));
	}
	return (depth);
}

/*
**	if (ft_isdigit(**str))
**	{
**		x = ft_atoi(*str);
**	}
*/

static int		pipe_cutter(char **str, va_list ap)
{
	int		pointer_depth;
	int		freed;

	pointer_depth = 0;
	while (**str == PIPE_KEY)
	{
		(*str)++;
		pointer_depth += 1;
	}
	freed = 0;
	if (**str)
	{
		freed += plunger(ap, pointer_depth, **str);
		(*str)++;
	}
	return (freed);
}

int				ft_pipewrench(char *str, ...)
{
	int		freed;
	va_list ap;

	freed = 0;
	va_start(ap, str);
	while (*str && freed >= 0)
	{
		if (*str != PIPE_KEY)
		{
			freed = -1;
			break ;
		}
		else
		{
			freed += pipe_cutter(&str, ap);
			if (freed == 0)
			{
				write(1, "\nusage: ft_pipewren", 19);
				write(1, "ch(const char * res", 19);
				write(1, "trict format, ...)\n", 19);
			}
		}
	}
	va_end(ap);
	return (freed);
}
