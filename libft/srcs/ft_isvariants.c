/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 22:27:42 by rpapagna          #+#    #+#             */
/*   Updated: 2019/02/19 22:27:45 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

int		ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}

int		ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

int		ft_isprint(int c)
{
	return (c <= 126 && c >= 32);
}

int		ft_isascii(int c)
{
	return (c <= 127 && c >= 0);
}
