/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:00:06 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/27 12:49:00 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "renderer.h"
#include "rt.h"

t_cam	*search_cam_list(t_scene *scene, char *name)
{
	t_list	*list;
	t_cam	*c;
	char	*c_name;

	list = scene->cam;
	c_name = get_name(name);
	while (list)
	{
		c = (t_cam *)list->content;
		if (ft_strequ(c->name, c_name))
		{
			free(c_name);
			return (c);
		}
		list = list->next;
	}
	free(c_name);
	return (NULL);
}

t_img	*search_img_list(t_env *env, char *name)
{
	t_list		*img;
	t_img_lst	*l;

	img = env->scene.img_list;
	while (img)
	{
		l = (t_img_lst *)img->content;
		if (ft_strequ(l->name, name))
			return (find_img(REN, l->id));
		img = img->next;
	}
	return (NULL);
}

t_lig	*search_light_list(t_scene *scene, char *name)
{
	t_list	*list;
	t_lig	*l;
	char	*l_name;

	list = scene->lig;
	l_name = get_name(name);
	while (list)
	{
		l = (t_lig*)list->content;
		if (ft_strequ(l->name, l_name))
		{
			free(l_name);
			return (l);
		}
		list = list->next;
	}
	free(l_name);
	return (NULL);
}

t_obj	*search_obj_list(t_scene *scene, char *name)
{
	t_list	*list;
	t_obj	*o;
	char	*o_name;

	list = scene->obj;
	o_name = get_name(name);
	while (list)
	{
		o = (t_obj*)list->content;
		if (ft_strequ(o->name, o_name))
		{
			free(o_name);
			return (o);
		}
		list = list->next;
	}
	free(o_name);
	return (NULL);
}
