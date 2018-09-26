/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:50:46 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/26 14:08:32 by ibotha           ###   ########.fr       */
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
	printf("==>UPNG_FORMAT_ID %i\n", upng_get_format(img));
	while (++cur[0] < ret->w)
	{
		cur[1] = -1;
		while (++cur[1] < ret->h)
		{
			if (ISGREY)
				FILLCOL(c, dat[P], dat[P], dat[P], 255);
			else
				FILLCOL(c, dat[P], dat[P + 1], dat[P + 2], NA ? 255 : dat[P + 3]);
			put_pixel(cur[0], cur[1], c, ret);
		}
	}
	return (ret);
}

void	image_setup(upng_t *img, t_obj *obj, t_env *env, int i)
{
	if (!obj->tex && i == 0)
		obj->tex = make_png_img(img, env);
	if (!obj->norm && i == 1)
		obj->norm = make_png_img(img, env);
	if (!obj->spec_map && i == 2)
		obj->spec_map = make_png_img(img, env);
}

void	load_png(t_obj *obj, char *fn, t_env *env, int i)
{
	upng_t	*img;

	printf("Loading==>%s\n", fn);
	fn = ft_strjoin_n_free(ft_strdup("./"), fn);
	if (!(img = upng_new_from_file(fn)))
	{
		free(fn);
		return ;
	}
	if (img != NULL)
	{
		upng_decode(img);
		if (upng_get_error(img) == UPNG_EOK)
			image_setup(img, obj, env, i);
		upng_free(img);
	}
	free(fn);
}
