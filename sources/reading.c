/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:33:28 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/06 17:33:29 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		reading_input(t_room **room, t_ret **ret, int fd)
{
	char	*line;

	line = NULL;
	reading_ants(room, ret, fd, line);
	reading_rooms(room, ret, fd, &line);
	if (line && line[0] == '\0')
		free(line);
}

void		reading_ants(t_room **room, t_ret **ret, int fd, char *line)
{
	int		index;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "#"))
			check_command_and_comment(room, ret, line);
		else if (line[0] != '#')
		{
			index = -1;
			while (line[++index])
				if (!ft_isdigit(line[index]))
					error_management1(1, line);
			(*room)->ants = ft_atoi(line);
			if ((*room)->ants < 1)
				error_management1(1, line);
			else
			{
				add_line(ret, line);
				return ;
			}
		}
		else if ((!line || line[0] == '\0') && (*room)->ants < 1)
			error_management1(1, line);
	}
}

void		reading_rooms(t_room **room, t_ret **ret, int fd, char **line)
{
	while (get_next_line(fd, &(*line)) > 0)
	{
		if (!(*line) || (*line)[0] == '\0')
			return ;
		if ((*line)[0] == ' ' && ft_strstr((*line), "#"))
			error_management1(6, (*line));
		else if ((*line)[0] == '#' && (ft_strcmp((*line), "##start") != 0
			&& ft_strcmp((*line), "##end") != 0))
		{
			check_command_and_comment(room, ret, (*line));
			if (!ft_strncmp((*line),
				"#Here is the number of lines required:", 38))
				(*room)->line_req = (*line);
		}
		else if (!ft_strcmp((*line), "##start"))
		{
			add_line(ret, (*line));
			if (!check_start(room, ret, fd, (*line)))
				return ;
		}
		else if (!reading_rooms_next(room, ret, fd, (*line)))
			return ;
	}
}

int			reading_rooms_next(t_room **room, t_ret **ret, int fd, char *line)
{
	if (ft_strcmp(line, "##end") == 0)
	{
		add_line(ret, line);
		if (!check_end(room, ret, fd, line))
			return (0);
	}
	else if (ft_strstr(line, "#"))
		check_command_and_comment(room, ret, line);
	else
	{
		if (check_name(line, 0, -1, 0) == 1)
			if (check_name_room(line, -1) == 1)
				add_room(room, line, -1, 'r');
		if (ft_strchr(line, '-'))
			return (reading_links(room, ret, fd, line));
		add_line(ret, line);
	}
	return (1);
}

int			reading_links(t_room **room, t_ret **ret, int fd, char *line)
{
	(room ? check_start_and_end(room, 0, 0) : 0);
	(room && ret && line ? check_link(room, ret, line) : 0);
	while (get_next_line(fd, &line) > 0)
	{
		if (!line || line[0] == '\0')
		{
			free(line);
			return (0);
		}
		if (line[0] == '#' && (ft_strcmp(line, "##start") != 0
			&& ft_strcmp(line, "##end") != 0))
		{
			check_command_and_comment(room, ret, line);
			if (ft_strcmp(line, "#Here is the number of lines required:") == 0)
				(*room)->line_req = line;
		}
		else if (check_name_room(line, -1) == 1)
			error_management1(7, line);
		else
			check_link(room, ret, line);
	}
	return (1);
}
