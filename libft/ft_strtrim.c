/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:53:34 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 11:33:01 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	int front;
	int back;

	if (!s)
		return (NULL);
	front = 0;
	back = ft_strlen(s) - 1;
	while (ft_iswhitespace(s[front]))
	{
		++front;
	}
	if (s[front] == '\0')
		return (ft_strdup(""));
	while (ft_iswhitespace(s[front]))
		--back;
	return (ft_strsub(s, front, back - front + 1));
}
