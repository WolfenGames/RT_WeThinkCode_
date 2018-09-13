/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:27:23 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/13 11:46:13 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"
#include "libbmp.h"

void	save_image(t_env *env)
{
	unsigned char	image[WIN_H][WIN_W][BYTESPERPIXEL];
	t_col			c;
	int				i;
	int				j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			get_img_col(j, WIN_H - i, env->img[2], c);
			image[i][j][2] = (unsigned char)c[0];
			image[i][j][1] = (unsigned char)c[1];
			image[i][j][0] = (unsigned char)c[2];
			j++;
		}
		i++;
	}
	generate_bitmap_image((unsigned char *)image, WIN_H, WIN_W, FILENAME);
}