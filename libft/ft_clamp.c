/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 10:25:59 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/02 15:00:49 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_max(double lo, double n)
{
	double g;

	g = n > lo ? n : lo;
	return (g);
}

double	ft_min(double hi, double n)
{
	double g;

	g = n < hi ? n : hi;
	return (g);
}

double	ft_clamp(double hi, double lo, double n)
{
	double g;

	g = ft_max(lo, n);
	g = ft_min(hi, g);
	return (g);
}
