/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:57:37 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/30 15:13:54 by jwolf            ###   ########.fr       */
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
	//if (*tab)
	//	ft_memdel((void **)&(*tab));
}

void	create_scene(int ac, char **av, t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));

	//Put your shit here.
	int		fd;
	char	*line;
	char	*line2;
	char	*tmp;
	char	*close_tag;
	char	*name;
	char	**sp;
	int		flag = 0;
	

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
	ft_memdel((void **)&line);
	ft_memdel((void **)&tmp);
	close(fd);

	(void)ac;
	(void)av;
	(void)scene;

	//Test scene parameters comment out when ready
	t_obj	newobj;
	t_cam	newcam;
	t_lig	newlig;

	ft_bzero(&newcam, sizeof(t_cam));
	ft_bzero(&newobj, sizeof(t_obj));
	ft_bzero(&newlig, sizeof(t_lig));

	//Camera Initialization
	newcam.name = ft_strdup("The all seeing eye!");
	newcam.fov = 80.0;
	FILLVEC(newcam.org, 0, 0, 20, 0);
	newcam.aperture = 1;
	ft_lstadd(&scene->cam, ft_lstnew(&newcam, sizeof(t_cam)));
	scene->c_cam = scene->cam->content;

	//Light Initialization
	newlig.name = ft_strdup("Gandalf the light");
	FILLVEC(newlig.col, 255, 255, 255, 255);
	FILLVEC(newlig.org, 4, 4, 4, 0);
	newlig.intensity = 1;
	newlig.type = light_point;
	ft_lstadd(&scene->lig, ft_lstnew(&newlig, sizeof(t_lig)));

	//Object Initialization
	newobj.name = ft_strdup("Palantir");
	newobj.type = obj_sphere;
	newobj.albedo = 0.18;
	FILLVEC(newobj.scale, 1, 1, 1, 0);
	FILLVEC(newobj.surface_colour, 255, 255, 255, 255);
	ft_lstadd(&scene->obj, ft_lstnew(&newobj, sizeof(t_obj)));
}