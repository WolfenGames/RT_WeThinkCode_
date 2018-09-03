/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:57:37 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/03 15:59:26 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	free_tab(char ***tab)
{
	int		i;

	i = -1;
	if (!*tab)
		return ;
	while ((*tab)[++i])
		ft_memdel((void **)&(*tab)[i]);
	ft_memdel((void**)tab);
}

void	create_scene(int ac, char **av, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*line2;
	char	*tmp;
	char	*close_tag;
	char	*name;
	char	**sp;
	int		flag = 0;
	
	ft_bzero(scene, sizeof(t_scene));
	if (ac != 2)
		exit(EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	while (get_next_line(fd, &line) > 0)
	{
		tmp = line;
		line = ft_strtrim(line);
		if (ft_strnequ(line, "<", 1) && !ft_strnequ(line, "<!", 2))
		{
			if (!flag)
			{
				line2 = ft_strdup(line);
				sp = ft_strsplit(line, ' ');
				flag = 1;
				name = ft_strsub(sp[0], 1, ft_strlen(sp[0]));
				close_tag = ft_strjoin("</", name);
				free(name);
				free_tab(&sp);
			}
			else
		 		handle_contents(line, line2, scene);
		}
		if (flag && ft_strnequ(line, close_tag, ft_strlen(close_tag)))
		{
			free(close_tag);
			free(line2);
			flag = 0;
		}
		ft_memdel((void **)&tmp);
		ft_memdel((void **)&line);
	}
	if (flag)
		die("Invalid XML");
	if (line)
		ft_memdel((void **)&line);
	if (tmp)
		ft_memdel((void **)&tmp);
	close(fd);
}