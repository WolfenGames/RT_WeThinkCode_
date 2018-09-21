/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 07:51:39 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/21 09:27:45 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

void	set_tex(t_obj *o, char *filename, t_env *env)
{
	int		fd;
	char	*small;

	small = ft_strmap(filename, char_lower);
	if (ft_strstr(small, ".xpm") &&
		ft_strnequ(ft_strrchr(small, '.'), ".xpm", 4))
	{
		if ((fd = open(filename, O_RDONLY)) < 0)
		{
			free(filename);
			return ;
		}
		close(fd);
		o->tex = add_img_xpm(REN, filename, 0, 0);
	}
	else
		load_png(o, filename);
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

void	do_da_polygon(char *line, t_env *env)
{
	char	*path;

	path = get_path_param(line);
	read_obj_files(path, env);
	free(path);
}
