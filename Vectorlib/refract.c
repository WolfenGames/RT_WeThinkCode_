/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:24:29 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/11 14:24:42 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

double	*refract(t_vec inc, t_vec norm, double index, t_vec ret)
{
	t_vec	tnorm;
    double	NdotI = dot(norm, inc);
    double	etai = 1;
	double	etat = index;
	vec_dup(norm, tnorm);
    if (NdotI < 0) 
        NdotI = -NdotI;
    else
	{
        v_multi(norm, -1, tnorm);
        ft_swap(&etai, &etat, sizeof(double));
	}
	double cosi = ft_clamp(1, -1, dot(inc, norm));
    etai = 1,
	etat = index;
    if (cosi < 0) { cosi = -cosi; vec_dup(norm, tnorm); } else { ft_swap(&etai, &etat, sizeof(double)); v_multi(norm, -1, tnorm); }
    double eta = etai / etat;
    double k = 1 - eta * eta * (1 - cosi * cosi); 
    k < 0 ? FILLVEC(ret, 0, 0, 0, 0) : v_add(v_multi(inc, eta, ret), v_multi(tnorm, eta * cosi - sqrtf(k), tnorm), ret)[0];
	return (ret);
}