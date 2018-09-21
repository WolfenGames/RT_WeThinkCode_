/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:49:34 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/20 13:53:09 by ibotha           ###   ########.fr       */
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

	ft_bzero(&template, sizeof(t_obj));
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
					parse_info(temp_list, bob, name);
				else
					die("[OBJ_PARSE_ERR]");
			}
		}
		else if (lst)
			lst = lst->next;
	}
}