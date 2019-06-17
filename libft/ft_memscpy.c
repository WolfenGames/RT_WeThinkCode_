/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memscpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:31:53 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/21 10:59:16 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memscpy(void *str1, const void *str2, size_t n)
{
	size_t		i;
	size_t		j;
	int			*temp;
	const int	*temp2;

	n /= 4;
	i = 0;
	j = n;
	temp = (int*)str1;
	temp2 = (const int*)str2;
	while (i < n)
	{
		temp[i++] = temp2[--j];
	}
	return (str1);
}
