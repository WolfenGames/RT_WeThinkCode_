/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 07:51:39 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/16 16:22:56 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"

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
		o->tex = add_img_xpm(REN, filename, 0, 0);
	}
	free(filename);
}
