/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:24:29 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/08 12:37:59 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

double	*refract(t_vec inc, t_vec norm, double index, t_vec ret)
{
	double	ni;
	double	k;
	t_vec	temp;
	t_vec	temp2;
	
	ni = dot(norm, inc);
	k = 1.f - index * index * (1.f - ni * ni);
	if (k < 0.f)
		FILLVEC(ret, 0.0, 0.0, 0.0, 0.0);
	else
		v_sub(v_multi(inc, index, temp),
			v_multi(norm, index * ni + sqrtf(k), temp2), ret);
	return (ret);
}