/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 15:51:18 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/25 17:46:28 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Here we handle deleting of elements of are no longer required,
*/

static void	del_obj(t_list **objs, t_env *env)
{
	t_obj	*obj;

	if (*objs)
	{
		del_obj(&(*objs)->next, env);
		obj = (t_obj*)(*objs)->content;
		if (obj->tex)
			del_img(&env->ren, obj->tex->id);
		if (obj->norm)
			del_img(&env->ren, obj->norm->id);
		if (obj->spec_map)
			del_img(&env->ren, obj->spec_map->id);
		if (obj->vertex_normal)
			free(obj->vertex_normal);
		if (obj->vertex_texture_coord)
			free(obj->vertex_texture_coord);
		if (obj->vertex_point)
			free(obj->vertex_point);
		if (obj->faces)
			free(obj->faces);
		free(obj->name);
		free(obj);
		free(*objs);
	}
}

static void	del_lig(t_list **ligs)
{
	t_lig	*lig;

	if (*ligs)
	{
		del_lig(&(*ligs)->next);
		lig = (t_lig*)(*ligs)->content;
		free(lig->name);
		free(lig);
		free(*ligs);
	}
}

static void	del_cam(t_list **cams)
{
	t_cam	*cam;

	if (*cams)
	{
		del_lig(&(*cams)->next);
		cam = (t_cam*)(*cams)->content;
		free(cam->name);
		free(cam);
		free(*cams);
	}
}

static void	del_scene_stuff(t_scene *scene)
{
	free(scene->fn);
}

void		del_scene(t_env *env)
{
	del_cam(&env->scene.cam);
	del_lig(&env->scene.lig);
	del_obj(&env->scene.obj, env);
	del_scene_stuff(&env->scene);
	ft_bzero(&env->scene, sizeof(t_scene));
}
