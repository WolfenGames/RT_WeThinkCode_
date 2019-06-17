/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descene2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 15:51:18 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 13:08:26 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		del_lig(t_list **ligs)
{
	t_lig	*lig;

	if (*ligs)
	{
		del_lig(&(*ligs)->next);
		lig = (t_lig*)(*ligs)->content;
		free(lig->name);
		free(lig);
		free(*ligs);
	}
}

void		del_cam(t_list **cams)
{
	t_cam	*cam;

	if (*cams)
	{
		del_lig(&(*cams)->next);
		cam = (t_cam*)(*cams)->content;
		free(cam->name);
		free(cam);
		free(*cams);
	}
}
