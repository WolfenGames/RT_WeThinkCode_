/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:57:37 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 18:09:32 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	create_scene(int ac, char **av, t_scene *scene)
{
	//Put your shit here.

	ft_bzero(scene, sizeof(t_scene));

	(void)scene;
	(void)ac;
	(void)av;

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
	newlig.intensity = 10;
	newlig.type = light_point;
	ft_lstadd(&scene->lig, ft_lstnew(&newlig, sizeof(t_lig)));

	//Object Initialization
	newobj.name = ft_strdup("Palantir");
	newobj.type = obj_sphere;
	FILLVEC(newobj.scale, 1, 1, 1, 0);
	FILLVEC(newobj.surface_colour, 255, 255, 255, 255);
	ft_lstadd(&scene->obj, ft_lstnew(&newobj, sizeof(t_obj)));
}