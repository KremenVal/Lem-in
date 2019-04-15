/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:41:50 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/06 17:41:51 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		check_command_and_comment(t_room **room, t_ret **ret, char *line)
{
	if (line[0] == ' ' && ft_strstr(line, "#"))
		error_management1(6, line);
	if (ft_strstr(line, "##") && ft_strstr(line, " ")
		&& (ft_strstr(line, "start") || ft_strstr(line, "end")))
		error_management1(6, line);
	if (!(ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		&& (*room)->ants < 1)
		error_management1(1, line);
	add_line(ret, line);
}

int			check_name(char *line, int i, int j, int num)
{
	int		count;
	int		index;
	char	**mass;

	count = count_space(line);
	mass = ft_strsplit(line, ' ');
	while (mass[i])
		i++;
	index = 0;
	if (i > 1)
		while (mass[++index])
		{
			j = -1;
			while (mass[index][++j])
				if (!ft_isdigit(mass[index][j]))
					num++;
		}
	if ((i == 3 && count != 2) || ((i == 2 || i == 3) && num > 0) || i == 2)
		error_management1(2, line);
	else if ((i == 1 && count != 0) || (i == 2 && num > 0))
		error_management1(7, line);
	if ((i == 2 || i == 3) && ft_strchr(mass[0], '-'))
		error_management1(2, line);
	free_mass(mass);
	return (1);
}

int			check_name_room(char *line, int index)
{
	int		count;
	char	*str;

	if (line[0] == 'L' || check_name(line, 0, -1, 0) != 1)
		error_management1(2, line);
	count = count_space(line);
	if (count != 2)
		return (0);
	str = ft_strdup(ft_strchr(line, ' ') + 1);
	while (ft_isdigit(str[++index]) && str[index])
		;
	if (str[index] != ' ')
	{
		free(str);
		return (0);
	}
	while (ft_isdigit(str[++index]) && str[index])
		;
	if (str[index] != '\0')
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

void		check_same_link(t_room **room, char *room_1, char *room_2,
							char *line)
{
	t_room	*tmp;
	t_link	*link;

	tmp = (*room);
	while (tmp)
	{
		if (tmp->links && !ft_strcmp(tmp->name, room_1))
		{
			link = tmp->links;
			while (link)
			{
				if (!ft_strcmp(link->link->name, room_2))
					error_management1(15, line);
				link = link->next;
			}
		}
		tmp = tmp->next;
	}
}

int			check_path(t_way **way, int i)
{
	int		j;
	int		count;

	count = 0;
	j = -1;
	while (++j < i)
		count += way[i]->len_path - way[j]->len_path;
	return (count);
}
