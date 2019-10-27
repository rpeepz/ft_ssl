/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:35:44 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/25 17:43:48 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		abs(int value)
{
	return (value < 0 ? -value : value);
}

double	abs_double(double value)
{
	return (value < 0 ? -value : value);
}
