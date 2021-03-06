/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@student.wethinkcode.co.za>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 07:51:39 by jwolf             #+#    #+#             */
/*   Updated: 2019/06/20 08:07:42 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"
#include "parse.h"

void	try_load_png(char *small, char *filename, t_env *env, t_img **o)
{
	int		fd;

	if (ft_strstr(small, ".png") &&
		ft_strnequ(ft_strrchr(small, '.'), ".png", 4))
	{
		if ((fd = open(filename, O_RDONLY)) < 0)
			return ;
		close(fd);
		load_png(o, ft_strdup(filename), env);
	}
}

void	assign_tex(t_img *img, char *filename, t_env *env)
{
	t_img_lst	temp;

	temp.id = img->id;
	temp.name = ft_strdup(filename);
	ft_lstadd(&env->scene.img_list, ft_lstnew(&temp, sizeof(t_img_lst)));
}

void	set_tex(t_img **i, char *filename, t_env *env)
{
	char	*small;

	small = ft_strmap(filename, char_lower);
	if (!(*i = search_img_list(env, small)))
	{
		try_load_png(small, filename, env, i);
		try_load_xpm(small, filename, env, i);
		if (*i)
			assign_tex(*i, small, env);
	}
	free(small);
	free(filename);
}

char	*get_path_param(char *line)
{
	char	*path;
	int		end;

	end = 0;
	while (line[end] != '<')
		end++;
	path = ft_strsub((const char *)line, 0, end);
	path = ft_strjoin_n_free(ft_strdup("./"), path);
	return (path);
}

void	set_polygon_properties(char *line, t_env *env)
{
	char	*path;

	path = get_path_param(line);
	read_obj_files(path, env);
	free(path);
}
