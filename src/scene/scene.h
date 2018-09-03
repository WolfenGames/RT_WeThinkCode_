/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:33:30 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/03 11:33:39 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vectorlib.h"
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_env t_env;

typedef enum	e_l_type
{
	light_point,
	light_directional
}				t_l_type;

typedef enum	e_o_type
{
	obj_sphere,
	obj_plane,
	obj_cone,
	obj_cylinder,
	obj_polygon
}				t_o_type;

typedef struct	s_obj
{
	char		*name;
	t_vec		org;
	t_vec		rot;
	t_vec		scale;
	t_matrix	otw;
	t_matrix	wto;
	t_vec		surface_colour;
	t_vec		specular_colour;
	int			tex_index;
	double		albedo;
	double		radius;
	t_vec		tex_scale;
	t_o_type	type;
	t_list		subtract;
	t_list		intersect;
	void		(*get_norm)(t_vec norm, t_vec point, struct s_obj *obj);
	int			(*get_intersect)(t_ray *ray, struct s_obj *obj);
	void		(*get_surface_col)(struct s_obj *obj,
		t_vec c, t_vec point, t_env *env);
}				t_obj;

typedef struct	s_lig
{
	char		*name;
	t_vec		org;
	t_vec		dir;
	double		intensity;
	t_vec		col;
	t_l_type	type;
}				t_lig;

typedef struct	s_cam
{
	char		*name;
	t_vec		org;
	t_vec		rot;
	t_matrix	ctw;
	t_matrix	wtc;
	t_vec		dir;
	double		fov;
	double		aperture;
}				t_cam;

typedef struct	s_scene
{
	t_list		*obj;
	t_list		*lig;
	t_list		*cam;
	t_cam		*c_cam;
}				t_scene;

void	handle_contents(char *line, char *name, t_scene *scene);
void	free_tab(char ***tab);
void	calc_scene(t_scene *scene);

#endif