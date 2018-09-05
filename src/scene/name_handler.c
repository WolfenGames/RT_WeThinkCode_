/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 14:58:08 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/05 11:20:02 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int		is_line_prop(const char *line)
{
	return (ft_strnequ(line, "<origin>", 8) ||
		ft_strnequ(line, "<rotation>", 10) ||
		ft_strnequ(line, "<fov>", 5) || ft_strnequ(line, "<aperture>", 10) ||
		ft_strnequ(line, "<scale>", 7) ||
		ft_strnequ(line, "<diffusecolour>", 15) ||
		ft_strnequ(line, "<specularcolour>", 16) ||
		ft_strnequ(line, "<albedo>", 8) ||
		ft_strnequ(line, "<refractiveindex>", 17) ||
		ft_strnequ(line, "<type>", 6) || ft_strnequ(line, "<direction>", 11) ||
		ft_strnequ(line, "<intensity>", 11) ||
		ft_strnequ(line, "<radius>", 8) || ft_strnequ(line, "<colour>", 8) ||
		ft_strnequ(line, "<texture>", 9) ||
		ft_strnequ(line, "<texturescale>", 14));
}

char	*get_prop_name_two(char *s)
{
	if (ft_strnequ((s + 1), "type", 4))
		return ("type");
	if (ft_strnequ((s + 1), "intensity", 9))
		return ("intensity");
	if (ft_strnequ((s + 1), "radius", 6))
		return ("radius");
	if (ft_strnequ((s + 1), "texturescale", 12))
		return ("texturescale");
	if (ft_strnequ((s + 1), "texture", 7))
		return ("texture");
	return (NULL);
}

char	*get_prop_name(char *s)
{
	if (ft_strnequ((s + 1), "origin", 6))
		return ("origin");
	if (ft_strnequ((s + 1), "colour", 6))
		return ("colour");
	if (ft_strnequ((s + 1), "rotation", 8))
		return ("rotation");
	if (ft_strnequ((s + 1), "direction", 9))
		return ("direction");
	if (ft_strnequ((s + 1), "fov", 3))
		return ("fov");
	if (ft_strnequ((s + 1), "aperture", 8))
		return ("aperture");
	if (ft_strnequ((s + 1), "scale", 5))
		return ("scale");
	if (ft_strnequ((s + 1), "diffusecolour", 13))
		return ("diffusecolour");
	if (ft_strnequ((s + 1), "specularcolour", 14))
		return ("specularcolour");
	if (ft_strnequ((s + 1), "albedo", 6))
		return ("albedo");
	if (ft_strnequ((s + 1), "refractiveindex", 15))
		return ("refractiveindex");
	return (get_prop_name_two(s));
}

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
			ft_strnequ(s, "<light", 6))
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
