/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:17:55 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/19 12:59:37 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define INBOUNDS(C) (C[0] >= 0 && C[0] < BLOCK_W && C[1] >= 0 && C[1] < BLOCK_H)
#define LEFT -1
#define RIGHT 1
#define UP -2
#define DOWN 2

static void	make_block(t_render_block *block, t_xy cur, int *placed)
{
	*placed = 1;
	block->taken = 0;
	block->start[0] = cur[0] * R_BLOCK_SIZE;
	block->start[1] = cur[1] * R_BLOCK_SIZE;
}

static void	walk(int length, t_render_block *blocks, t_xy c[2], int dir)
{
	int i;

	i = -1;
	while (++i < length)
	{
		c[0][0] += ABS(dir) == 1 ? 1 * dir : 0;
		c[0][1] += ABS(dir) == 2 ? 0.5 * dir : 0;
		if (INBOUNDS(c[0]))
			make_block(&blocks[c[1][0]++], c[0], &c[1][1]);
	}
}

/*
** c[0] = cur;
** c[1][0] = i;
** c[1][1] = placed;
*/

void		create_blocks(t_render_block *blocks)
{
	int		r;
	t_xy	c[2];

	r = 0;
	c[0][0] = BLOCK_W / 2;
	c[0][1] = BLOCK_H / 2;
	c[1][0] = 1;
	make_block(&blocks[0], c[0], &c[1][1]);
	while (c[1][1])
	{
		c[1][1] = 0;
		c[0][1] -= 1;
		r += 2;
		if (INBOUNDS(c[0]))
			make_block(&blocks[c[1][0]++], c[0], &c[1][1]);
		walk(r - 1, blocks, c, RIGHT);
		walk(r, blocks, c, DOWN);
		walk(r, blocks, c, LEFT);
		walk(r, blocks, c, UP);
	}
}
