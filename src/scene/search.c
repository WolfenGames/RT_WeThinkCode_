/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:00:06 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/03 16:59:27 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

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
