/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 07:48:27 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/03 10:48:01 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

char	char_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int		is_line_prop(const char *line)
{
	int		ret;

	ret = 0;
	if (ft_strnequ(line, "<origin>", 8))
		ret = 1;
	if (ft_strnequ(line, "<roation>", 9))
		ret = 1;
	if (ft_strnequ(line, "<fov>", 5))
		ret = 1;
	if (ft_strnequ(line, "<aperture>", 10))
		ret = 1;
	if (ft_strnequ(line, "<scale>", 7))
		ret = 1;
	if (ft_strnequ(line, "<diffusecolour>", 15))
		ret = 1;
	if (ft_strnequ(line , "<specularcolour>", 16))
		ret = 1;
	if (ft_strnequ(line, "<albedo>", 8))
		ret = 1;
	if (ft_strnequ(line, "<refractiveindex>", 17))
		ret = 1;
	if (ft_strnequ(line, "<glossy>", 8))
		ret = 1;
	return (ret);
}

char	*get_name(char *s)
{
	int		i;

	if (ft_strnequ(s, "<camera name=\"", 14) || ft_strnequ(s, "<object name=\"",
					14) || ft_strnequ(s, "<light name=\"", 13))
	{
		i = 14;
		while (s[i])
		{
			if (s[i] == 34)
				break ;
			i++;
		}
		return (ft_strsub(s, 14, i - 14));
	}
	return ("No Name Bob");
}

t_cam	*search_cam_list(t_scene *scene, char *name)
{
	t_list	*list;
	t_cam	*c;

	list = scene->cam;
	while (list)
	{
		c = (t_cam *)list->content;
		if (ft_strequ(c->name, get_name(name)))
			return (c);
		ft_putendl(c->name);
		list = list->next;
	}
	return (NULL);
}

/* int		match_brackets(char *string, char *line)
{
	char	*linestart;
	char	*endline;

	linestart = get_name(line);
	endline = make_end(linestart);
	if (ft_strnequ(linestart, string, ft_strlen(string)))
		if (ft_strnrequ(line, endline, ft_strlen(endline)))
			return (1);
	return (0);
} */

void	do_da_camera(char *name, char *line, t_scene *scene)
{
	t_cam	*newcam;
	t_cam	template;

	(void)line;
	if (!(newcam = search_cam_list(scene, name)))
	{
		ft_bzero(&template, sizeof(t_cam));
		ft_lstadd(&scene->cam, ft_lstnew(&template, sizeof(t_cam)));
		newcam = (t_cam*)scene->cam->content;
	}
	printf("Assigning\n");
	newcam->name = (newcam->name != NULL) ? newcam->name : get_name(name);
	if (is_fov(line))
		get_fov(newcam, line);
	if (is_rot(line))
		get_rot(newcam, line);
	if (is_ap(line))
		get_ap(newcam, line);
	newcam->fov = 80;
	FILLVEC(newcam->org, 0, 0, 40, 0);
	scene->c_cam = (scene->c_cam != NULL) ? scene->c_cam : scene->cam->content;
}

void	do_da_light(char *name, char *line, t_scene *scene)
{
	(void)name;
	(void)line;
	(void)scene;
}

void	do_da_object(char *name, char *line, t_scene *scene)
{
	(void)name;
	(void)line;
	(void)scene;
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