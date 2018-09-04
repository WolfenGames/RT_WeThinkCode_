/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typehandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 08:06:31 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/04 08:18:40 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_l_type	set_l_type(char *s)
{
	t_l_type	ret;

	ret = light_point;
	if (ft_strequ(s, "point"))
		ret = light_point;
	if (ft_strequ(s, "directional"))
		ret = light_directional;
	free(s);
	return (ret);	
}

t_o_type	set_o_type(char *s)
{
	t_o_type	ret;

	ret = obj_sphere;
	if (ft_strequ(s, "sphere"))
		ret = obj_sphere;
	if (ft_strequ(s, "plane"))
		ret = obj_plane;
	if (ft_strequ(s, "cone"))
		ret = obj_cone;
	if (ft_strequ(s, "cylinder"))
		ret = obj_cylinder;
	if (ft_strequ(s, "polygon"))
		ret = obj_polygon;
	free(s);
	return (ret);
}