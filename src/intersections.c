/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:25:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/27 15:20:27 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	get_col(t_ray *ray, t_env *env, t_col c)
{
	(void)env;
	usleep(10);
	c[0] = sqrt(ABS(ray->dir[0] * ray->dir[1])) * 255;
	c[1] = sqrt(ABS(ray->dir[1] * ray->dir[2])) * 255;
	c[2] = sqrt(ABS(ray->dir[2] * ray->dir[0])) * 255;
}
