/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 14:53:50 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/12 13:28:58 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

double	*v_mult(t_vec a, t_vec b, t_vec ret)
{
	ret[0] = a[0] * b[0];
	ret[1] = a[1] * b[1];
	ret[2] = a[2] * b[2];
	return (ret);
}

double	*v_add(t_vec a, t_vec b, t_vec ret)
{
	ret[0] = a[0] + b[0];
	ret[1] = a[1] + b[1];
	ret[2] = a[2] + b[2];
	return (ret);
}

double	*v_sub(t_vec a, t_vec b, t_vec ret)
{
	ret[0] = a[0] - b[0];
	ret[1] = a[1] - b[1];
	ret[2] = a[2] - b[2];
	return (ret);
}

double	*v_multi(t_vec a, double b, t_vec ret)
{
	ret[0] = a[0] * b;
	ret[1] = a[1] * b;
	ret[2] = a[2] * b;
	return (ret);
}

void	vec_dup(t_vec src, t_vec dst)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
}
