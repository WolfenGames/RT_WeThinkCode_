/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 07:51:39 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/05 16:42:33 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "RT.h"

void	set_tex(t_obj *o, char *filename, t_env *env)
{
	int		fd;

	if (ft_strstr(filename, ".xpm") &&
		ft_strnequ(ft_strrchr(filename, '.'), ".xpm", 4))
	{
		if ((fd = open(filename, O_RDONLY)) < 0)
		{
			free(filename);
			return ;
		}
		close(fd);
		if (o->tex)
			del_img(&env->ren, o->tex->id);
		o->tex = find_img(REN, add_img_xpm(REN, filename, 0, 0));
	}
	free(filename);
}
