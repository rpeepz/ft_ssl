/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:49:48 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:56:34 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

# include "ft_printf.h"

/*
**	----- ----- -----
**	MACROS
**	----- ----- -----
*/

# define ADD_ONE_TO_BUFF(buf, c, n) ft_strncpy(buf, c, 1); buf++; n++;
# define ADD_TO_BUFF(buf, src, n, ln) ft_strncpy(buf, src, ln); buf+=ln; n+=ln;

/*
**	----- ----- -----
**	STRUCTS
**	----- ----- -----
*/

typedef struct		s_fl
{
	int				space;
	int				pound;
	int				minus;
	int				fplus;
	int				fzero;
}					t_fl;

typedef struct		s_mod
{
	t_fl			fl;
	int				width;
	int				prcsn;
	int				length;
	int				neg;
}					t_mod;

t_mod				get_mod(char **str, va_list ap);

int					c_to_buf(char *buf, t_mod modifiers, va_list ap);
int					i_to_buf(char *buf, t_mod modifiers, va_list ap);
int					s_to_buf(char *buf, t_mod modifiers, va_list ap);
int					u_to_buf(char *buf, t_mod modifiers, va_list ap, int i);
int					x_to_buf(char *buf, t_mod modifiers, va_list ap, int i);

int					ft_padding(char *buf, int len, t_mod mod, int nbyte);
void				left_jut(char *buf, char *num, t_mod mod, int nbyte);
#endif
