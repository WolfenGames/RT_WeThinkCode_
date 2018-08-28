/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:55:08 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 16:07:45 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getsize(long n)
{
	int size;

	size = 0;
	if (n < 0)
	{
		++size;
	}
	while (n != 0)
	{
		++size;
		n /= 10;
	}
	return (size);
}

static char	*mincase(void)
{
	char *ret;

	if (!(ret = ft_strnew(1)))
		return (NULL);
	else
		ret[0] = '0';
	return (ret);
}

char		*ft_ltoa(long n)
{
	int		size;
	char	*ret;

	if (n == 0)
		return (mincase());
	else
	{
		size = getsize(n);
		if (!(ret = ft_strnew(size)))
			return (NULL);
		if (n < 0)
		{
			ret[0] = '-';
			n *= -1;
		}
		while (--size >= (ret[0] == '-'))
		{
			ret[size] = n % 10 + '0';
			n /= 10;
		}
	}
	return (ret);
}
