/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:27:23 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/18 07:49:51 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libbmp.h"
#include "time.h"

char	*ft_get_time(void)
{
	time_t	current_time;
	char	*c_time;

	current_time = time(NULL);
	if (current_time == ((time_t)-1))
		return ("0");
	c_time = ctime(&current_time);
	return (c_time);
}

void	save_image(t_env *env)
{
	unsigned char	image[env->scene.win_h][env->scene.win_w][BYTESPERPIXEL];
	char			*fn;
	t_col			c;
	int				i;
	int				j;

 	i = 0;
	while (i < env->scene.win_h)
	{
		j = 0;
		while (j < env->scene.win_w)
		{
			get_img_col(j, env->scene.win_h - i, env->img[2], c);
			image[i][j][2] = (unsigned char)c[0];
			image[i][j][1] = (unsigned char)c[1];
			image[i][j][0] = (unsigned char)c[2];
			j++;
		}
		i++;
	}
	fn = ft_strjoin_n_free(ft_strdup("Screen Shots/"), ft_strdup(env->scene.fn));
	fn = ft_strjoin_n_free(fn, ft_strdup(" "));
	fn = ft_strjoin_n_free(fn, ft_strdup(ft_get_time()));
	fn = ft_strjoin_n_free(fn, ft_strdup(".bmp"));
	generate_bitmap_image((unsigned char *)image, env->scene.win_h,
							env->scene.win_w, fn);
}
