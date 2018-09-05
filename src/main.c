/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:01:48 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/05 16:17:52 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	check_alive(t_env *env)
{
	if (!PROP_WIN || !TRACER || TRACER->keys[esc] || PROP_WIN->keys[esc]
		|| !PROP_WIN->id || !TRACER->id)
		die("\x1b[34mClosed!\x1b[0m");
}

static int	fill_windows(t_env *env)
{
	static	char		pspace;
	static	pthread_t	thread;

	if (env->ren.c_win->keys[space] && !pspace)
	{
		create_scene(env->amount, env->names, &env->scene, env);
		calc_scene(&env->scene);
		if (env->running)
		{
			env->running = 0;
			pthread_join(thread, NULL);
		}
		pthread_create(&thread, NULL, raytracer, env);
	}
	pspace = env->ren.c_win->keys[space];
	loading(env);
	check_alive(env);
	properties(env);
	present_img(&env->ren, TRACER->id, RENDER->id);
	if (env->progress < 0.99999)
		present_img(&env->ren, TRACER->id, LOAD->id);
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

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc == 1)
		die("Usage: ./RT [Scene1]...[SceneN]");
	ft_bzero(&env, sizeof(t_env));
	renderer_set(&env.ren);
	create_blocks(env.block);
	env.win[0] = find_win(&env.ren, add_win(&env.ren,
		"The Best RT You Ever Did See", WIN_W, WIN_H));
	env.win[1] = find_win(&env.ren, add_win(&env.ren, "Properties",
		P_WIN_W, P_WIN_H));
	select_win(&env.ren, env.win[0]->id);
	env.img[0] = find_img(&env.ren, add_img(&env.ren, P_WIN_W, P_WIN_H));
	env.img[1] = find_img(&env.ren, add_img(&env.ren, WIN_W - 50, 20));
	set_img_pos(&env.ren, env.img[1]->id, 25, WIN_H - 60);
	env.img[2] = find_img(&env.ren, add_img(&env.ren, WIN_W, WIN_H));
	env.names = argv;
	env.amount = argc;
	mlx_loop_hook(env.ren.mlx, fill_windows, &env);
	env.point_start = -1;
	mlx_loop(env.ren.mlx);
}
