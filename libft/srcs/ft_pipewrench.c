/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipewrench.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:27:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/01 22:30:37 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_pipewrench.h"

static int		teflon_tape(va_list ap)
{
	char	**p_string;
	int		freed;

	freed = 0;
	p_string = va_arg(ap, char **);
	if (!p_string || !*p_string)
		return (freed);
	while (p_string[freed])
		ft_strdel(&(p_string[freed++]));
	ft_memdel((void **)&p_string);
	return (freed + 1);
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
		ft_memdel((void **)&p_ints[freed++]);
	}
	ft_memdel((void **)&p_ints);
	return (i + 1);
}

static int		plunger(va_list ap, int depth, char sig)
{
	char	*s;
	int		*i;

	if (sig == 's')
	{
		if (depth == 2)
			return (teflon_tape(ap));
		else
		{
			s = va_arg(ap, char*);
			ft_memdel((void **)s);
		}
	}
	else if (sig == 'i')
	{
		if (depth == 2)
			return (screwdriver(ap));
		else
		{
			i = va_arg(ap, int*);
			ft_memdel((void **)i);
		}
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
		if (pointer_depth > 2)
			ft_putendl_fd("Unsupported Input", 2);
		else
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
				ft_putendl_fd("No valid pointers were freed", 2);
			}
		}
	}
	va_end(ap);
	return (freed);
}
