/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 20:52:54 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/20 20:46:09 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"
#include <stdio.h>

static int			verify_arg(t_parse *des, char *fname, int type, int i)
{
	if ((!fname || !*fname))
	{
		type & D_VECT ? dprintf(2, "missing IV argument for -v\n") : 0;
		type & D_KEY ? dprintf(2, "missing key argument for -k\n") : 0;
		type & D_SALT ? dprintf(2, "missing salt argument for -s\n") : 0;
		return (-1);
	}
	else
	{
		while (fname[++i])
			if (!ft_isdigit(fname[i]) &&
			!(ft_toupper(fname[i]) >= 'A' && ft_toupper(fname[i]) <= 'F'))
			{
				ft_putstr_fd("non-hex digit\ninvalid hex ", 2);
				type & D_VECT ? ft_putstr_fd("iv", 2) : 0;
				type & D_KEY ? ft_putstr_fd("key", 2) : 0;
				type & D_SALT ? ft_putstr_fd("salt", 2) : 0;
				ft_putstr_fd(" value\n", 2);
				return (-type);
			}
	}
	des->args->iv = (type & D_VECT) ? ft_hextoull(fname) : des->args->iv;
	des->args->key = (type & D_KEY) ? ft_hextoull(fname) : des->args->key;
	des->args->salt = (type & D_SALT) ? ft_hextoull(fname) : des->args->salt;
	return (0);
}

static int			check_input(t_parse *des, char *arg, char *fname)
{
	if ((!ft_strcmp(arg, "v") || !ft_strcmp(arg, "-iv")) &&\
	(des->flag |= D_VECT))
		return (verify_arg(des, fname, D_VECT, -1));
	else if ((!ft_strcmp(arg, "k") || !ft_strcmp(arg, "-key")) &&\
	(des->flag |= D_KEY))
		return (verify_arg(des, fname, D_KEY, -1));
	else if ((!ft_strcmp(arg, "s") || !ft_strcmp(arg, "-salt")) &&\
	(des->flag |= D_SALT))
		return (verify_arg(des, fname, D_SALT, -1));
	else if ((!ft_strcmp(arg, "p") || !ft_strcmp(arg, "-pass")) &&\
	(des->flag |= D_PASS))
	{
		if (!fname || !*fname)
		{
			ft_putstr_fd("missing source argument for '-p'\n", 2);
			return (-1);
		}
		else
			ft_pipewrench("-s", &des->args->pass) &&\
			(des->args->pass = ft_strdup(fname));
	}
	else
		return (1);
	return (0);
}

static int			valid_arg(t_parse *des, char *arg, char *fname, int tmp)
{
	if ((des->fd_out == 1) && (!ft_strcmp(arg, "out") || !ft_strcmp(arg, "o")))
	{
		des->flag |= F_OUT;
		!fname ? dprintf(2, "missing argument for '-out'\n") : 0;
		return (!fname ? -1 : 0);
	}
	else if (!ft_strcmp(arg, "in") || !ft_strcmp(arg, "i"))
	{
		des->flag |= F_IN;
		!fname ? dprintf(2, "missing argument for '-in'\n") : 0;
		if (open_file_to_fd(&tmp, fname, 0))
			return (-1);
		close(tmp);
	}
	else if (!ft_strcmp(arg, "a") || !ft_strcmp(arg, "base64"))
		des->flag |= A_FLAG;
	else if (!ft_strcmp(arg, "e") || !ft_strcmp(arg, "-encrypt"))
		des->flag |= E_FLAG;
	else if (!ft_strcmp(arg, "d") || !ft_strcmp(arg, "-decrypt"))
		des->flag |= D_FLAG;
	else
		return (check_input(des, arg, fname));
	return (0);
}

static void			clear_arg(int *i, t_parse *des)
{
	if (des->args->pass && des->flag & D_PASS)
	{
		des->flag &= ~D_PASS;
		++(*i);
	}
	else if (des->args->key && des->flag & D_KEY)
	{
		des->flag &= ~D_KEY;
		++(*i);
	}
	else if (des->args->salt && des->flag & D_SALT)
	{
		des->flag &= ~D_SALT;
		++(*i);
	}
	else if (des->args->iv && des->flag & D_VECT)
	{
		des->flag &= ~D_VECT;
		++(*i);
	}
}

int					parse_des(char **av, t_parse *des, t_ssl *ssl, int i)
{
	while ((av[++i]))
	{
		if (av[i][0] == '-')
		{
			if ((des->mode = valid_arg(des, &av[i][1], av[i + 1], 0)))
			{
				ssl->flag = des->mode < 0 ? -42 : ssl->flag;
				if (des->mode < 0)
					ssl->flag = -42;
				return (ft_error(6, &av[i][1], ssl));
			}
			else if (des->fd_out == 1 && des->flag & F_OUT)
				open_file_to_fd((int*)&des->fd_out, av[++i], 1);
			else if ((!des->fd_in) && (des->flag & F_IN))
				open_file_to_fd((int*)&des->fd_in, av[++i], 0);
			else
				clear_arg(&i, des);
		}
		else
			return (ft_error(6, av[i], ssl));
	}
	return (0);
}
