/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prop_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:26:59 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/24 12:03:52 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

char	*get_prop_name_three(char *s)
{
	if (ft_strnequ((s + 1), "ambience", 8))
		return ("ambience");
	if (ft_strnequ((s + 1), "normalmap", 9))
		return ("normalmap");
	if (ft_strnequ((s + 1), "specularmap", 11))
		return ("specularmap");
	return (NULL);
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
	if (ft_strnequ((s + 1), "transparency", 12))
		return ("transparency");
	if (ft_strnequ((s + 1), "raydepth", 8))
		return ("raydepth");
	if (ft_strnequ((s + 1), "path", 4))
		return ("path");
	if (ft_strnequ((s + 1), "objfilepath", 11))
		return ("objfilepath");
	if (ft_strnequ((s + 1), "cellshade", 9))
		return ("cellshade");
	if (ft_strnequ((s + 1), "eyewidth", 8))
		return ("eyewidth");
	return(get_prop_name_three(s));
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
	if (ft_strnequ((s + 1), "refractionindex", 15))
		return ("refractionindex");
	return (get_prop_name_two(s));
}