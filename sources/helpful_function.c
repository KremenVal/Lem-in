/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:28:30 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/07 17:28:32 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		free_mass(char **mass)
{
	int		index;

	index = -1;
	while (mass[++index])
		free(mass[index]);
	free(mass);
}

int			count_space(char *line)
{
	int		index;
	int		count;

	index = -1;
	count = 0;
	while (line[++index])
		if (line[index] == ' ')
			count++;
	return (count);
}

t_link		*find_link(t_room **room, char *name)
{
	t_room	*tmp;
	t_link	*link;

	tmp = (*room);
	link = (t_link *)ft_memalloc(sizeof(t_link));
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			link->link = tmp;
			return (link);
		}
		tmp = tmp->next;
	}
	return (link);
}

t_room		*find_end(t_room **room)
{
	t_room	*tmp;

	tmp = (*room);
	while (tmp)
	{
		if (tmp->type == 'e')
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void		clear_room(t_room **room)
{
	t_room	*tmp;

	tmp = (*room);
	while (tmp)
	{
		if (tmp->visit && !tmp->block)
			tmp->visit = 0;
		tmp = tmp->next;
	}
}
