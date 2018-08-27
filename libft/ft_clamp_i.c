/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 11:42:27 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/02 15:01:06 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_max_i(int lo, int n)
{
	int g;

	g = n > lo ? n : lo;
	return (g);
}

int	ft_min_i(int hi, int n)
{
	int g;

	g = n < hi ? n : hi;
	return (g);
}

int	ft_clamp_i(int hi, int lo, int n)
{
	int g;

	g = ft_max_i(lo, n);
	g = ft_min_i(hi, g);
	return (g);
}
