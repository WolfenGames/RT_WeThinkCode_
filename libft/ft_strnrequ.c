/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrequ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:50:33 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/16 15:31:58 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strnrequ(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (n > 0 && i >= 0 && j >= 0)
	{
		if (s1[i--] != s2[j--])
			return (0);
		n--;
	}
	return (1);
}
