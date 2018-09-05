/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:12:38 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/05 16:41:42 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	generate_ray(t_ray *ray, t_xy coord, t_env *env)
{
	const double	invheight = 1 / (double)WIN_H;
	const double	invwidth = 1 / (double)WIN_W;
	const double	angle = tan(env->scene.c_cam->fov * 0.5 * M_PI / 180.0);

	ft_memcpy(ray->org, env->scene.c_cam->org, sizeof(double) * 4);
	ray->dir[0] = (2 * (coord[0] + 0.5) * invwidth - 1) * (double)WIN_W
		* invheight * angle;
	ray->dir[1] = (1 - 2 * (coord[1] + 0.5) * invheight) * angle;
	ray->dir[2] = -1;
	transformvec(env->scene.c_cam->ctw, ray->dir, ray->dir);
	normalize(ray->dir);
}

static void	render_block(t_env *env, t_render_block *block, t_img *img)
{
	t_ray	ray;
	t_xy	size;
	t_col	c;

	c[3] = 255;
	size[1] = block->start[1] - 1;
	while (++size[1] < (R_BLOCK_SIZE + block->start[1]) && size[1] < WIN_H)
	{
		size[0] = block->start[0] - 1;
		while (++size[0] < (R_BLOCK_SIZE + block->start[0]) && size[0] < WIN_W)
		{
			generate_ray(&ray, size, env);
			get_col(&ray, env, c, 0);
			put_pixel(size[0], size[1], c, img);
		}
	}
}

static void	*calc_block(void *temp)
{
	int					x;
	t_render_set		*set;

	set = (t_render_set*)temp;
	x = -1;
	while (++x < BLOCK_NO)
	{
		if (!(set->env->block[x].taken))
		{
			if (!set->env->running)
				pthread_exit(NULL);
			set->env->block[x].taken = 1;
			render_block(set->env, &set->env->block[x], set->img);
			set->env->progress += 1 / (double)BLOCK_NO;
		}
	}
	return (NULL);
}

static void	clear_blocks(t_render_block *blocks)
{
	int i;

	i = -1;
	while (++i < BLOCK_NO)
		blocks[i].taken = 0;
}

void		*raytracer(void *env)
{
	t_render_set	set;
	pthread_t		threads[4];

	PROG = 0;
	set.env = env;
	set.env->running = 1;
	set.img = RENDER;
	pthread_create(&threads[0], NULL, calc_block, &set);
	pthread_create(&threads[1], NULL, calc_block, &set);
	pthread_create(&threads[2], NULL, calc_block, &set);
	pthread_create(&threads[3], NULL, calc_block, &set);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);
	PROG = 1;
	clear_blocks(set.env->block);
	set.env->running = 0;
	return (0);
}
