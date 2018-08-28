/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:55:08 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 16:06:21 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_dtoa(double n)
{
	char	*ret;

	ret = ft_ltoa((long)n);
	ret = ft_strjoin_n_free(ret, ft_strdup("."));
	n -= (int)n;
	while (n - (int)n)
		n *= 10;
	ret = ft_strjoin_n_free(ret, ft_ltoa(n));
	return (ret);
}
