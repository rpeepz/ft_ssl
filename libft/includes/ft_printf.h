/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:48:49 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/17 21:56:43 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

/*
**	----- ----- -----
**	MACROS
**	----- ----- -----
*/

/*
**	----- ----- -----
**	STRUCTS
**	----- ----- -----
*/

typedef struct		s_flag
{
	int				space;
	int				pound;
	int				minus;
	int				fplus;
	int				fzero;
}					t_flag;

typedef struct		s_mods
{
	t_flag			fl;
	int				width;
	int				prcsn;
	int				length;
}					t_mods;

void				set_flags(t_flag *fl, char c);
void				print_one(char **str);
int					get_type_specifier(char x);
int					get_pre_float(long double number, int ret);
int					get_undef_length(char x);

t_mods				get_mods(char **str, va_list ap);

int					convert_percent(t_mods modifiers);
int					convert_i(t_mods modifiers, va_list ap);
int					convert_c(t_mods modifiers, va_list ap);
int					convert_s(t_mods modifiers, va_list ap);
int					convert_p(t_mods modifiers, va_list ap);
int					convert_o(t_mods modifiers, va_list ap, int i);
int					convert_u(t_mods modifiers, va_list ap, int i);
int					convert_x(t_mods modifiers, va_list ap, int i);
int					convert_f(t_mods modifiers, va_list ap, int i);
int					convert_b(t_mods modifiers, va_list ap, int i);

#endif
