/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streplace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 16:54:21 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/16 15:30:27 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_streplace(char *line, char a, char b)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == a)
			line[i] = b;
		i++;
	}
	return (line);
}
