/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 07:51:39 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/05 11:20:34 by jwolf            ###   ########.fr       */
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
			return ;
		close(fd);
		printf("Hello World\n");
		o->tex = find_img(REN, add_img_xpm(REN, filename, 0, 0));
	}
}
