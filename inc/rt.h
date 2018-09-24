/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 11:21:17 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/24 13:27:53 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "scene.h"
# include "renderer.h"
# include "pthread.h"

# define TRACER	((t_env*)env)->win[0]
# define PROP_WIN ((t_env*)env)->win[1]
# define PROP_BACK ((t_env*)env)->img[0]
# define LOAD ((t_env*)env)->img[1]
# define ILEFT ((t_env*)env)->img[2]
# define IRIGHT ((t_env*)env)->img[3]
# define IFINAL ((t_env*)env)->img[4]
# define RENDER ((t_env*)env)->curr_img
# define REN &((t_env*)env)->ren
# define PROG ((t_env*)env)->progress
# define M_WIN_NAME "The Best RT You Ever Did See!"

# define R_BLOCK_SIZE 32
# define WIN_H 900
# define WIN_W 1500
# define P_WIN_H 900
# define P_WIN_W 450
# define BLOCK_W (WIN_W / R_BLOCK_SIZE + 1)
# define BLOCK_H (WIN_H / R_BLOCK_SIZE + 1)
# define BLOCK_NO (BLOCK_H * BLOCK_W)

# define VP(N) obj->vertex_point[obj->faces[i][N][0]]
# define VT(N) obj->vertex_texture_coord[obj->faces[i][N][1]]
# define VN(N) obj->vertex_normal[obj->faces[i][N][2]]

# include "intersections.h"

typedef struct	s_render_block
{
	t_xy	start;
	int		taken;
}				t_render_block;

typedef struct	s_env
{
	pthread_t		render;
	t_scene			scene;
	float			progress;
	t_win			*win[10];
	t_img			*img[10];
	t_img			*curr_img;
	int				running;
	int				point;
	double			point_start;
	t_renderer		ren;
	t_render_block	block[BLOCK_NO];
	char			**names;
	int				amount;
	int				mode;
	int				side;
	int				stereod;
	double			eye_w;
	t_col			ambience;
}				t_env;

typedef struct	s_render_set
{
	t_env			*env;
	t_img			*img;
}				t_render_set;

void			properties(t_env *env);
void			loading(t_env *env);
void			*raytracer(void *env);
void			print_vector(t_env *env, void *win, char *name, t_vec vec);
void			create_scene(int ac, char **av, t_scene *scene, t_env *env);
void			create_blocks(t_render_block *blocks);
void			del_scene(t_env *env);
void			gen_stereo(t_env *env);
void			generate_ray(t_ray *ray, double x, double y, t_env *env);
void			floid_dithering(t_env *env);
void			vector_print(t_env *env, void *win, t_obj *obj);
void			aa(t_env *env);

#endif
