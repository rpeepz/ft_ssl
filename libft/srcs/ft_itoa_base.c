/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:44:14 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 16:27:11 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static const char	g_base[] = "0123456789ABCDEF";

char	*ft_itoa_base(int n, int base)
{
	int		tmp;
	int		len;
	char	*str;

	IF_RETURN((n == -2147483648), ft_strdup("-2147483648"));
	IF_THEN(n < 0, n *= -1);
	tmp = n;
	len = 1;
	while (tmp /= base)
		len++;
	tmp = n;
	IF_THEN(base == 10, len += 1);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		str[len] = g_base[(tmp % base)];
		tmp /= base;
	}
	if (n < 0 && base == 10)
		str[0] = '-';
	return (str);
}

char	*ft_uitoa_base(unsigned int n, int base)
{
	unsigned int	tmp;
	int				len;
	char			*str;

	tmp = n;
	len = 1;
	while (tmp /= base)
		len++;
	tmp = n;
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		str[len] = g_base[(tmp % base)];
		tmp /= base;
	}
	return (str);
}
