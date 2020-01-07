/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:04:08 by rpapagna          #+#    #+#             */
/*   Updated: 2020/01/06 20:42:56 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"

int			handle_salt(t_parse des, uint64_t salt)
{
	if (des.flag & D_FLAG)
		;
	else
	{
		ft_putstr_fd("Salted__", des.fd_out);
		salt = endianflip_64bit(des.args->salt);
		write(des.fd_out, (void *)&salt, 8);
	}
	return (1);
}