/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:50:46 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/21 12:47:09 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "upng.h"
#include "rt.h"

void	do_da_image(upng_t *img, t_obj *obj, t_env *env)
{
	if (obj->tex)
		return ;
	obj->tex = add_img(&env->ren, upng_get_width(img),
								upng_get_height(img));
	ft_memscpy(obj->tex->dat, (unsigned char *)upng_get_buffer(img),
				obj->tex->w * obj->tex->h * upng_get_bpp(img) / 8);
}

void	load_png(t_obj *obj, char *fn, t_env *env)
{
	upng_t	*img;

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
			do_da_image(img, obj, env);
		upng_free(img);
	}
	free(fn);
}
