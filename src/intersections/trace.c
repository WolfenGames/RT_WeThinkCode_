/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 09:34:36 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/21 11:19:46 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	The trace function takes a ray and determines if it hits an object,
**	it shortens the ray to the distance to the point of intersection and
**	returns the hit object.
*/

t_obj			*trace(t_ray *ray, t_list *cur)
{
	t_obj	*ret;

	ret = NULL;
	while (cur)
	{
		if (((t_obj*)cur->content)->get_intersect(ray, cur->content))
			ret = (t_obj*)cur->content;
		cur = cur->next;
	}
	return (ret);
}
