/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:12:20 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/16 16:30:15 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
 
static void	print_cam_properties(t_env *env, void *win, t_cam *cam)
{
	t_vec	cam_prop;

	cam_prop[0] = cam->fov;
	cam_prop[1] = cam->aperture;
	cam_prop[2] = 1 / (cam->aperture ? cam->aperture : 1);

	if (++env->point > -1 && env->point < 43)
		mlx_string_put(env->ren.mlx, win, 10, env->point * 20, 0xff8cff,
			cam->name);
	if (++env->point > -1 && env->point < 43)
		mlx_string_put(env->ren.mlx, win, 40, env->point * 20, 0x886611,
			"Camera");
	print_vector(env, win, "O", cam->org);
	print_vector(env, win, "R", cam->rot);
	print_vector(env, win, "P", cam_prop);
}

static void	print_obj_properties(t_env *env, void *win, t_obj *obj)
{
	char *type;

	if (obj->type == obj_cone)
		type = "Cone";
	else if (obj->type == obj_cylinder)
		type = "Cylinder";
	else if (obj->type == obj_plane)
		type = "Plane";
	else if (obj->type == obj_polygon)
		type = "Polygon";
	else if (obj->type == obj_sphere)
		type = "Sphere";
	else
		type = "Invalid Type!";
	if (++env->point > -1 && env->point < 43)
		mlx_string_put(env->ren.mlx, win, 10, env->point * 20, 0x8cff00,
			obj->name);
	if (++env->point > -1 && env->point < 43)
		mlx_string_put(env->ren.mlx, win, 40, env->point * 20, 0x886611,
			type);
	print_vector(env, win, "O", obj->org);
	print_vector(env, win, "R", obj->rot);
	print_vector(env, win, "S", obj->scale);
	print_vector(env, win, "C", obj->surface_colour);
	print_vector(env, win, "SP_C", obj->specular_colour);
}

void	print_lig_properties(t_env *env, void *win, t_lig *lig)
{
	char *type;

	if (lig->type == light_directional)
		type = "Directional Light";
	else if (lig->type == light_point)
		type = "Point Light";
	else
		type = "Invalid Type!";
	if (++env->point > -1 && env->point < 43)
		mlx_string_put(env->ren.mlx, win, 10, env->point * 20, 0xff8c00,
			lig->name);
	if (++env->point > -1 && env->point < 43)
		mlx_string_put(env->ren.mlx, win, 40, env->point * 20, 0x886611, type);
	type = ft_strjoin_n_free(ft_strdup("Intesity: "), ft_dtoa(lig->intensity, 3));
	mlx_string_put(env->ren.mlx, win, 40, ++env->point * 20, 0xcccccc,
		type);
	free(type);
	print_vector(env, win, "O", lig->org);
	print_vector(env, win, "C", lig->col);
}

static void	print_properties(void *win, t_env *env)
{
	t_list	*cur;

	cur = env->scene.cam;
	env->point = env->point_start;
	while (cur || (++env->point < env->point_start))
	{
		print_cam_properties(env, win, cur->content);
		cur = cur->next;
	}
	cur = env->scene.lig;
	while (cur || (++env->point < env->point_start))
	{
		print_lig_properties(env, win, cur->content);
		cur = cur->next;
	}
	cur = env->scene.obj;
	while (cur)
	{
		print_obj_properties(env, win, cur->content);
		cur = cur->next;
	}
	mlx_string_put(env->ren.mlx, win, 20, 873, 0x777777,
		"Ibotha    Jdorner    Jwolf");
}

void		properties(t_env *env)
{
	t_col		col;
	t_xy		start[2];
	t_win		*win;

	start[0][0] = 0;
	start[0][1] = 0;
	start[1][0] = 300;
	start[1][1] = 900;
	FILLCOL(col, 25, 25, 25, 255);
	draw_box(start[0], start[1], col, PROP_BACK);
	start[0][1] = 870;
	FILLCOL(col, 70, 25, 25, 255);
	draw_box(start[0], start[1], col, PROP_BACK);
	start[1][1] = 870;
	FILLCOL(col, 0, 0, 0, 255);
	draw_line(start[0], start[1], col, PROP_BACK);
	present_img(&env->ren, PROP_WIN, PROP_BACK);
	win = PROP_WIN;
	if (win->keys[up] || win->keys[down])
		env->point_start += (win->keys[up] ? 0.5 : -0.5);
	if (env->point_start > -1)
		env->point_start = -1;
	if (win && win->win)
		print_properties(win->win, env);
}
