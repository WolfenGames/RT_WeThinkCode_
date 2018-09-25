/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenehandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 09:01:47 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/25 10:39:28 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

char	*ft_get_filename(char *str, char delim)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	while (str[j] != delim)
		j++;
	i = 0;
	ret = ft_strnew(j);
	while (j-- > 0)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

void	set_scene_properties(char *line, t_env *env)
{
	if (match_brackets("raydepth", line))
		env->scene.raydepth = ft_atod(line + 10);
	if (match_brackets("path", line))
		env->scene.fn = ft_get_filename(line + 6, '<');
	if (match_brackets("objfilepath", line))
		set_polygon_properties(line + 13, env);
	if (match_brackets("cellshade", line))
		env->scene.cellshade = ft_atod(line + 11);
	if (match_brackets("eyewidth", line))
		env->eye_w = ft_atod(line + 10);
	if (match_brackets("ambience", line))
		set_vec(env->ambience, ft_strsub(line, 10, ft_strlen(line) - 21));
	if (match_brackets("posteffect", line))
	{
		//sepai effect number and stuff;
	}
}
