/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:05:20 by jdorner           #+#    #+#             */
/*   Updated: 2018/09/19 11:36:59 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
			ft_lstadd(&readcontents, ft_lstnew(tmp, ft_strlen(tmp) + 1));
			ft_strdel(&line);
			free(tmp);
		}
		free(line);
	}
	ft_lstrev(&readcontents);
	close(fd);
	return (readcontents);
}

t_list	*read_file(char *path)
{
	t_list		*readcontents;

	readcontents = NULL;
	if (!(readcontents = read_to_list(path, readcontents)))
		return (NULL);
	return (readcontents);
}

void	kill_lst(void *content, size_t size)
{
	(void)size;
	free(content);
}

int		read_obj_files(char *paths, t_env *env)
{
	char	*er;
	t_list	*read_list;

	if ((read_list = read_file(paths)) == NULL)
	{
		er = ft_strjoin_n_free(ft_strdup("\x1b[34mBad .obj: \x1b[0m"), paths);
		die(er);
	}
	parse_list(read_list, env);
	ft_lstdel(&read_list, kill_lst);
	return (1);
}
