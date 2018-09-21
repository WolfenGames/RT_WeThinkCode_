/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 12:53:40 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/21 12:55:06 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	vector_print(t_env *env, void *win, t_obj *obj)
{
	t_vec	t;

	print_vector(env, win, "O", obj->org);
	print_vector(env, win, "R", obj->rot);
	print_vector(env, win, "S", obj->scale);
	print_vector(env, win, "C", obj->surface_colour);
	print_vector(env, win, "SP_C", obj->specular_colour);
	if (obj->type == obj_polygon)
	{
		FILLVEC(t, obj->n_v_point, obj->n_v_t_coord, obj->n_faces, 0);
		print_vector(env, win, "P_MEM", t);
	}
}
