/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:47:01 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/21 10:21:21 by jwolf            ###   ########.fr       */
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
	t_col	temp[2];

	make_shadow(lig, point);
	ft_memmove(&sh, point, sizeof(t_ray));
	set_value(sh, lig, col);
	FILLVEC(temp[0], temp[0][0], point->u, point->v, point->tri_index);
	while (VEC3_IS(col) && sh.len > 0)
	{
		make_shadow(lig, &sh);
		if ((obj = trace(&sh, env->scene.obj)))
		{
			v_add(sh.org, v_multi(sh.dir, sh.len + 0.0001, sh.dir), sh.org);
			obj->get_surface_col(obj, temp[0], sh.org);
			FILLCOL(temp[1], 255, 255, 255, 255);
			sc_col(temp[0], 1 - obj->trans, temp[0]);
			sc_col(temp[1], obj->trans, temp[1]);
			add_col(temp[0], temp[1], temp[0]);
			sc_col(temp[0], obj->trans, temp[0]);
			mask_col(col, temp[0], col);
		}
		else
			sh.len = 0;
	}
}
