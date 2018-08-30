/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RT.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 11:21:17 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/29 16:42:24 by ibotha           ###   ########.fr       */
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
# define RENDER ((t_env*)env)->img[2]
# define REN &((t_env*)env)->ren
# define PROG ((t_env*)env)->progress

# define R_BLOCK_SIZE 8
# define WIN_H 900
# define WIN_W 1300
# define P_WIN_H 900
# define P_WIN_W 300
# define BLOCK_W (WIN_W / R_BLOCK_SIZE + 1)
# define BLOCK_H (WIN_H / R_BLOCK_SIZE + 1)
# define BLOCK_NO (BLOCK_H * BLOCK_W)

typedef struct	s_env
{
	t_scene		scene;
	float		progress;
	int			win[10];
	int			img[10];
	int			running;
	int			point;
	double		point_start;
	t_renderer	ren;
}				t_env;

typedef struct	s_render_block
{
	t_xy	start;
	int		taken;
}				t_render_block;

typedef struct	s_render_set
{
	t_env			*env;
	t_render_block	block[BLOCK_NO];
	t_img			*img;
}				t_render_set;

void	properties(t_env *env);
void	loading(t_env *env);
void	*raytracer(void *env);
void	get_col(t_ray *ray, t_env *env, t_col c);
void	print_vector(t_env *env, void *win, char *name, t_vec vec);

#include "intersections.h"

#endif
