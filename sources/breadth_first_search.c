/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:00:17 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/08 15:00:19 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		create_way(t_way **way, t_room **room, int len)
{
	t_way	*new;
	t_room	*end;

	end = find_end(room);
	while (end->prev)
	{
		new = (t_way *)ft_memalloc(sizeof(t_way));
		new->name = end->name;
		new->type = end->type;
		if (!(*way))
			(*way) = new;
		else
		{
			new->next = (*way);
			(*way) = new;
			(*way)->next->prev = new;
		}
		len++;
		end = end->prev;
		end->block = 1;
		if (!end->prev)
			(*way)->line_req = (*room)->line_req;
	}
	(*way)->len_path = len;
}

int			add_path(t_path **stack)
{
	t_link	*link;
	t_path	*new;
	t_path	*tmp;

	link = (*stack)->room->links;
	tmp = (*stack);
	while (tmp->next)
		tmp = tmp->next;
	while (link)
	{
		if (!link->link->visit && !link->link->block)
		{
			link->link->visit = 1;
			new = (t_path *)ft_memalloc(sizeof(t_path));
			new->room = link->link;
			tmp->next = new;
			link->link->prev = (*stack)->room;
			if (tmp->room->type == 'e')
				return (0);
			tmp = tmp->next;
		}
		link = link->next;
	}
	return (1);
}

void		find_path_2(t_room **room, t_way **way, t_path **stack)
{
	t_path	*tmp;
	t_path	*del;

	tmp = (*stack);
	while ((*stack))
	{
		del = (*stack);
		if (!add_path(stack))
		{
			create_way(way, room, 0);
			while ((*stack))
			{
				del = (*stack);
				(*stack) = (*stack)->next;
				free(del);
			}
			clear_room(room);
			return ;
		}
		(*stack) = (*stack)->next;
		free(del);
	}
}

void		find_path(t_room **room, t_way **way, t_path *stack, t_link *link)
{
	t_path	*new;
	t_path	*tmp;

	while (link)
	{
		if (!link->link->visit && !link->link->block)
		{
			link->link->visit = 1;
			new = (t_path *)ft_memalloc(sizeof(t_path));
			new->room = link->link;
			new->room->prev = (*room);
			if (!stack)
			{
				stack = new;
				tmp = stack;
			}
			else
			{
				tmp->next = new;
				tmp = tmp->next;
			}
		}
		link = link->next;
	}
	find_path_2(room, way, &stack);
}

t_way		**breadth_first_search(t_room **room, t_ret *ret, int count_path)
{
	t_way	**way;
	t_path	*stack;
	t_link	*link;
	int		index;

	count_path = count_pathes(room);
	way = (t_way **)ft_memalloc(sizeof(t_way *) * count_path);
	stack = NULL;
	index = -1;
	(*room)->visit = 1;
	link = (*room)->links;
	while (link)
	{
		if (link->link->type == 'e')
			shortest_way(link->link, ret, (*room)->ants);
		link = link->next;
	}
	while (++index < count_path)
	{
		link = (*room)->links;
		find_path(room, &way[index], stack, link);
	}
	return (way);
}
