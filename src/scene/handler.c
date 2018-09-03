/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 07:48:27 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/03 16:59:20 by jwolf            ###   ########.fr       */
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

	(void)line;
	if (!(new = search_light_list(scene, name)))
	{
		ft_bzero(&template, sizeof(t_lig));
		ft_lstadd(&scene->lig, ft_lstnew(&template, sizeof(t_lig)));
		new = (t_lig*)scene->lig->content;
	}
	new->name = (new->name != NULL) ? new->name : get_name(name);
}

void	do_da_object(char *name, char *line, t_scene *scene)
{
	t_obj	*new;
	t_obj	template;

	(void)line;
	if (!(new = search_obj_list(scene, name)))
	{
		ft_bzero(&template, sizeof(t_obj));
		ft_lstadd(&scene->obj, ft_lstnew(&template, sizeof(t_obj)));
		new = (t_obj*)scene->obj->content;
	}
	new->name = (new->name != NULL) ? new->name : get_name(name);
}

void	handle_contents(char *line, char *name, t_scene *scene)
{
	char	*small;
	char	*small2;

	small = ft_strmap(line, char_lower);
	small2 = ft_strmap(name, char_lower);
	if (is_line_prop(small))
	{
		if (ft_strnequ(small2, "<object", 7))
			do_da_object(name, line, scene);
		if (ft_strnequ(small2, "<camera", 7))
			do_da_camera(name, line, scene);
		if (ft_strnequ(small2, "<light", 6))
			do_da_light(name, line, scene);
	}
	free(small);
	free(small2);
}
