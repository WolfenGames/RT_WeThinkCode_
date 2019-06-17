/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:50:46 by jwolf             #+#    #+#             */
/*   Updated: 2019/06/17 13:12:38 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "upng.h"
#include "rt.h"

#define P ((cur[0] + (cur[1]) * (ret->w)) * upng_get_bpp(img) / 8)
#define NA (upng_get_format(img) == (UPNG_RGB16 | UPNG_RGB8 | UPNG_LUMINANCE8))
#define ISGREY (upng_get_format(img) == (UPNG_LUMINANCE8))

t_img	*make_png_img(upng_t *img, t_env *env)
{
	t_img				*ret;
	t_xy				cur;
	const unsigned char	*dat;
	t_col				c;

	ret = add_img(&env->ren, upng_get_width(img),
					upng_get_height(img));
	dat = upng_get_buffer(img);
	cur[0] = -1;
	while (++cur[0] < ret->w)
	{
		cur[1] = -1;
		while (++cur[1] < ret->h)
		{
			if (ISGREY)
				FILLCOL(c, dat[P], dat[P], dat[P], 255);
			else
				FILLCOL(c, dat[P], dat[P + 1], dat[P + 2], NA ?
					255 : dat[P + 3]);
			put_pixel(cur[0], cur[1], c, ret);
		}
	}
	return (ret);
}

void	load_png(t_img **obj, char *fn, t_env *env)
{
	upng_t	*img;
	char	*thing;

	thing = ft_strjoin("Loading==> ", fn);
	fn = ft_strjoin_n_free(ft_strdup("./"), fn);
	ft_putendl(thing);
	free(thing);
	if (!(img = upng_new_from_file(fn)))
	{
		free(fn);
		return ;
	}
	if (img != NULL)
	{
		upng_decode(img);
		if (upng_get_error(img) == UPNG_EOK)
			*obj = make_png_img(img, env);
		upng_free(img);
	}
	thing = ft_strjoin("Finished loading==> ", fn + 2);
	ft_putendl(thing);
	free(thing);
	free(fn);
}
