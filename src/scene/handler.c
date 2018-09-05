/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 07:48:27 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/05 11:30:31 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	do_da_camera(char *name, char *line, t_scene *scene)
{
	t_cam	*newcam;
	t_cam	template;

	if (!(newcam = search_cam_list(scene, name)))
	{
		ft_bzero(&template, sizeof(t_cam));
		ft_lstadd(&scene->cam, ft_lstnew(&template, sizeof(t_cam)));
		newcam = (t_cam*)scene->cam->content;
	}
	newcam->name = (newcam->name != NULL) ? newcam->name : get_name(name);
	if (match_brackets("origin", line))
		set_vec(newcam->org, ft_strsub(line, 8, ft_strlen(line) - 17));
	if (match_brackets("rotation", line))
		set_vec(newcam->rot, ft_strsub(line, 10, ft_strlen(line) - 21));
	if (match_brackets("fov", line))
		newcam->fov = ft_clamp(120, 0, ft_atod(line + 5));
	if (match_brackets("aperture", line))
		newcam->aperture = ft_clamp(1, 0.1, ft_atod((line + 10)));
	scene->c_cam = (scene->c_cam != NULL) ? scene->c_cam : scene->cam->content;
}

void	do_da_light(char *name, char *line, t_scene *scene)
{
	t_lig	*new;
	t_lig	template;

	if (!(new = search_light_list(scene, name)))
	{
		ft_bzero(&template, sizeof(t_lig));
		ft_lstadd(&scene->lig, ft_lstnew(&template, sizeof(t_lig)));
		new = (t_lig*)scene->lig->content;
	}
	new->name = (new->name != NULL) ? new->name : get_name(name);
	if (match_brackets("origin", line))
		set_vec(new->org, ft_strsub(line, 8, ft_strlen(line) - 17));
	if (match_brackets("direction", line))
		set_vec(new->dir, ft_strsub(line, 11, ft_strlen(line) - 23));
	if (match_brackets("colour", line))
		set_vec(new->col, ft_strsub(line, 8, ft_strlen(line) - 17));
	if (match_brackets("type", line))
		new->type = set_l_type(ft_strsub(line, 6, ft_strlen(line) - 13));
	if (match_brackets("intensity", line))
		new->intensity = ft_clamp(__LONG_LONG_MAX__, 0.1, ft_atod(line + 11));
}

void	do_da_object_stuff(char *name, char *line, t_obj *new, t_env *env)
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
	set_obj_params(new);
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
	do_da_object_stuff(name, line, new, env);
}

void	handle_contents(char *line, char *name, t_scene *scene, t_env *env)
{
	char	*small;
	char	*small2;

	small = ft_strmap(line, char_lower);
	small2 = ft_strmap(name, char_lower);
	if (is_line_prop(small))
	{
		if (ft_strnequ(small2, "<object", 7))
			do_da_object(name, line, scene, env);
		if (ft_strnequ(small2, "<camera", 7))
			do_da_camera(name, line, scene);
		if (ft_strnequ(small2, "<light", 6))
			do_da_light(name, line, scene);
	}
	free(small);
	free(small2);
}
