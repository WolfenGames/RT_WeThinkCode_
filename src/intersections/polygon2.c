/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:55:47 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 13:00:54 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define T1 (obj->faces[i][0][1] >= obj->n_v_t_coord || obj->faces[i][0][1] < 0)
#define T2 (obj->faces[i][1][1] >= obj->n_v_t_coord || obj->faces[i][1][1] < 0)
#define T3 (obj->faces[i][2][1] >= obj->n_v_t_coord || obj->faces[i][2][1] < 0)
#define P1 (obj->faces[i][0][0] >= obj->n_v_point || obj->faces[i][0][0] < 0)
#define P2 (obj->faces[i][1][0] >= obj->n_v_point || obj->faces[i][1][0] < 0)
#define P3 (obj->faces[i][2][0] >= obj->n_v_point || obj->faces[i][2][0] < 0)
#define N1 (obj->faces[i][0][2] >= obj->n_v_normal || obj->faces[i][0][2] < 0)
#define N2 (obj->faces[i][1][2] >= obj->n_v_normal || obj->faces[i][1][2] < 0)
#define N3 (obj->faces[i][2][2] >= obj->n_v_normal || obj->faces[i][2][2] < 0)
#define LEN temp[3]
#define O1 (VT(2)[1] * LEN[0] + VT(0)[1] * LEN[1] + VT(1)[1] * LEN[2])
#define O0 (VT(2)[0] * LEN[0] + VT(0)[0] * LEN[1] + VT(1)[0] * LEN[2])

void	poly_surface_col_cont(t_vec temp[4], t_obj *obj, t_ray *c, t_vec point)
{
	(void)point;
	temp[2][1] = 1 - temp[2][1];
	surface_scale(temp[2], obj);
	if (obj->spec_map)
	{
		get_p_img_col(temp[2][0], temp[2][1], obj->spec_map, c->org);
		FILLVEC(c->org,
		(c->org[0] / 255.0) * obj->specular_colour[0],
		(c->org[1] / 255.0) * obj->specular_colour[1],
		(c->org[2] / 255.0) * obj->specular_colour[2], 0);
	}
	if (obj->tex)
		get_p_img_col(temp[2][0], temp[2][1], obj->tex, c->dir);
	if (obj->norm)
		get_p_img_col(temp[2][0], temp[2][1], obj->norm, c->hold);
}
