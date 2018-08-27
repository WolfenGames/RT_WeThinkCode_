/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 11:21:17 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/25 16:44:29 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "vectorlib.h"
# include "libft.h"
# include "renderer.h"
# define CAM_ORG env->scene.cur_cam->centre.org
# define CAM_DIR env->scene.cur_cam->centre.dir
# define CAM env->scene.cur_cam
# define TRACER	env->win[0]
# define PROP_WIN env->win[1]
# define PROP_BACK env->img[0]
# define LOAD env->img[1]
# define RENDER env->img[2]
# define WIN_H 900.0
# define WIN_W 1300.0
# define P_WIN_H 900.0
# define P_WIN_W 300.0

typedef struct	s_env
{
	float		progress;
	int			win[10];
	int			img[10];
	t_renderer	ren;
}				t_env;

void	properties(t_env *env);
void	loading(t_env *env);
void	*raytracer(void *env);

#endif
