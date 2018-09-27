/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 07:20:51 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/27 12:29:27 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

void	set_object_properties_two(char *line, t_obj *new, t_env *env)
{
	if (match_brackets("transparency", line))
		new->trans = ft_clamp(1, 0, ft_atod(line + 14));
	if (match_brackets("refractionindex", line))
		new->r_index = ft_max(0, ft_atod(line + 17));
	if (!new->norm && match_brackets("normalmap", line))
		set_tex(&new->norm, ft_strsub(line, 11, ft_strlen(line) - 23), env);
	if (!new->spec_map && match_brackets("specularmap", line))
		set_tex(&new->spec_map, ft_strsub(line, 13, ft_strlen(line) - 27), env);
}

void	set_object_properties_one(char *name, char *line, t_obj *new, t_env *env)
{
	new->name = (new->name != NULL) ? new->name : get_name(name);
	if (match_brackets("origin", line))
		set_vec(new->org, ft_strsub(line, 8, ft_strlen(line) - 17));
	if (match_brackets("rotation", line))
		set_vec(new->rot, ft_strsub(line, 10, ft_strlen(line) - 21));
	if (match_brackets("diffusecolour", line))
		set_vec(new->surface_colour, ft_strsub(line, 15, ft_strlen(line) - 31));
	if (match_brackets("specularcolour", line))
		set_vec(new->specular_colour, ft_strsub(line, 16,
			ft_strlen(line) - 33));
	if (match_brackets("albedo", line))
		new->albedo = ft_clamp(1, 0, ft_atod(line + 8));
	if (match_brackets("radius", line))
		new->radius = ft_clamp(__LONG_MAX__, 0.1, ft_atod(line + 8));
	if (match_brackets("type", line))
		set_object_type(ft_strsub(line, 6, ft_strlen(line) - 13), new);
	if (match_brackets("scale", line))
		set_vec(new->scale, ft_strsub(line, 7, ft_strlen(line) - 15));
	if (!new->tex && match_brackets("texture", line))
		set_tex(&new->tex, ft_strsub(line, 9, ft_strlen(line) - 19), env);
	if (match_brackets("texturescale", line))
		set_vec(new->tex_scale, ft_strsub(line, 14, ft_strlen(line) - 29));
	set_object_properties_two(line, new, env);
}

void	set_object_param(t_env *env)
{
	t_list	*cur;

	cur = env->scene.obj;
	while (cur)
	{
		set_obj_params(OBJ);
		cur = cur->next;
	}
}

void	set_object_properties(char *name, char *line, t_scene *scene, t_env *env)
{
	t_obj	*new;
	t_obj	template;

	if (!(new = search_obj_list(scene, name)))
	{
		ft_bzero(&template, sizeof(t_obj));
		ft_lstadd(&scene->obj, ft_lstnew(&template, sizeof(t_obj)));
		new = (t_obj*)scene->obj->content;
	}
	set_object_properties_one(name, line, new, env);
}

void	polygon_scale(t_env *env)
{
	t_list	*cur;
	int		i;

	cur = env->scene.obj;
	while (cur)
	{
		if (OBJ->type == obj_polygon)
		{
			i = -1;
			while (++i < OBJ->n_v_point)
				v_mult(OBJ->vertex_point[i], OBJ->scale, OBJ->vertex_point[i]);
		}
		cur = cur->next;
	}
}
