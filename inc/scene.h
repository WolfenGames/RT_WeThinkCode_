/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:33:30 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/27 16:57:20 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vectorlib.h"
# include "libft.h"

typedef enum	e_l_type
{
	point,
	directional
}				t_l_type;

typedef enum	e_o_type
{
	sphere,
	plane,
	cone,
	cylinder,
	polygon
}				t_o_type;

typedef struct	s_obj
{
	t_vec		org;
	t_vec		rot;
	t_vec		scale;
	t_matrix	otw;
	t_matrix	wto;
	t_vec		surface_colour;
	t_vec		specular_colour;
	int			tex_index;
	t_vec		tex_scale;
	t_o_type	type;
	t_list		subtract;
	t_list		intersect;
}				t_obj;

typedef struct	s_lig
{
	t_vec		org;
	t_vec		rot;
	double		intensity;
	t_vec		col;
	t_l_type	type;
}				t_lig;

typedef struct	s_cam
{
	t_vec		org;
	t_vec		rot;
	t_matrix	ctw;
	t_matrix	wtc;
	double		fov;
	double		aperture;
}				t_cam;

typedef struct	s_scene
{
	t_list	*obj;
	t_list	*lig;
	t_list	*cam;
}				t_scene;

void	create_scene(int ac, char **av, t_scene *scene);

#endif