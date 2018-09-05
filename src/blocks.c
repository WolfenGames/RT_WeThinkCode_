/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:17:55 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/05 13:34:53 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	sort_blocks(t_render_block *blocks)
{
	int i;
	int max;

	max = BLOCK_NO;
	while (--max)
	{
		i = -1;
		while (++i < (max - 1))
		{
			if ((pow(blocks[i].start[0] - (WIN_W / 2), 2) + pow(blocks[i].start[1] - (WIN_H / 2), 2))
				> (pow(blocks[i + 1].start[0] - (WIN_W / 2), 2)
				+ pow(blocks[i + 1].start[1] - (WIN_H / 2), 2)))
				ft_swap(&blocks[i], &blocks[i + 1], sizeof(t_render_block));
		}
	}
}

void		create_blocks(t_render_block *blocks)
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
	sort_blocks(blocks);
}