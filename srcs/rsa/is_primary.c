/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_primary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:49:49 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/04 23:36:00 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "rsa.h"

/*
**	int				lazy_prime(__uint64_t n, t_primary checks)
**	{
**		uint64_t	i;
**
**		ft_printf("d= %llu\n", checks.d);
**		i = 2;
**		while (i < n)
**		{
**			if (n % i == 0)
**				return (0);
**			i++;
**		}
**		return (1);
**	}
*/

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

__uint64_t		*get_a(__uint64_t n)
{
	if (n < 2047)
		return (array_make(1, 2));
	if (n < 1373653)
		return (array_make(2, 2, 3));
	if (n < 9080191)
		return (array_make(2, 31, 73));
	if (n < 25326001)
		return (array_make(3, 2, 3, 5));
	if (n < 3215031751)
		return (array_make(4, 2, 3, 5, 7));
	if (n < 4759123141)
		return (array_make(3, 2, 7, 61));
	if (n < 1122004669633)
		return (array_make(4, 2, 13, 23, 1662803));
	if (n < 2152302898747)
		return (array_make(5, 2, 3, 5, 7, 11));
	if (n < 3474749660383)
		return (array_make(6, 2, 3, 5, 7, 11, 13));
	if (n < 341550071728321)
		return (array_make(7, 2, 3, 5, 7, 11, 13, 17));
	if (n < 3825123056546413051)
		return (array_make(9, 2, 3, 5, 7, 11, 13, 17, 19, 23));
	return (array_make(12, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37));
}

static int		witness(__uint64_t n, t_primary *checks)
{
	__uint64_t	tmp;
	int			i;

	tmp = checks->r;
	i = -1;
	while (checks->a[++i] != 0)
	{
		checks->r = tmp;
		checks->x = modpow(checks->a[i], checks->d, n);
		if (checks->x == 1 || checks->x == n - 1)
		{
			ft_putchar_fd('+', 2);
			continue ;
		}
		while (checks->r - 1)
		{
			checks->x = (checks->x * checks->x) % n;
			if (checks->x == n - 1)
				break ;
			--checks->r;
		}
		IF_RETURN(!(checks->r - 1) && !(checks->a[i + 1]), 0);
	}
	ft_putchar_fd('+', 2);
	return (1);
}

/*
** n - 1 = even number
** (2 ^ r) * d = n - 1
** a * a % n = w;
** w * a % n = w <<-- repeat d - 1
*/

int				ft_is_primary(__uint64_t number, float probability)
{
	t_primary	checks;
	int			ret;

	(void)probability;
	if (number == 2 || number == 3)
		return (1);
	if (number == 1 || !(number & 0x1))
		return (0);
	checks.d = number - 1;
	checks.r = 0;
	while (!(checks.d & 0x1) && ++checks.r)
		checks.d /= 2;
	checks.a = get_a(number);
	ret = witness(number, &checks);
	free(checks.a);
	return (ret);
}
