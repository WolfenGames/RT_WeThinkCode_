/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:47:01 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/25 11:10:14 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	make_shadow(t_lig *lig, t_ray *shadow)
{
	if (lig->type == light_directional)
	{
		v_multi(lig->dir, -1, shadow->dir);
		shadow->len = INFINITY;
	}
	if (lig->type == light_point)
	{
		v_sub(lig->org, shadow->org, shadow->dir);
		shadow->len = length(shadow->dir);
	}
	normalize(shadow->dir);
}

/*
**temp[0][3] = point->tri_index;
**temp[0][2] = point->v;
**temp[0][1] = point->u;
*/

void		set_value(t_ray sh, t_lig *lig, t_col col)
{
	vec_dup(lig->col, col);
	sh.len = 1;
}

void		generate_shadow_ray(t_ray *point, t_lig *lig, t_env *env, t_col col)
{
	t_ray	sh;
	t_obj	*obj;
	t_ray	temp;

	make_shadow(lig, point);
	ft_memmove(&sh, point, sizeof(t_ray));
	set_value(sh, lig, col);
	FILLVEC(temp.dir, temp.dir[0], point->u, point->v, point->tri_index);
	while (VEC3_IS(col) && sh.len > 0)
	{
		make_shadow(lig, &sh);
		if ((obj = trace(&sh, env->scene.obj)))
		{
			v_add(sh.org, v_multi(sh.dir, sh.len + 0.0001, sh.dir), sh.org);
			obj->get_surface_col(obj, &temp, sh.org);
			FILLCOL(temp.org, 255, 255, 255, 255);
			sc_col(temp.dir, 1 - obj->trans, temp.dir);
			sc_col(temp.org, obj->trans, temp.org);
			add_col(temp.dir, temp.org, temp.dir);
			sc_col(temp.dir, obj->trans, temp.dir);
			mask_col(col, temp.dir, col);
		}
		else
			sh.len = 0;
	}
}

void		surface_scale(t_vec o, t_obj *obj)
{
	o[0] = ABS(o[0] * obj->tex_scale[0]) - (int)(ABS(o[0] * obj->tex_scale[0]));
	o[1] = ABS(o[1] * obj->tex_scale[1]) - (int)(ABS(o[1] * obj->tex_scale[1]));
}
