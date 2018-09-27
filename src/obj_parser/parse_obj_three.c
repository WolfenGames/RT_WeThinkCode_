/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:49:34 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/26 15:46:22 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void			parse_list(t_list *lst, t_env *env)
{
	t_obj			template;
	t_obj			*bob;
	t_list			*temp_list;
	char			*name;
	int				cur_index[3];

	ft_bzero(&template, sizeof(t_obj));
	ft_bzero(cur_index, sizeof(int) * 3);
	while (lst)
	{
		if ((name = object_name_zone(lst)) != NULL)
		{
			if (!(bob = the_good_search_name(&env->scene, name)))
			{
				lst = lst->next;
				ft_lstadd(&env->scene.obj, ft_lstnew(&template, sizeof(t_obj)));
				bob = env->scene.obj->content;
				temp_list = lst;
				if (malloc_obj_info(&lst, bob))
					parse_info(temp_list, bob, name, cur_index);
				else
					die("[OBJ_PARSE_ERR]");
				cur_index[0] += bob->n_v_point;
				cur_index[1] += bob->n_v_normal;
				cur_index[2] += bob->n_v_t_coord;
			}
		}
		else if (lst)
			lst = lst->next;
	}
}
