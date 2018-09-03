/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 14:59:14 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/03 16:27:17 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

char	char_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

char	*make_end(char *str)
{
	int		i;
	int		j;
	int		l;
	char	*ret;

	l = ft_strlen(str);
	j = 2;
	ret = ft_strnew(l + 3);
	ret[0] = '<';
	ret[1] = '/';
	i = 0;
	while (j < l + 2)
		ret[j++] = str[i++];
	ret[j] = '>';
	return (ret);
}

int		match_brackets(char *string, char *line)
{
	char	*linestart;
	char	*endline;
	int		ret;

	linestart = get_prop_name(line);
	endline = make_end(linestart);
	ret = (ft_strnequ(linestart, string, ft_strlen(string)) &&
		ft_strnrequ(line, endline, ft_strlen(endline))) ? 1 : 0;
	free(endline);
	return (ret);
}

void	set_vec(t_vec vec, char *linesub)
{
	vec_from_str(vec, linesub);
	free(linesub);
}

void	free_tab(char ***tab)
{
	int		i;

	i = -1;
	if (!*tab)
		return ;
	while ((*tab)[++i])
		ft_memdel((void **)&(*tab)[i]);
	ft_memdel((void**)tab);
}
