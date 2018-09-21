/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:50:46 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/21 09:16:11 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "upng.h"
#include "rt.h"

void	do_da_image(upng_t *img, t_obj *obj)
{
	obj->tex->img = img;
	obj->tex->dat = (unsigned char *)upng_get_buffer(img);
}

void	load_png(t_obj *obj, char *fn)
{
	upng_t	*img;

	img = upng_new_from_file(fn);
	if (!img)
	{
		upng_decode(img);
		if (upng_get_error(img) == UPNG_EOK)
			do_da_image(img, obj);
		upng_free(img);
	}
}
