/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 15:51:18 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 13:07:07 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		del_img_elem(void *lst, size_t i)
{
	(void)i;
	free(((t_img_lst *)lst)->name);
	free(lst);
}

static void	del_img_lst(t_list *lst, t_env *env)
{
	t_img_lst	*img;
	t_list		*l;

	l = lst;
	while (l)
	{
		img = (t_img_lst *)l->content;
		del_img(REN, img->id);
		l = l->next;
	}
	ft_lstdel(&env->scene.img_list, del_img_elem);
}

static void	del_obj(t_list **objs, t_env *env)
{
	t_obj	*obj;

	if (*objs)
	{
		del_obj(&(*objs)->next, env);
		obj = (t_obj*)(*objs)->content;
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
	del_img_lst(env->scene.img_list, env);
	ft_bzero(&env->scene, sizeof(t_scene));
}
