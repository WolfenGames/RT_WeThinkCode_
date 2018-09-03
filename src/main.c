/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:01:48 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/29 15:52:51 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	check_alive(t_env *env)
{
	t_win	*trace;
	t_win	*prop;

	trace = find_win(&env->ren, TRACER);
	prop = find_win(&env->ren, PROP_WIN);
	if (!prop || !trace || trace->keys[esc] || prop->keys[esc])
		die("\x1b[34mClosed!\x1b[0m");
}

static int	fill_windows(t_env *env)
{
	static	char		pspace;
	static	pthread_t	thread;

	check_alive(env);
	if (env->ren.c_win->keys[space] && !pspace)
	{
		if (env->running)
		{
			env->running = 0;
			pthread_join(thread, NULL);
		}
		pthread_create(&thread, NULL, raytracer, env);
	}
	pspace = env->ren.c_win->keys[space];
	loading(env);
	properties(env);
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

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc == 1)
		die("Usage: ./RT [Scene1]...[SceneN]");
	ft_bzero(&env, sizeof(t_env));
	renderer_set(&env.ren);
	env.win[0] = add_win(&env.ren, "The Best RT You Ever Did See",
		WIN_W, WIN_H);
	env.win[1] = add_win(&env.ren, "Properties", P_WIN_W, P_WIN_H);
	select_win(&env.ren, env.win[0]);
	env.img[0] = add_img(&env.ren, P_WIN_W, P_WIN_H);
	env.img[1] = add_img(&env.ren, WIN_W - 50, 20);
	set_img_pos(&env.ren, env.img[1], 25, WIN_H - 60);
	env.img[2] = add_img(&env.ren, WIN_W, WIN_H);
	create_scene(argc, argv, &env.scene);
	mlx_loop_hook(env.ren.mlx, fill_windows, &env);
	env.point_start = -1;
	mlx_loop(env.ren.mlx);
}
