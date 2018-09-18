/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 07:51:39 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/18 14:44:48 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

void	set_tex(t_obj *o, char *filename, t_env *env)
{
	int		fd;

	if (ft_strstr(filename, ".xpm") &&
		ft_strnequ(ft_strrchr(filename, '.'), ".xpm", 4))
	{
		if ((fd = open(filename, O_RDONLY)) < 0)
		{
			free(filename);
			return ;
		}
		close(fd);
		o->tex = add_img_xpm(REN, filename, 0, 0);
	}
	free(filename);
}

char	*get_path_param(char *line)
{
	char	*path;
	int		end;

	end = 0;
	while (line[end++] != '<');
	path = ft_strsub((const char *)line, 0, end - 1);
	path = ft_strjoin_n_free(ft_strdup("./"), path);
	return (path);
}

void	do_da_polygon(char *line, t_env *env)
{
	char	*path;

	path = get_path_param(line);
	read_obj_files(path, env);
	free(path);
}
