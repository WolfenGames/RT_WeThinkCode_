/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@student.wethinkcode.co.za>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:49:34 by jwolf             #+#    #+#             */
/*   Updated: 2019/06/19 15:12:49 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

static void		parse_list_good(t_list *lst, t_env *env, char *name, int ci[3])
{
	t_obj			template;
	t_obj			*bob;
	t_list			*temp_list;

	ft_bzero(&template, sizeof(t_obj));
	if (!(bob = the_good_search_name(&env->scene, name)))
	{
		lst = lst->next;
		ft_lstadd(&env->scene.obj, ft_lstnew(&template, sizeof(t_obj)));
		bob = env->scene.obj->content;
		temp_list = lst;
		if (malloc_obj_info(&lst, bob))
			parse_info(temp_list, bob, name, ci);
		else
			die("[OBJ_PARSE_ERR]");
		ci[0] += bob->n_v_point;
		ci[1] += bob->n_v_normal;
		ci[2] += bob->n_v_t_coord;
	}
}

void			parse_list(t_list *lst, t_env *env)
{
	char			*name;
	int				ci[3];

	ft_bzero(ci, sizeof(int) * 3);
	while (lst)
	{
		if ((name = object_name_zone(lst)) != NULL)
		{
			parse_list_good(lst, env, name, ci);
		}
		else if (lst)
			lst = lst->next;
	}
}
