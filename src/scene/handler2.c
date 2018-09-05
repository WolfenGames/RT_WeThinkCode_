/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 07:51:39 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/05 08:18:30 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	set_tex(t_img *img, char *filename, t_env *env)
{
	int		fd;

	if (ft_strstr(filename, ".xpm") &&
		ft_strnequ(ft_strrchr(filename, '.'), ".xpm", 4))
	{
		printf("Finding texture\n");
		if ((fd = open(filename, O_RDONLY)) < 0)
			return ;
		close(fd);
		(void)img;
		(void)env;
	}
}
