/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:54:19 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/07 11:54:20 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			check_start(t_room **room, t_ret **ret, int fd, char *line)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (!line || line[0] == '\0')
			return (0);
		if (ft_strstr(line, "#"))
		{
			if (!ft_strcmp(line, "##end"))
				error_management1(5, line);
			(!ft_strcmp(line, "##start") ? error_management1(10, line) : 0);
			check_command_and_comment(room, ret, line);
			continue ;
		}
		if (!ft_strchr(line, ' '))
			error_management1(2, line);
		else
		{
			if (check_name_room(line, -1) == 1)
				add_room(room, line, -1, 's');
			else
				error_management1(2, line);
			add_line(ret, line);
		}
		return (1);
	}
	return (1);
}

int			check_end(t_room **room, t_ret **ret, int fd, char *line)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (!line || line[0] == '\0')
			return (0);
		if (ft_strstr(line, "#"))
		{
			if (!ft_strcmp(line, "##start"))
				error_management1(5, line);
			(!ft_strcmp(line, "##end") ? error_management1(11, line) : 0);
			check_command_and_comment(room, ret, line);
			continue ;
		}
		if (!ft_strchr(line, ' '))
			error_management1(2, line);
		else
		{
			if (check_name_room(line, -1) == 1)
				add_room(room, line, -1, 'e');
			else
				error_management1(2, line);
			add_line(ret, line);
		}
		return (1);
	}
	return (1);
}

void		check_start_and_end(t_room **room, int count_s, int count_e)
{
	t_room	*tmp;

	tmp = (*room);
	while (tmp)
	{
		if (tmp->type == 's')
		{
			count_s++;
			if (count_s > 1)
				error_management1(10, tmp->name);
		}
		else if (tmp->type == 'e')
		{
			count_e++;
			if (count_e > 1)
				error_management1(11, tmp->name);
		}
		tmp = tmp->next;
	}
	if (count_s != 1)
		error_management1(12, (*room)->name);
	if (count_e != 1)
		error_management1(13, (*room)->name);
}

void		check_link(t_room **room, t_ret **ret, char *line)
{
	int		len;
	char	*room_1;
	char	*room_2;

	len = -1;
	while (line[++len] != '-')
		;
	room_1 = ft_strsub(line, 0, len);
	room_2 = ft_strdup(ft_strchr(line, '-') + 1);
	if (!ft_strcmp(room_1, room_2))
		error_management1(14, line);
	check_same_link(room, room_1, room_2, line);
	add_link(room, room_1, room_2);
	add_link(room, room_2, room_1);
	free(room_1);
	free(room_2);
	add_line(ret, line);
}

int			count_pathes(t_room **room)
{
	t_link	*link;
	int		count;

	link = (*room)->links;
	count = 0;
	while (link)
	{
		count++;
		link = link->next;
	}
	return (count);
}
