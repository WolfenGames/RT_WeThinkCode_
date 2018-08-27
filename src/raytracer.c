/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 17:12:38 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/27 17:28:35 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	generate_ray(t_ray *ray, t_xy coord, t_env *env)
{
	const double	invheight = 1 / (double)WIN_H;
	const double	invwidth = 1 / (double)WIN_W;
	const double	angle = tan(90.0 * 0.5 * M_PI / 180.0);

	(void)env;
	ray->org[0] = 0;
	ray->org[1] = 0;
	ray->org[2] = 20;
	ray->dir[0] = (2 * (coord[0] + 0.5) * invwidth - 1) * (double)WIN_W
		* invheight * angle;
	ray->dir[1] = (1 - 2 * (coord[1] + 0.5) * invheight) * angle;
	ray->dir[2] = -1;
	normalize(ray->dir);
}

static void	create_blocks(t_render_block *blocks)
{
	t_xy			coord;
	t_render_block	*cur;

	coord[1] = -1;
	while (++coord[1] < BLOCK_H)
	{
		coord[0] = -1;
		while (++coord[0] < BLOCK_W)
		{
			cur = &blocks[coord[0] + coord[1] * BLOCK_W];
			cur->start[0] = coord[0] * R_BLOCK_SIZE;
			cur->start[1] = coord[1] * R_BLOCK_SIZE;
			cur->taken = 0;
		}
	}
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
			get_col(&ray, env, c);
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
		if (!(set->block[x].taken))
		{
			if (!set->env->running)
				pthread_exit(NULL);
			set->block[x].taken = 1;
			render_block(set->env, &set->block[x], set->img);
			set->env->progress += 1 / (double)BLOCK_NO;
		}
	}
	return (NULL);
}

void		*raytracer(void *env)
{
	t_render_set	set;
	pthread_t		threads[4];

	PROG = 0;
	create_blocks(set.block);
	set.env = env;
	set.env->running = 1;
	set.img = find_img(REN, RENDER);
	pthread_create(&threads[0], NULL, calc_block, &set);
	pthread_create(&threads[1], NULL, calc_block, &set);
	pthread_create(&threads[2], NULL, calc_block, &set);
	pthread_create(&threads[3], NULL, calc_block, &set);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);
	PROG = 1;
	return (0);
}
