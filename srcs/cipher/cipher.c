/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 22:52:45 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/20 02:33:32 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"
#include <readpassphrase.h>

#define PASS_BUF 128

char				*get_pass(t_parse des, char *cipher)
{
	char	prompt[ft_strlen(cipher) + 27 + 1];
	char	pass[PASS_BUF];
	char	pass2[PASS_BUF];
	char	*pswd;

	ft_bzero(prompt, sizeof(prompt));
	ft_strcat(prompt, "enter ");
	ft_strcat(prompt, cipher);
	ft_strcat(prompt, des.flag & D_FLAG ? " decryption" : " encryption");
	ft_strcat(prompt, " password:");
	if (!*readpassphrase(prompt, pass, PASS_BUF, 0))
		return NULL;
	ft_putstr_fd("Verifying - ", 2);
	if (!*(pswd = readpassphrase(prompt, pass2, PASS_BUF, 0)))
		return NULL;
	if (ft_strcmp(pass, pass2))
	{
		ft_putstr_fd("Verify failure\n", 2);
		return (NULL);
	}
	return (ft_strdup(pswd));
}

void				des_process(t_parse des, t_ssl *ssl, char *cipher)
{
	uint8_t		block[9];
	uint64_t	n;

	if (!des.args->pass)
		if (!(des.args->pass = get_pass(des, cipher)))
		{
			ft_putstr_fd("bad password read\n", 2);
			return ;
		}
	ft_bzero(block, 9);
	while (read(des.fd_in, block, 8) == 8)
	{
		ft_memcpy(&n, block, 8);
		ft_printf("[%llu] ", n);
		ft_memcpy(block, &n, 8);
		ft_printf("[%s]\n", block);
		ft_bzero(block, 8);
	}
	ft_memcpy(&n, block, 8);
	ft_printf("[%llu]\n", n);
	des.fd_in > 1 ? close(des.fd_in) : 0;
	des.fd_out > 1 ? close(des.fd_out) : 0;
	(void)ssl;
}
