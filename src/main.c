/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:01:48 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/24 12:56:21 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_alive(t_env *env, pthread_t *thread)
{
	if (PRESSED(TRACER, esc) || PRESSED(PROP_WIN, esc)
		|| !PROP_WIN->id || !TRACER->id)
	{
		if (env->running)
		{
			env->running = 0;
			pthread_join(*thread, NULL);
		}
		del_renderer(&env->ren);
		del_scene(env);
		die("\x1b[34mClosed!\x1b[0m");
	}
}

static void	mode_set(t_env *env)
{
	if (PRESSED(TRACER, space))
	{
		env->stereod = 0;
		env->mode = 1;
		if (env->running && !(env->running = 0))
			pthread_join(env->render, NULL);
		env->running = 1;
		create_scene(env->amount, env->names, &env->scene, env);
		pthread_create(&env->render, NULL, raytracer, env);
	}
	if (PRESSED(TRACER, key_w))
	{
		env->stereod = 0;
		env->mode = 2;
		if (env->running && !(env->running = 0))
			pthread_join(env->render, NULL);
		env->running = 1;
		create_scene(env->amount, env->names, &env->scene, env);
		pthread_create(&env->render, NULL, raytracer, env);
	}
	if (PRESSED(TRACER, np_4))
		floid_dithering(env);
	if (env->mode == 2 && env->running == 0 && !env->stereod)
		gen_stereo(env);
}

static int	fill_windows(t_env *env)
{
	mode_set(env);
	if (PRESSED_SET(TRACER, cmd, key_s))
		save_image(env);
	loading(env);
	check_alive(env, &env->render);
	properties(env);
	if (PRESSED(TRACER, left) && !env->running)
		RENDER = ILEFT;
	if (PRESSED(TRACER, right) && !env->running)
		RENDER = IRIGHT;
	if (PRESSED(TRACER, up) && !env->running)
		RENDER = IFINAL;
	if (ISDOWN(TRACER, down) && !env->running)
		RENDER = (RENDER == ILEFT) ? IRIGHT : ILEFT;
	present_img(&env->ren, TRACER, RENDER);
	if (env->progress < 0.99999)
		present_img(&env->ren, TRACER, LOAD);
	update(&env->ren);
	return (0);
}

/*
**	In the main we set up the renderer and the objects
**
**	win[0] = Tracer
**	win[1] = Properties
**	img[0] = Properties Background
**	img[1] = Tracer Loading bar
**	img[2] = Render Image
*/

void		setup(t_env *env, int argc, char **argv)
{
	ft_bzero(env, sizeof(t_env));
	renderer_set(&env->ren);
	create_blocks(env->block);
	env->win[0] = add_win(&env->ren, M_WIN_NAME, WIN_W, WIN_H);
	env->win[1] = add_win(&env->ren, "Properties", P_WIN_W, P_WIN_H);
	env->img[0] = add_img(&env->ren, P_WIN_W, P_WIN_H);
	env->img[1] = add_img(&env->ren, WIN_W - 50, 20);
	set_img_pos(env->img[1], 25, WIN_H - 60);
	env->img[2] = add_img(&env->ren, WIN_W, WIN_H);
	env->img[3] = add_img(&env->ren, WIN_W, WIN_H);
	env->img[4] = add_img(&env->ren, WIN_W, WIN_H);
	env->img[5] = add_img(&env->ren, WIN_W, WIN_H);
	env->names = argv;
	env->amount = argc;
	env->mode = 1;
	create_scene(env->amount, env->names, &env->scene, env);
	pthread_create(&env->render, NULL, raytracer, env);
	env->running = 1;
	mlx_loop_hook(env->ren.mlx, fill_windows, env);
	env->point_start = -1;
	env->curr_img = env->img[2];
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc == 1)
		die("Usage: ./RT [Scene1]...[SceneN]");
	setup(&env, argc, argv);
	mlx_loop(env.ren.mlx);
	return (0);
}
