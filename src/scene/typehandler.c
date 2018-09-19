/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typehandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 08:06:31 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/19 15:19:08 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "../../inc/rt.h"

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

void		set_obj_params_two(t_obj *o)
{
	if (o->type == obj_cylinder)
	{
		o->get_norm = cylinder_getnorm;
		o->get_intersect = cylinder_intersect;
		o->get_surface_col = cylinder_surface_col;
	}
	if (o->type == obj_polygon)
	{
		o->get_norm = poly_getnorm;
		o->get_intersect = poly_intersect;
		o->get_surface_col = poly_surface_col;
	}
}

void		set_obj_params(t_obj *o)
{
	o->get_norm = sphere_getnorm;
	o->get_intersect = sphere_intersect;
	o->get_surface_col = sphere_surface_col;
	if (o->albedo == 0)
		o->albedo = 0.18;
	if (o->r_index == 0)
		o->r_index = 1;
	if (!VEC3_IS(o->scale))
		FILLVEC(o->scale, 1, 1, 1, 1);
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
	set_obj_params_two(o);
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
