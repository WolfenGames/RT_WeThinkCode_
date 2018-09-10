/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 07:20:51 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/10 07:46:50 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	do_da_object_stuff_two(char *name, char *line, t_obj *new, t_env *env)
{
	(void)name;
	(void)env;
	if (match_brackets("transparency", line))
		new->transparency = ft_atod(line + 14);
	if (match_brackets("refractionindex", line))
		new->r_index = ft_atod(line + 17);
	set_obj_params(new);
}

void	do_da_object_stuff_one(char *name, char *line, t_obj *new, t_env *env)
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
		set_o_type(ft_strsub(line, 6, ft_strlen(line) - 13), new);
	if (match_brackets("scale", line))
		set_vec(new->scale, ft_strsub(line, 5, ft_strlen(line) - 11));
	if (match_brackets("texture", line))
		set_tex(new, ft_strsub(line, 9, ft_strlen(line) - 19), env);
	if (match_brackets("texturescale", line))
		set_vec(new->tex_scale, ft_strsub(line, 14, ft_strlen(line) - 29));
	do_da_object_stuff_two(name, line, new, env);
}

void	do_da_object(char *name, char *line, t_scene *scene, t_env *env)
{
	t_obj	*new;
	t_obj	template;

	if (!(new = search_obj_list(scene, name)))
	{
		ft_bzero(&template, sizeof(t_obj));
		ft_lstadd(&scene->obj, ft_lstnew(&template, sizeof(t_obj)));
		new = (t_obj*)scene->obj->content;
	}
	do_da_object_stuff_one(name, line, new, env);
}