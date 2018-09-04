/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:57:37 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/04 13:41:12 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

char	*get_close_tag(char *line)
{
	char	*name;
	char	**sp;
	char	*close_tag;

	ft_streplace(line, '\t', ' ');
	sp = ft_strsplit(line, ' ');
	name = ft_strsub(sp[0], 1, ft_strlen(sp[0]));
	close_tag = ft_strjoin("</", name);
	free(name);
	free_tab(&sp);
	return (close_tag);
}


void	end_read(int flag, char *line, char *tmp)
{
	if (flag)
		die("Invalid XML");
	if (line)
		ft_memdel((void **)&line);
	if (tmp)
		ft_memdel((void **)&tmp);
}

int		end_line_read(int flag, char *line, char *close_tag, char *line2)
{
	if (flag && ft_strnequ(line, close_tag, ft_strlen(close_tag)))
	{
		free(close_tag);
		free(line2);
		flag = 0;
	}
	ft_memdel((void **)&line);
	return (flag);
}

void	do_read(int fd, t_scene *scene)
{
	t_read	*r;

	r = (t_read *)ft_memalloc(sizeof(t_read));
	r->flag = 0;
	while (get_next_line(fd, &r->line) > 0)
	{
		r->tmp = r->line;
		r->line = ft_strtrim(r->line);
		if (ft_strnequ(r->line, "<", 1) && !ft_strnequ(r->line, "<!", 2))
		{
			if (!r->flag)
			{
				r->line2 = ft_strdup(r->line);
				r->flag = 1;
				r->close_tag = get_close_tag(r->line);
			}
			else
				handle_contents(r->line, r->line2, scene);
		}
		r->flag = end_line_read(r->flag, r->line, r->close_tag, r->line2);
		ft_memdel((void **)&r->tmp);
	}
	end_read(r->flag, r->line, r->tmp);
	free(r);
}

void	create_scene(int ac, char **av, t_scene *scene, t_env *env)
{
	int		fd;

	(void)env;
	ft_bzero(scene, sizeof(t_scene));
	if (ac != 2)
		exit(EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	do_read(fd, scene);
	close(fd);
}
