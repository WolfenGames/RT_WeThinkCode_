/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 14:58:08 by jwolf             #+#    #+#             */
/*   Updated: 2019/07/04 11:17:31 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** similar to get_prop_name, this makes sure the initial part of the line
** matches.
*/

int		is_line_prop(const char *line)
{
	return (ft_strnequ(line, "<origin>", 8) ||
		ft_strnequ(line, "<rotation>", 10) ||
		ft_strnequ(line, "<fov>", 5) || ft_strnequ(line, "<aperture>", 10) ||
		ft_strnequ(line, "<scale>", 7) || ft_strnequ(line, "<albedo>", 8) ||
		ft_strnequ(line, "<diffusecolour>", 15) ||
		ft_strnequ(line, "<specularcolour>", 16) ||
		ft_strnequ(line, "<type>", 6) || ft_strnequ(line, "<direction>", 11) ||
		ft_strnequ(line, "<intensity>", 11) ||
		ft_strnequ(line, "<radius>", 8) || ft_strnequ(line, "<colour>", 8) ||
		ft_strnequ(line, "<texture>", 9) ||
		ft_strnequ(line, "<cellshade>", 11) ||
		ft_strnequ(line, "<texturescale>", 14) ||
		ft_strnequ(line, "<refractionindex>", 17) ||
		ft_strnequ(line, "<transparency>", 14) ||
		ft_strnequ(line, "<raydepth>", 10) ||
		ft_strnequ(line, "<eyewidth>", 10) ||
		ft_strnequ(line, "<ambience>", 10) ||
		ft_strnequ(line, "<path>", 6) ||
		ft_strnequ(line, "<objfilepath>", 13) ||
		ft_strnequ(line, "<normalmap>", 11) ||
		ft_strnequ(line, "<specularmap>", 13));
}

/*
** This gets the name of our HEAD object
*/

char	*get_name(char *s)
{
	char	*name;
	char	*ret;
	int		i;

	i = 0;
	if (ft_strlen(s) > 0)
	{
		ft_streplace(s, '\"', '\'');
		if (ft_strnequ(s, "<camera", 7) || ft_strnequ(s, "<object", 7) ||
			ft_strnequ(s, "<light", 6) || ft_strnequ(s, "<polygon", 8))
		{
			if ((name = ft_strstr(s, "name='")))
			{
				while (*(name + 6 + i) != '\'')
					i++;
				ret = ft_strnew(i);
				i = -1;
				while (*(name + 6 + ++i) != '\'')
					ret[i] = *(name + 6 + i);
				return (ret);
			}
		}
	}
	return (ft_strdup("No Name Bob"));
}
