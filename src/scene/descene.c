/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 15:51:18 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/06 16:03:54 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	del_obj(t_list **objs, t_env *env)
{
	t_obj	*obj;

	if (*objs)
	{
		del_obj(&(*objs)->next, env);
		obj = (t_obj*)(*objs)->content;
		if (obj->tex)
			del_img(&env->ren, obj->tex->id);
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

void		del_scene(t_env *env)
{
	del_cam(&env->scene.cam);
	del_lig(&env->scene.lig);
	del_obj(&env->scene.obj, env);
	ft_bzero(&env->scene, sizeof(t_scene));
}