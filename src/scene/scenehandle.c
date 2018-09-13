/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenehandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 09:01:47 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/13 11:54:57 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	do_da_scene(char *line, t_scene *scene)
{
	if (match_brackets("raydepth", line))
		scene->raydepth = ft_atod(line + 10);
	if (match_brackets("width", line))
		scene->win_w = ft_atod(7);
	if (match_brackets("height", line))
		scene->win_h = ft_atod(8);
}