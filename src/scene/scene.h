/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:33:30 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/19 09:49:18 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vectorlib.h"
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_env	t_env;
typedef struct s_img	t_img;
typedef int				t_vertex[3];
typedef	t_vertex		t_face[3];	

typedef enum	e_l_type
{
	light_point,
	light_directional
}				t_l_type;

typedef enum	e_style
{
	greyscale,
	cartoon,
	cell_shaded
}				t_style;

typedef enum	e_o_type
{
	obj_sphere,
	obj_plane,
	obj_cone,
	obj_cylinder,
	obj_polygon
}				t_o_type;

typedef enum	e_bool_type
{
	none,
	subtract,
	intersect,
}				t_bool_type;

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
	t_img		*tex;
	double		albedo;
	double		radius;
	double		r_index;
	double		transparency;
	t_vec		tex_scale;
	t_o_type	type;
	t_list		subtract;
	t_list		intersect;
	int			n_v_point;
	t_vec		*vertex_point;
	int			n_v_normal;
	t_vec		*vertex_normal;
	int			n_v_t_coord;
  t_tex		*vertex_texture_coord;
	int			n_faces;
  t_face		*faces;
	t_list		bools;
	t_list		points;
	t_list		triangles;
	t_bool_type	bool_type;
	void		(*get_norm)(t_vec norm, t_vec point, struct s_obj *obj);
	int			(*get_intersect)(t_ray *ray, struct s_obj *obj);
	void		(*get_surface_col)(struct s_obj *obj, t_vec c, t_vec point);
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
	t_style		style;
	int			win_w;
	int			win_h;
	char		*fn;
	int			aa_level;
	double		raydepth;
	t_list		*obj;
	t_list		*lig;
	t_list		*cam;
	t_cam		*c_cam;
	int			cellshade;
}				t_scene;

typedef struct	s_read
{
	char		*line;
	char		*line2;
	char		*close_tag;
	char		*tmp;
	int			flag;
}				t_read;

void			create_scene(int ac, char **av, t_scene *scene, t_env *env);
void			do_da_scene(char *line, t_env *env);
void			do_da_object(char *name, char *line,
								t_scene *scene, t_env *env);
void			do_da_object_stuff_one(char *name, char *line,
										t_obj *new, t_env *env);
void			do_da_polygon(char *line, t_env *env);
void			free_tab(char ***tab);
void			handle_contents(char *line, char *name, t_scene *scene,
								t_env *env);
void			set_vec(t_vec vec, char *linesub);
void			set_obj_params(t_obj *o);
void			set_o_type(char *s, t_obj *o);
void			set_tex(t_obj *o, char *filename, t_env *env);
void			save_image(t_env *env);

int     		read_obj_files(char *paths, t_env *env);
void			parse_list(t_list *lst, t_env *env);

int				is_line_prop(const char *line);
int				match_brackets(char *str, char *line);

char			char_lower(char c);

char			*get_name(char *s);
char			*get_prop_name(char *s);
char			*make_end(char *str);

t_cam			*search_cam_list(t_scene *scene, char *name);
t_obj			*search_obj_list(t_scene *scene, char *name);
t_lig			*search_light_list(t_scene *scene, char *name);

t_l_type		set_l_type(char *s);

void			calc_scene(t_scene *scene);

#endif
