/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typehandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 08:06:31 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/10 14:59:35 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "../../inc/RT.h"

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

void		set_obj_params(t_obj *o)
{
	o->get_norm = sphere_getnorm;
	o->get_intersect = sphere_intersect;
	o->get_surface_col = sphere_surface_col;
	if (o->type == obj_cone)
	{
		o->get_norm = cone_getnorm;
		o->get_intersect = cone_intersect;
		o->get_surface_col = cone_surface_col;
	}
	if (o->type == obj_plane)
	{
		o->get_norm = plane_getnorm;
		o->get_intersect = plane_intersect;
		o->get_surface_col = plane_surface_col;
	}
}

void		set_o_type(char *s, t_obj *o)
{
	if (ft_strequ(s, "sphere"))
		o->type = obj_sphere;
	if (ft_strequ(s, "plane"))
		o->type = obj_plane;
	if (ft_strequ(s, "cone"))
		o->type = obj_cone;
	if (ft_strequ(s, "cylinder"))
		o->type = obj_cylinder;
	if (ft_strequ(s, "polygon"))
		o->type = obj_polygon;
	free(s);
}
