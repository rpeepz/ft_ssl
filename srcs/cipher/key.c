/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 05:43:05 by rpapagna          #+#    #+#             */
/*   Updated: 2019/12/21 07:07:14 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"
#include "hash.h"
#include "standard.h"
#include <readpassphrase.h>

#define PASS_BUF 128


static const int	g_permuted_choice1[56] = {
	57, 49, 41, 33, 25, 17, 9,
	01, 58, 50, 42, 34, 26, 18,
	10, 02, 59, 51, 43, 35, 27,
	19, 11, 03, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	07, 62, 54, 46, 38, 30, 22,
	14, 06, 61, 53, 45, 37, 29,
	21, 13, 05, 28, 20, 12, 04
};

static const int	g_permuted_choice2[48] = {
	14, 17, 11, 24, 01, 05,
	03, 28, 15, 06, 21, 10,
	23, 19, 12, 04, 26, 8,
	16, 07, 27, 20, 13, 02,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

static const int	g_rotations[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

void				key_schedule(uint64_t key, uint64_t *subkey)
{
	uint32_t	left;
	uint32_t	right;
	int			i;

	key = reorder_bits(key, g_permuted_choice1, 56);
	split_bits(key, 56, &left, &right);
	i = 0;
	while (i < 16)
	{
		left = ((left << g_rotations[i]) | (left >> (28 - g_rotations[i])));
		right = ((right << g_rotations[i]) | (right >> (28 - g_rotations[i])));
		subkey[i] = join_bits(left, right, 28);
		subkey[i] = reorder_bits(subkey[i], g_permuted_choice2, 48);
		++i;
	}
}

void				key_derivation(t_des_arg *des)
{
	uint8_t		block[9];
	char		*hash;
	char		*salted;

	hash = ft_memalloc(128);
	if (!(des->spec & D_SALT))
		des->salt = genrand((1ULL << 58), UINT64_MAX);
	ft_memcpy(block, &des->salt, 8);
	salted = ft_strjoin(des->pass, (char *)block);
	md5(hash, salted);
	des->key = !(des->spec & D_KEY) ? ft_hextoull(hash) : des->key;
	des->iv = !(des->spec & D_VECT) ? ft_hextoull(hash + 16) : des->iv;
	ft_strdel(&des->pass);
	ft_strdel(&salted);
	ft_strdel(&hash);
}

/*
**	char		out[25];
**
**	ft_bzero(out, 25);
**	ft_strcat(out, "Salted__");
**	ft_strcat(out + 8, (char *)block);
**	d.flag & A_FLAG ? base64_nstr_fd((uint8_t *)out, 16, d.fd_out, 0) :\
**	ft_putstr_fd(out, d.fd_out);
**
**	Salted output
*/

char					*get_pass(t_parse des, char *cipher)
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
