/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenehandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 09:01:47 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/18 08:37:48 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

char	*ft_get_filename(char *str, char delim)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i++] != delim);
	i = j;
	i = 0;
	ret = (char *)ft_memalloc(i);
	while (j-- > 0)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

void	do_da_scene(char *line, t_env *env)
{
	if (match_brackets("raydepth", line))
		env->scene.raydepth = ft_atod(line + 10);
	if (match_brackets("width", line))
		env->scene.win_w = ft_atoi(line + 7);
	if (match_brackets("height", line))
		env->scene.win_h = ft_atoi(line + 8);
	if (match_brackets("path", line))
		env->scene.fn = ft_get_filename(line + 6, '<');
}
