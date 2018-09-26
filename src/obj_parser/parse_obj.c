/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 08:47:53 by jdorner           #+#    #+#             */
/*   Updated: 2018/09/26 14:59:58 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

int				recurr_count(char *str, char delim)
{
	int ret;

	ret = 0;
	while (str && *str)
	{
		if (*str == delim)
			ret++;
		++str;
	}
	return (ret);
}

void			assign_mem(t_obj *new)
{
	if (new->vertex_normal)
		free(new->vertex_normal);
	if (new->vertex_texture_coord)
		free(new->vertex_texture_coord);
	if (new->vertex_point)
		free(new->vertex_point);
	if (new->faces)
		free(new->faces);
	new->vertex_point = malloc(sizeof(t_face) * new->n_v_point);
	new->vertex_normal = malloc(sizeof(t_face) * new->n_v_normal);
	new->vertex_texture_coord = malloc(sizeof(t_face) * new->n_v_t_coord);
	new->faces = malloc(sizeof(t_face) * new->n_faces);
}

int				malloc_obj_info(t_list **lst, t_obj *new)
{
	while (*lst)
	{
		printf("M====>%s\n", (*lst)->content);
		if (ft_strstr((*lst)->content, "v "))
			new->n_v_point++;
		if (ft_strstr((*lst)->content, "vn "))
			new->n_v_normal++;
		if (ft_strstr((*lst)->content, "vt "))
			new->n_v_t_coord++;
		if (ft_strstr((*lst)->content, "f "))
			new->n_faces += recurr_count((*lst)->content, ' ') - 2;
		*lst = (*lst)->next;
		if (!*lst || ft_strstr((*lst)->content, "o ") ||
			ft_strstr((*lst)->content, "# object"))
		{
			assign_mem(new);
			return (1);
		}
	}
	return (0);
}

char			*object_name_zone(t_list *lst)
{
	if (lst && ft_strstr(lst->content, "# object"))
		return (lst->content + 9);
	if (lst && ft_strstr(lst->content, "o "))
		return (lst->content + 2);
	return (NULL);
}

t_obj			*the_good_search_name(t_scene *scene, char *name)
{
	t_list	*list;
	t_obj	*o;

	list = scene->obj;
	while (list)
	{
		o = (t_obj*)list->content;
		if (ft_strequ(o->name, name))
			return (o);
		list = list->next;
	}
	return (NULL);
}
