/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:00:06 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/03 15:00:19 by jwolf            ###   ########.fr       */
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
