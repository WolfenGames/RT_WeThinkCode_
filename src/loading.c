/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 14:46:45 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/29 16:09:55 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

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

void	print_vector(t_env *env, void *win, char *name, t_vec vec)
{
	char	*string;

	string = ft_strjoin_n_free(ft_strdup(name), ft_strdup(": "));
	string = ft_strjoin_n_free(string, ft_dtoa(vec[0]));
	string = ft_strjoin_n_free(string, ft_strdup(", "));
	string = ft_strjoin_n_free(string, ft_dtoa(vec[1]));
	string = ft_strjoin_n_free(string, ft_strdup(", "));
	string = ft_strjoin_n_free(string, ft_dtoa(vec[2]));
	if (++env->point > -1 && env->point < 43)
		mlx_string_put(env->ren.mlx, win, 40, env->point * 20, 0xcccccc, string);
	free(string);
}