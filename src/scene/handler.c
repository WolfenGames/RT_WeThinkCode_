/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 07:48:27 by jwolf             #+#    #+#             */
/*   Updated: 2018/08/30 14:34:41 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

char	char_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int		is_line_prop(const char *line)
{
	int		ret;

	ret = 0;
	if (ft_strnequ(line, "<origin>", 8))
		ret = 1;
	if (ft_strnequ(line, "<roation>", 9))
		ret = 1;
	if (ft_strnequ(line, "<fov>", 5))
		ret = 1;
	if (ft_strnequ(line, "<aperture>", 10))
		ret = 1;
	if (ft_strnequ(line, "<scale>", 7))
		ret = 1;
	if (ft_strnequ(line, "<diffusecolour>", 15))
		ret = 1;
	if (ft_strnequ(line , "<specularcolour>", 16))
		ret = 1;
	if (ft_strnequ(line, "<albedo>", 8))
		ret = 1;
	if (ft_strnequ(line, "<refractiveindex>", 17))
		ret = 1;
	if (ft_strnequ(line, "<glossy>", 8))
		ret = 1;
	return (ret);
}

void	do_da_camera(void)
{
	printf("Doing da Camera\n");
}

void	do_da_light(void)
{
	printf("Doing da light\n");
}

void	do_da_object(void)
{
	printf("Doing da object\n");
}

void	handle_contents(char *line, char *name, t_scene *scene)
{
	char	*small;
	char	*small2;

	small = ft_strmap(line, char_lower);
	small2 = ft_strmap(name, char_lower);
	if (is_line_prop(small))
	{
		if (ft_strnequ(small2, "<object", 7))
			do_da_object();
		if (ft_strnequ(small2, "<camera", 7))
			do_da_camera();
		if (ft_strnequ(small2, "<light", 6))
			do_da_light();
	}
	free(small);
	free(small2);
	(void)scene;
}