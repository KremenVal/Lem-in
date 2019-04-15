/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:54:43 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/07 11:54:45 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		add_line(t_ret **ret, char *line)
{
	t_ret	*new;
	t_ret	*tmp;

	new = (t_ret *)ft_memalloc(sizeof(t_ret));
	new->line = line;
	tmp = (*ret);
	if (!(*ret))
		(*ret) = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		add_room(t_room **room, char *line, int len, char type)
{
	t_room	*new;

	new = (t_room *)ft_memalloc(sizeof(t_room));
	while (line[++len] != ' ')
		;
	new->name = ft_strsub(line, 0, len);
	new->x = ft_atoi(ft_strchr(line, ' ') + 1);
	new->y = ft_atoi(ft_strrchr(line, ' ') + 1);
	new->type = type;
	new->line_req = (*room)->line_req;
	if (!(*room)->name || type == 's')
		add_room_check(room, &new, line);
	else
		add_room_and_check(room, new, line);
}

void		add_room_check(t_room **room, t_room **new, char *line)
{
	(*new)->line_req = (*room)->line_req;
	(*new)->ants = (*room)->ants;
	if ((*room)->line_req)
		(*new)->line_req = ft_strdup((*room)->line_req);
	(*new)->next = (*room);
	if ((*room)->name)
	{
		if (!ft_strcmp((*new)->name, (*room)->name))
			error_management1(8, line);
		if ((*new)->x == (*room)->x && (*new)->y == (*room)->y)
			error_management1(9, line);
	}
	if (!(*room)->name)
	{
		free((*room));
		(*room) = (*new);
		(*room)->next = NULL;
	}
	(*room) = (*new);
}

void		add_room_and_check(t_room **room, t_room *new, char *line)
{
	t_room	*tmp;

	tmp = (*room);
	while (tmp->next)
	{
		if (!ft_strcmp(new->name, tmp->name))
			error_management1(8, line);
		if (new->x == tmp->x && new->y == tmp->y)
			error_management1(9, line);
		tmp = tmp->next;
	}
	if (!ft_strcmp(new->name, tmp->name))
		error_management1(8, line);
	if (new->x == tmp->x && new->y == tmp->y)
		error_management1(9, line);
	tmp->next = new;
}

void		add_link(t_room **room, char *room_1, char *room_2)
{
	t_room	*tmp;
	t_link	*link;

	tmp = (*room);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, room_1))
		{
			link = find_link(room, room_2);
			if (!tmp->links)
				tmp->links = link;
			else
			{
				link->next = tmp->links;
				tmp->links = link;
			}
			return ;
		}
		tmp = tmp->next;
	}
	error_management1(17, room_1);
}
