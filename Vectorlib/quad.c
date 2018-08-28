/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 18:51:53 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 18:52:45 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

int	quad(t_vec val, double t[2])
{
	double discr;
	double q;

	discr = val[1] * val[1] - 4.f * val[0] * val[2];
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		t[1] = -0.5 * val[1] / val[0];
		t[0] = t[1];
	}
	else
	{
		q = (val[1] > 0) ? -0.5 * (val[1] + sqrt(discr)) : -0.5 * (val[1] - sqrt(discr));
		t[0] = q / val[0];
		t[1] = val[2] / q;
	}
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1], sizeof(double));
	return (1);
}
