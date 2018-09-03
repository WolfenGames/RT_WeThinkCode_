/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:55:39 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/03 13:42:09 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char *ret;

	if (!s)
		return (NULL);
	if (!(ret = ft_strnew(len)))
		return (NULL);
	ft_strncpy(ret, s + start, len);
	return (ret);
}

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	char *ret;

	ret = ft_strsub(s, start, len);
	free(s);
	return (ret);
}
