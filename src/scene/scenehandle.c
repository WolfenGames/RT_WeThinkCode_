/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenehandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 09:01:47 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/10 09:03:02 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	do_da_scene(char *line, t_scene *scene)
{
	if (match_brackets("raydepth", line))
		scene->raydepth = ft_atod(line + 10);		
}