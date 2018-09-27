/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:40:13 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/26 15:46:17 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "rt.h"

void	face_from_str(char *str, int vert[3], int off[3])
{
	while (*str == '/' || *str == '\t')
		++str;
	vert[0] = ft_atoi(str) - 1 - off[0];
	while (!(*str == '/' || *str == '\t'))
		++str;
	if (*str == '/' || *str == '\t')
		++str;
	vert[1] = ft_atoi(str) - 1 - off[2];
	while (!(*str == '/' || *str == '\t'))
		++str;
	if (*str == '/' || *str == '\t')
		++str;
	vert[2] = ft_atoi(str) - 1 - off[1];
}

void	to_face(char *str, t_obj *obj, int *index, int off[3])
{
	char	**faces_arr;
	int		total_cnt;
	int		i;

	faces_arr = ft_strsplit(str, ' ');
	i = 0;
	total_cnt = 0;
	while (faces_arr[total_cnt])
		total_cnt++;
	while (i < total_cnt - 3)
	{
		face_from_str(faces_arr[1], obj->faces[*index][0], off);
		face_from_str(faces_arr[2 + i], obj->faces[*index][1], off);
		face_from_str(faces_arr[3 + i], obj->faces[*index][2], off);
		i++;
		*index += 1;
	}
	free_tab(&faces_arr);
}

void	assign_vertexpoints(t_vec vec, t_vec *ret)
{
	*ret[0] = vec[0];
	*ret[1] = vec[1];
	*ret[2] = vec[2];
}

void	assign_texturecoord(t_vec vec, t_tex *ret)
{
	*ret[0] = vec[0];
	*ret[1] = vec[1];
	*ret[2] = vec[2];
}

void	parse_info(t_list *lst, t_obj *obj, char *name, int off[3])
{
	int		count[4];

	FILLVEC(count, 0, 0, 0, 0);
	obj->name = ft_strdup(name);
	obj->type = obj_polygon;
	while (lst &&
		!((ft_strstr(lst->content, "#") &&
		(ft_strstr(lst->content, "triangles") ||
		ft_strstr(lst->content, "polygons")))))
	{
		if (ft_strstr(lst->content, "v "))
			vec_from_str(obj->vertex_point[count[0]++], lst->content + 2);
		if (ft_strstr(lst->content, "vn "))
			vec_from_str(obj->vertex_normal[count[1]++], lst->content + 3);
		if (ft_strstr(lst->content, "vt "))
			vec_from_str(obj->vertex_texture_coord[count[2]++],
				lst->content + 3);
		if (ft_strstr(lst->content, "f "))
			to_face(lst->content, obj, &count[3], off);
		lst = lst->next;
		if (!lst || ft_strstr((lst)->content, "o ") ||
			ft_strstr((lst)->content, "# object"))
			return ;
	}
}
