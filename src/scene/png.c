/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:50:46 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/25 10:38:35 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "upng.h"
#include "rt.h"

void	image_setup(upng_t *img, t_obj *obj, t_env *env, int i)
{
	if (!obj->tex && i == 0)
	{
		obj->tex = add_img(&env->ren, upng_get_width(img),
									upng_get_height(img));
		ft_memscpy(obj->tex->dat, (unsigned char *)upng_get_buffer(img),
					obj->tex->w * obj->tex->h * upng_get_bpp(img) / 8);
	}
	if (!obj->norm && i == 1)
	{
		obj->norm = add_img(&env->ren, upng_get_width(img),
									upng_get_height(img));
		ft_memscpy(obj->norm->dat, (unsigned char *)upng_get_buffer(img),
					obj->norm->w * obj->norm->h * upng_get_bpp(img) / 8);
	}
	if (!obj->spec_map && i == 2)
	{
		obj->spec_map = add_img(&env->ren, upng_get_width(img),
									upng_get_height(img));
		ft_memscpy(obj->spec_map->dat, (unsigned char *)upng_get_buffer(img),
					obj->spec_map->w * obj->spec_map->h *
					upng_get_bpp(img) / 8);
	}
}

void	load_png(t_obj *obj, char *fn, t_env *env, int i)
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
			image_setup(img, obj, env, i);
		upng_free(img);
	}
	free(fn);
}
