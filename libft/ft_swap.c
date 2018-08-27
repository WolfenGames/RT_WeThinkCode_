/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 11:06:11 by ibotha            #+#    #+#             */
/*   Updated: 2018/07/13 09:30:16 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	void	*temp;

	temp = malloc(size);
	ft_memmove(temp, a, size);
	ft_memmove(a, b, size);
	ft_memmove(b, temp, size);
	free(temp);
}
