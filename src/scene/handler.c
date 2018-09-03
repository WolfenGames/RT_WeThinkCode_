/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 07:48:27 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/03 14:36:30 by jwolf            ###   ########.fr       */
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
	if (ft_strnequ(line, "<rotation>", 9))
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

char	*get_prop_name(char *s)
{
	if (ft_strnequ((s + 1), "origin", 6))
		return ("origin");
	if (ft_strnequ((s + 1), "rotation", 8))
		return ("rotation");
	if (ft_strnequ((s + 1), "fov", 3))
		return ("fov");
	if (ft_strnequ((s + 1), "aperture", 8))
		return ("aperture");
	if (ft_strnequ((s + 1), "scale", 5))
		return ("scale");
	if (ft_strnequ((s + 1), "diffusecolour", 13))
		return ("diffusecolour");
	if (ft_strnequ((s + 1), "specularcolour", 14))
		return ("specularcolour");
	if (ft_strnequ((s + 1), "albedo", 6))
		return ("albedo");
	if (ft_strnequ((s + 1), "refractiveindex", 15))
		return ("refractiveindex");
	if (ft_strnequ((s + 1), "glossy", 6))
		return ("glossy");
	return (NULL);
}

char	*get_name(char *s)
{
	char	*name;
	char	*ret;
	int		i;

	i = 0;
	if (ft_strnequ(s, "<camera", 7) || ft_strnequ(s, "<object", 7) ||
		ft_strnequ(s, "<light", 6))
	{
		name = ft_strstr(s, "name");
		while (*(name + 6 + i) != '\'')
			i++;
		ret = ft_strnew(i);
		i = -1;
		while (*(name + 6 + i) != '\'')
		{
			ret[i] = *(name + 6 + i);
			i++;
		}
		return (ret);
	}
	else
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
		list = list->next;
	}
	return (NULL);
}

char	*make_end(char *str)
{
	int		i;
	int		j;
	int		l;
	char	*ret;

	l = ft_strlen(str);
	j = 2;
	ret = ft_strnew(l + 3);
	ret[0] = '<';
	ret[1] = '/';
	i = 0;
	while (j < l + 2)
		ret[j++] = str[i++];
	ret[j] = '>';
	return (ret);
}

int		match_brackets(char *string, char *line)
{
	char	*linestart;
	char	*endline;
	int		ret;

	linestart = get_prop_name(line);
	endline = make_end(linestart);
	ret = (ft_strnequ(linestart, string, ft_strlen(string)) && 
		ft_strnrequ(line, endline, ft_strlen(endline))) ? 1 : 0;
	free(endline);
	return (ret);
}

void	set_vec(t_vec vec, char *linesub)
{
	vec_from_str(vec, linesub);
	free(linesub);
}

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