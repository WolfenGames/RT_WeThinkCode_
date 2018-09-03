/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:57:37 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/03 17:09:20 by jwolf            ###   ########.fr       */
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


void	end_read(int flag, char *line, char *tmp
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

void	create_scene(int ac, char **av, t_scene *scene)
{
	int		fd;

	ft_bzero(scene, sizeof(t_scene));
	if (ac != 2)
		exit(EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	do_read(fd, scene);
	close(fd);
}
	if (flag)
		die("Invalid XML");
	ft_memdel((void **)&line);
	ft_memdel((void **)&tmp);
	close(fd);

	//Test scene parameters comment out when ready
	t_obj	newobj;
	t_cam	newcam;
	t_lig	newlig;

	ft_bzero(&newcam, sizeof(t_cam));
	ft_bzero(&newobj, sizeof(t_obj));
	ft_bzero(&newlig, sizeof(t_lig));

	//Camera Initialization
	newcam.name = ft_strdup("The all seeing eye!");
	newcam.fov = 35.0;
	FILLVEC(newcam.org, 5, 5, 40, 0);
	FILLVEC(newcam.rot, 0, 0, 0, 0);
	newcam.aperture = 1;
	ft_lstadd(&scene->cam, ft_lstnew(&newcam, sizeof(t_cam)));
	scene->c_cam = scene->cam->content;

	//Light Initialization
	newlig.name = ft_strdup("Gandalf the light");
	FILLVEC(newlig.col, 255, 170, 170, 255);
	FILLVEC(newlig.org, 20, 20, 0, 0);
	newlig.intensity = 500;
	newlig.type = light_point;
	ft_lstadd(&scene->lig, ft_lstnew(&newlig, sizeof(t_lig)));
	newlig.name = ft_strdup("Vigin");
	FILLVEC(newlig.col, 170, 170, 255, 255);
	FILLVEC(newlig.org, -20, 20, 0, 0);
	newlig.intensity = 500;
	newlig.type = light_point;
	ft_lstadd(&scene->lig, ft_lstnew(&newlig, sizeof(t_lig)));

	//Object Initialization
	newobj.name = ft_strdup("Palantir");
	newobj.type = obj_sphere;
	newobj.albedo = 0.18;
	newobj.tex_index = add_img_xpm(REN, "Textures/earth.xpm", 0, 0);
	FILLVEC(newobj.scale, 1, 1, 1, 0);
	FILLVEC(newobj.surface_colour, 255, 255, 255, 255);
	newobj.radius = 1;
	newobj.get_norm = sphere_getnorm;
	newobj.get_intersect = sphere_intersect;
	newobj.get_surface_col = sphere_surface_col;
	FILLVEC(newobj.tex_scale, 1, 1, 0, 0);
	ft_lstadd(&scene->obj, ft_lstnew(&newobj, sizeof(t_obj)));

	newobj.tex_index = 0;
	newobj.name = ft_strdup("X");
	FILLVEC(newobj.org, 10, 0, 0, 0);
	FILLVEC(newobj.rot, 0, -90, 0, 0);
	FILLVEC(newobj.surface_colour, 255, 170, 170, 255);
	newobj.type = obj_cone;
	newobj.get_norm = cone_getnorm;
	newobj.get_intersect = cone_intersect;
	newobj.get_surface_col = cone_surface_col;
	ft_lstadd(&scene->obj, ft_lstnew(&newobj, sizeof(t_obj)));

	newobj.name = ft_strdup("Y");
	FILLVEC(newobj.org, 0, 10, 0, 0);
	FILLVEC(newobj.surface_colour, 170, 255, 170, 255);
	ft_lstadd(&scene->obj, ft_lstnew(&newobj, sizeof(t_obj)));

	newobj.name = ft_strdup("Z");
	FILLVEC(newobj.org, 0, 0, 10, 0);
	FILLVEC(newobj.surface_colour, 170, 170, 255, 255);
	ft_lstadd(&scene->obj, ft_lstnew(&newobj, sizeof(t_obj)));
}
