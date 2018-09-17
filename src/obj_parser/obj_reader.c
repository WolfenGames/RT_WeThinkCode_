/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:20 by jdorner           #+#    #+#             */
/*   Updated: 2018/09/12 16:05:21 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_list	*read_to_list(char *path, t_list *readcontents)
{
	int		fd;
	char	*line;
	char	*tmp;

	readcontents = NULL;
	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		line = NULL;
		while ((get_next_line(fd, &line)) > 0)
		{
			tmp = ft_strtrim(line);
			ft_lstadd(&readcontents, ft_lstnew(tmp, ft_strlen(line) + 1));
			ft_strdel(&line);
			free(tmp);
		}
	}
	ft_lstrev(&readcontents);
	if (readcontents != NULL)
		close(fd);
	return (readcontents);
}

t_list	*read_file(char *path)
{
	t_list		*readcontents;
	
	readcontents = NULL;
	if (!(readcontents = read_to_list(path, readcontents)))
	{
		return (NULL);
	}
	return (readcontents);
}

int     read_obj_files(char *paths, t_env *env)
{
    char    *er;
    t_list  *read_list;

	if((read_list = read_file(paths)) == NULL)
	{
		er = ft_strjoin_n_free(ft_strdup("\x1b[34mWarn[ng: Unable to locate the object file at the path: \x1b[0m"), paths);
		ft_putendl(er);
		free(er);
		return (0);
	}
	/*
	while (read_list)
	{
		printf("%s\n", read_list->content);
		read_list = read_list->next;
	}
	*/
	parse_list(read_list, env);
	return (1);
}
