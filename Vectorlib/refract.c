/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:24:29 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/25 10:25:42 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

double		fresnel(t_vec inc, t_vec norm, double index)
{
	double	var[5];

	var[1] = ft_clamp(1, -1, dot(inc, norm));
	var[2] = 1;
	var[3] = index;
	if (var[1] >= 0)
		ft_swap(&var[2], &var[3], sizeof(double));
	var[4] = var[2] / var[3] * sqrt(ft_max(0.0, 1 - var[1] * var[1]));
	if (var[4] > 1)
		var[0] = 1;
	else
	{
		var[4] = sqrt(ft_max(0.0, 1 - var[4] * var[4]));
		var[1] = ABS(var[1]);
		var[0] = ((var[3] * var[1]) - (var[2] * var[4]))
			/ ((var[3] * var[1]) + (var[2] * var[4]));
		var[1] = ((var[2] * var[1]) - (var[3] * var[4]))
			/ ((var[2] * var[1]) + (var[3] * var[4]));
		var[0] = (var[0] * var[0] + var[1] * var[1]) / 2.0;
	}
	return (var[0]);
}

static void	refract_helper(t_vec norm, t_vec tnorm, double var[6])
{
	var[1] = 1;
	if (var[3] < 0)
	{
		var[3] = -var[3];
		vec_dup(norm, tnorm);
	}
	else
	{
		ft_swap(&var[1], &var[2], sizeof(double));
		v_multi(norm, -1, tnorm);
	}
	var[4] = var[1] / var[2];
	var[5] = 1 - var[4] * var[4] * (1 - var[3] * var[3]);
}

double		*refract(t_vec inc, t_vec norm, double index, t_vec ret)
{
	t_vec	tnorm;
	double	var[6];

	var[0] = dot(norm, inc);
	var[1] = 1;
	var[2] = index;
	vec_dup(norm, tnorm);
	if (var[0] < 0)
		var[0] = -var[0];
	else
	{
		v_multi(norm, -1, tnorm);
		ft_swap(&var[1], &var[2], sizeof(double));
	}
	var[3] = ft_clamp(1, -1, dot(inc, norm));
	var[2] = index;
	refract_helper(norm, tnorm, var);
	var[5] < 0 ? FILLVEC(ret, 0, 0, 0, 0) : v_add(v_multi(inc, var[4], ret),
		v_multi(tnorm, var[4] * var[3] - sqrtf(var[5]), tnorm), ret)[0];
	return (ret);
}
