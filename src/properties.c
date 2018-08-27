/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:12:20 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/27 17:25:38 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	print_properties(void *win, t_env *env)
{
	mlx_string_put(env->ren.mlx, win, 20, 873, 0x777777,
		"Ibotha    Jdorner    Jwolf");
}

void		properties(t_env *env)
{
	t_col		col;
	t_xy		start[2];
	t_win		*win;
	const t_img	*img = find_img(&env->ren, PROP_BACK);

	start[0][0] = 0;
	start[0][1] = 0;
	start[1][0] = 300;
	start[1][1] = 900;
	FILLCOL(col, 25, 25, 25, 255);
	draw_box(start[0], start[1], col, (t_img*)img);
	start[0][1] = 870;
	FILLCOL(col, 120, 0, 0, 70);
	draw_box(start[0], start[1], col, (t_img*)img);
	start[1][1] = 870;
	FILLCOL(col, 0, 0, 0, 255);
	draw_line(start[0], start[1], col, (t_img*)img);
	present_img(&env->ren, PROP_WIN, PROP_BACK);
	win = find_win(&env->ren, PROP_WIN);
	if (win)
		print_properties(win->win, env);
}

void		loading(t_env *env)
{
	t_xy		start;
	t_xy		end;
	t_col		col;
	const t_img	*img = find_img(&env->ren, LOAD);

	start[0] = -1;
	start[1] = -1;
	FILLCOL(col, 5, 5, 5, 255);
	end[0] = img->w;
	end[1] = img->h;
	draw_box(start, end, col, (t_img*)img);
	env->progress = ft_clamp(1.0, 0.0, env->progress);
	end[0] *= env->progress;
	while (++start[0] < end[0])
	{
		start[1] = -1;
		while (++start[1] < end[1])
		{
			FILLCOL(col, 200, 50, 50, 255);
			sc_col(col, ((end[1] + 8) - start[1]) / (float)(end[1] + 8), col);
			put_pixel(start[0], start[1], col, (t_img*)img);
		}
	}
}
