/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:47:01 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/11 18:10:32 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

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

void	generate_shadow_ray(t_ray *point, t_lig *lig, t_env *env, t_col col)
{
	t_ray	sh;
	t_obj	*obj;
	t_col	temp[1];

	make_shadow(lig, point);
	ft_memmove(&sh, point, sizeof(t_ray));
	vec_dup(lig->col, col);
	sh.len = 1;
	while (VEC3_IS(col) && sh.len > 0)
	{
		make_shadow(lig, &sh);
		if ((obj = trace(&sh, env)))
		{
			v_add(sh.org, v_multi(sh.dir, sh.len + 0.0001, sh.dir), sh.org);
			obj->get_surface_col(obj, temp[0], sh.org);
			sc_col(temp[0], obj->transparency, temp[0]);
			mask_col(col, temp[0], col);
		}
		else
			sh.len = 0;
	}
}