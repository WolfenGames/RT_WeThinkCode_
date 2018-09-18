/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 08:47:53 by jdorner           #+#    #+#             */
/*   Updated: 2018/09/18 15:26:42 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
float      ft_stof(char* s)
{
    float  rez;
    float  fact;
    int     point_seen;

    rez = 0;
    fact = 1;
    point_seen = 0;
    if ((*s) == '-')
    {
        fact = -1;
        s++;
    }
    while(*s)
    {
        if (*s == '.')
        {
            point_seen = 1; 
            s++;
        }
        if ((*s - '0') >= 0 && (*s - '0') <= 9)
        {
            if (point_seen)
                fact /= 10.0f;
            rez = rez * 10.0f + (float)(*s - '0');
        }
        s++;
    }
    return (rez * fact);
}
*/

/*
t_vector3       to_vector3(char *str)
{
    t_vector3   vector;
    char        **vector_arr;

    vector_arr = ft_strsplit(str, ' ');
    vector.x = ft_stof(vector_arr[1]);
    vector.y = ft_stof(vector_arr[2]);
    vector.z = ft_stof(vector_arr[3]);
    return (vector);
}
*/

void		face_from_str(char *str, int vert[3])
{
	while (*str == '/' || *str == '\t')
		++str;
	vert[0] = ft_atoi(str) - 1;
	while (!(*str == '/' || *str == '\t'))
		++str;
	if (*str == '/' || *str == '\t')
		++str;
	vert[1] = ft_atoi(str) - 1;
	while (!(*str == '/' || *str == '\t'))
		++str;
	if (*str == '/' || *str == '\t')
		++str;
	vert[2] = ft_atoi(str) - 1;
}

void       to_face(char *str, t_obj *obj, int *index)
{
    char        **faces_arr;
	int			total_cnt;
	int			i;

    faces_arr = ft_strsplit(str, ' ');
	i = 0;
	total_cnt = 0;
	while (faces_arr[total_cnt])
		total_cnt++;
	while (i < total_cnt - 3)
	{
		face_from_str(faces_arr[1], obj->faces[*index][0]);
		face_from_str(faces_arr[2 + i], obj->faces[*index][1]);
		face_from_str(faces_arr[3 + i], obj->faces[*index][2]);
		i++;
		*index += 1;
	}
	free_tab(&faces_arr);
}

void				assign_vertexpoints(t_vec vec, t_vec *ret)
{
    *ret[0] = vec[0];
    *ret[1] = vec[1];
    *ret[2] = vec[2];
}

void				assign_texturecoord(t_vec vec, t_tex *ret)
{
    *ret[0] = vec[0];
    *ret[1] = vec[1];
    *ret[2] = vec[2];
}

void				parse_info(t_list *lst, t_obj *obj)
{
	int				count[4];

	FILLVEC(count, 0, 0, 0, 0);
	while (lst &&
	!((ft_strstr(lst->content, "#") &&
	(ft_strstr(lst->content, "triangles") || ft_strstr(lst->content, "polygons")))))
	{
		if (ft_strstr(lst->content, "v "))
			vec_from_str(obj->vertex_point[count[0]++], lst->content + 2);
		if (ft_strstr(lst->content, "vn "))
			vec_from_str(obj->vertex_normal[count[1]++], lst->content + 3);
		if (ft_strstr(lst->content, "vt "))
			vec_from_str(obj->vertex_texture_coord[count[2]++], lst->content + 3);
		if (ft_strstr(lst->content, "f "))
			to_face(lst->content, obj, &count[3]);
		lst = lst->next;
	}
}

int				recurr_count(char *str, char delim)
{
	int ret;

	ret = 0;
	while (str && *str)
	{
		if (*str == delim)
			ret++;
		++str;
	}
	return (ret);
}

void		assign_mem(t_obj *new)
{
	if (new->vertex_normal)
		free(new->vertex_normal);
	if (new->vertex_texture_coord)
		free(new->vertex_texture_coord);
	if (new->vertex_point)
		free(new->vertex_point);
	if (new->faces)
		free(new->faces);
	new->vertex_point = malloc(sizeof(t_face) * new->n_v_point);
	new->vertex_normal = malloc(sizeof(t_face) * new->n_v_normal);
	new->vertex_texture_coord = malloc(sizeof(t_face) * new->n_v_t_coord);
	new->faces = malloc(sizeof(t_face) * new->n_faces);
}

int			malloc_obj_info(t_list **lst, t_obj *new)
{
    while (*lst)
    {
        if (ft_strstr((*lst)->content, "v "))
			new->n_v_point++;
		if (ft_strstr((*lst)->content, "vn "))
			new->n_v_normal++;
        if (ft_strstr((*lst)->content, "vt "))
			new->n_v_t_coord++;
        if (ft_strstr((*lst)->content, "f "))
			new->n_faces += recurr_count((*lst)->content, ' ') - 2;
		*lst = (*lst)->next;
        if (!*lst || ft_strstr((*lst)->content, "o ") || ft_strstr((*lst)->content, "# object"))
        {
			assign_mem(new);
			return (1);
        }
    }
    return (0);
}

char    *object_name_zone(t_list *lst)
{
	if (lst && ft_strstr(lst->content, "# object"))
		return (lst->content + 9);
	if (lst && ft_strstr(lst->content, "o "))
		return (lst->content + 2);
    return (NULL);
}

t_obj	*the_good_search_name(t_scene *scene, char *name)
{
	t_list	*list;
	t_obj	*o;

	list = scene->obj;
	while (list)
	{
		o = (t_obj*)list->content;
		if (ft_strequ(o->name, name))
			return (o);
		list = list->next;
	}
	return (NULL);
}

void    parse_list(t_list *lst, t_env *env)
{
	t_obj           template;
	t_obj			*bob;
	t_list			*temp_list;
	char			*name;

	ft_bzero(&template, sizeof(t_obj));
    while (lst)
    {
        if ((name = object_name_zone(lst)) != NULL)
		{
            if (!(bob = the_good_search_name(&env->scene, name)))
			{
				lst = lst->next;
				ft_lstadd(&env->scene.obj, ft_lstnew(&template, sizeof(t_obj)));
				bob = env->scene.obj->content;
				bob->name = ft_strdup(name);
				bob->type = obj_polygon;
				temp_list = lst;
				if (malloc_obj_info(&lst, bob))
					parse_info(temp_list, bob);
				else
					die("[OBJ_PARSE_ERR]");
			}
		}
		else if (lst)
        	lst = lst->next;
    }
}
