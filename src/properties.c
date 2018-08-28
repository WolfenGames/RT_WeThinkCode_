/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:12:20 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 18:13:01 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"
 
static void	print_cam_properties(t_env *env, void *win, t_cam *cam)
{
	t_vec	cam_prop;

	cam_prop[0] = cam->fov;
	cam_prop[1] = cam->aperture;
	cam_prop[2] = 1 / cam->aperture;
	mlx_string_put(env->ren.mlx, win, 10, ++env->point * 20, 0xff8cff,
		cam->name);
	mlx_string_put(env->ren.mlx, win, 40, ++env->point * 20, 0x886611,
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
	mlx_string_put(env->ren.mlx, win, 10, ++env->point * 20, 0x8cff00,
		obj->name);
	mlx_string_put(env->ren.mlx, win, 40, ++env->point * 20, 0x886611,
		type);
	print_vector(env, win, "O", obj->org);
	print_vector(env, win, "R", obj->rot);
	print_vector(env, win, "S", obj->scale);
	print_vector(env, win, "C", obj->surface_colour);
}

static void	print_lig_properties(t_env *env, void *win, t_lig *lig)
{
	char *type;

	if (lig->type == light_directional)
		type = "Directional Light";
	else if (lig->type == light_point)
		type = "Point Light";
	else
		type = "Invalid Type!";
	mlx_string_put(env->ren.mlx, win, 10, ++env->point * 20, 0xff8c00,
		lig->name);
	mlx_string_put(env->ren.mlx, win, 40, ++env->point * 20, 0x886611,
		type);
	type = ft_strjoin_n_free(ft_strdup("Intesity: "), ft_dtoa(lig->intensity));
	mlx_string_put(env->ren.mlx, win, 40, ++env->point * 20, 0xcccccc,
		type);
	print_vector(env, win, "O", lig->org);
	print_vector(env, win, "C", lig->col);
}

static void	print_properties(void *win, t_env *env)
{
	t_list	*cur;

	cur = env->scene.cam;
	env->point = -1;
	while (cur || !(++env->point))
	{
		print_cam_properties(env, win, cur->content);
		cur = cur->next;
	}
	cur = env->scene.lig;
	while (cur || !(++env->point))
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
	const t_img	*img = find_img(&env->ren, PROP_BACK);

	start[0][0] = 0;
	start[0][1] = 0;
	start[1][0] = 300;
	start[1][1] = 900;
	FILLCOL(col, 25, 25, 25, 255);
	draw_box(start[0], start[1], col, (t_img*)img);
	start[0][1] = 870;
	FILLCOL(col, 120, 0, 0, 70);
	draw_box(start[0], start[1], col, (t_img*)img);
	start[1][1] = 870;
	FILLCOL(col, 0, 0, 0, 255);
	draw_line(start[0], start[1], col, (t_img*)img);
	present_img(&env->ren, PROP_WIN, PROP_BACK);
	win = find_win(&env->ren, PROP_WIN);
	if (win)
		print_properties(win->win, env);
}
