/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_primary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:49:49 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/12 20:08:21 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../../ft_ssl.h"

__uint64_t		*array_make(int len, ...)
{
	va_list		ap;
	__uint64_t	*a;
	int			i;

	a = malloc(sizeof(__uint64_t) * (len + 1));
	i = 0;
	va_start(ap, len);
	while (i < len)
	{
		a[i] = va_arg(ap, int);
		i++;
	}
	a[len] = 0;
	va_end(ap);
	return (a);
}

__uint64_t		*get_a(t_ftbi *n)
{
	if (ftbi_lt(n, ftbi_new_str("2047")))
		return (array_make(1, 2));
	if (ftbi_lt(n, ftbi_new_str("1373653")))
		return (array_make(2, 2, 3));
	if (ftbi_lt(n, ftbi_new_str("9080191")))
		return (array_make(2, 31, 73));
	if (ftbi_lt(n, ftbi_new_str("25326001")))
		return (array_make(3, 2, 3, 5));
	if (ftbi_lt(n, ftbi_new_str("3215031751")))
		return (array_make(4, 2, 3, 5, 7));
	if (ftbi_lt(n, ftbi_new_str("4759123141")))
		return (array_make(3, 2, 7, 61));
	if (ftbi_lt(n, ftbi_new_str("1122004669633")))
		return (array_make(4, 2, 13, 23, 1662803));
	if (ftbi_lt(n, ftbi_new_str("2152302898747")))
		return (array_make(5, 2, 3, 5, 7, 11));
	if (ftbi_lt(n, ftbi_new_str("3474749660383")))
		return (array_make(6, 2, 3, 5, 7, 11, 13));
	if (ftbi_lt(n, ftbi_new_str("341550071728321")))
		return (array_make(7, 2, 3, 5, 7, 11, 13, 17));
	if (ftbi_lt(n, ftbi_new_str("3825123056546413051")))
		return (array_make(9, 2, 3, 5, 7, 11, 13, 17, 19, 23));
	if (ftbi_lt(n, ftbi_new_str("318665857834031151167461")))
		return (array_make(12, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37));
	// if (ftbi_lt(n, ftbi_new_str("3317044064679887385961981")))
		return (array_make(13, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41));
}

/*
**	x = (num * num) % mod;
**	--exp;
**	while (exp && --exp)
**		x = (x * num) % mod;
**	
**	jmbomeyo implement below
*/

	t_ftbi *zero;
	t_ftbi *one;
	t_ftbi *two;
	t_ftbi *three;
	t_ftbi *tmp;

t_ftbi			*modpow(t_ftbi* num, t_ftbi *exp, t_ftbi *mod)
{
	t_ftbi	*x;
	t_ftbi	*d;

	d = ftbi_copy(exp);
	if (ftbi_lt(mod, two) || ftbi_is_zero(num))
	{
		if (ftbi_is_zero(mod))
			write(2, "Cannot take modpow with modulus 0\n", 34);
		return (zero);
	}
	if (ftbi_is_zero(d))
		return (one);
	x = ftbi_copy(one);
	num = ftbi_mod(num, mod);
	while (ftbi_gt(d, zero))
	{
		if (d->a[0] & 0x1){
			// write(1, "here1\n", 6);
			// x = ftbi_mod(ftbi_mul(x, num), mod);
			// ftbi_repl(&x, ftbi_mod(ftbi_mul(x, num), mod));
			ftbi_divmod(ftbi_mul(x, num), mod, &x);
			ft_printf("x %s\n", ftbi_tostr(x));
		}
		ftbi_repl(&d, ftbi_div2(d));
		ft_printf("exp = %s\n", ftbi_tostr(d));
		// write(1, "here2\n", 6);
		// num = ftbi_mod(ftbi_mul(num, num), mod);
		// ftbi_repl(&num, ftbi_mod(ftbi_mul(num, num), mod));
		ftbi_divmod(ftbi_mul(num, num), mod, &num);
		ft_printf("mod %s\n", ftbi_tostr(num));
	}
	return (x);
}

static int		witness(t_ftbi *n, t_ftbi *d, t_ftbi *r, __uint64_t *a)
{
	t_ftbi		*tmp;
	t_ftbi		*x;
	int			i;

	tmp = ftbi_copy(r);
	i = -1;
	while (a[++i] != 0)
	{
		r = tmp;
		x = modpow(ftbi_new_ullong(a[i]), d, n);
		if (ftbi_eq(x, ftbi_new_str("1")) || ftbi_eq(x, ftbi_sub(n, ftbi_new_str("1"))))
			continue ;
		while (!(ftbi_is_zero(ftbi_sub(r, ftbi_new_str("1")))))
		{
			x = ftbi_mod(ftbi_mul(x, x), n);
			if (ftbi_eq(x, ftbi_sub(n, ftbi_new_str("1"))))
				break ;
			r = ftbi_sub(r, ftbi_new_str("1"));
		}
		if (ftbi_is_zero(ftbi_sub(r, ftbi_new_str("1"))))
			return (0);
	}
	return (1);
}

/*
** n - 1 = even number
** (2 ^ r) * d = n - 1
** a * a % n = w;
** w * a % n = w <<-- repeat d - 1
*/

// int				ft_is_primary(__uint64_t number, float probability)
// {
// 	t_primary	checks;
// 	int			ret;
// 	(void)probability;
// 	if (number == 2 || number == 3)
// 		return (1);
// 	if (number == 1 || !(number & 0x1))
// 		return (0);
// 	checks.d = number - 1;
// 	checks.r = 0;
// 	while (!(checks.d & 0x1) && ++checks.r)
// 		checks.d /= 2;
// 	checks.a = get_a(number);
// 	ret = witness(number, &checks);
// 	free(checks.a);
// 	return (ret);
// }

int				ft_is_primary(t_ftbi *number, float probability)
{
	int			ret;
	t_ftbi		*d;
	t_ftbi		*r;
	__uint64_t	*a;

	zero = ftbi_new_str("0");
	one = ftbi_new_str("1");
	two = ftbi_new_str("2");
	three = ftbi_new_str("3");
	(void)probability;
	if (ftbi_eq(number, two) || ftbi_eq(number, three))
		return (1);
	if (ftbi_eq(number, one) || !(number->a[0] & 0x1))
		return (0);
	d = ftbi_sub(number, one);
	r = ftbi_copy(zero);
	while (!(d->a[0] & 0x1))
	{
		ftbi_repl(&r, ftbi_add(r, one));
		ftbi_repl(&d, ftbi_div2(d));
	}
	a = get_a(number);
	ret = witness(number, d, r, a);
	ft_memdel((void **)&a);
	return (ret);
}
