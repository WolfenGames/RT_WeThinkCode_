/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:55:08 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/16 15:37:59 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim_dec_part(char *dec_part)
{
	char	*ret;
	int		i;

	i = ft_strlen(dec_part) - 1;
	while (i > 0 && dec_part[i] == '0')
		i--;
	ret = ft_strsub(dec_part, 0, i + 1);
	free(dec_part);
	return (ret);
}

char		*ft_dtoa(double n, int precision)
{
	char	*ret;
	char	*dec_part;
	int		b;

	ret = ft_ltoa((long)n);
	ret = ft_strjoin_n_free(ret, ft_strdup("."));
	n -= (int)n;
	b = -1;
	while (++b < precision)
		n *= 10;
	dec_part = ft_ltoa(n);
	dec_part = trim_dec_part(dec_part);
	ret = ft_strjoin_n_free(ret, dec_part);
	return (ret);
}
