/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:04:06 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/18 20:04:08 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		print_ways(t_way **way, t_room *room, int index)
{
	t_way	*way_tmp;

	while (way && way[++index])
	{
		way_tmp = way[index];
		while (way_tmp)
		{
			ft_printf("%s", way_tmp->name);
			if (way_tmp->next)
				ft_printf("-");
			way_tmp = way_tmp->next;
		}
		(!way[index + 1] ? ft_printf("\n\n") : ft_printf("\n"));
	}
	if (!way)
		ft_printf("%s\n\n", room->name);
}

void		print_input_and_ways(t_ret *ret, t_way **way, t_room *room,
							int index)
{
	t_ret	*ret_tmp;

	ret_tmp = ret;
	if ((g_flag && ft_strcmp(g_flag, "-c")) || !g_flag)
	{
		while (ret_tmp)
		{
			ft_printf("%s\n", ret_tmp->line);
			ret_tmp = ret_tmp->next;
		}
		ft_printf("\n");
	}
	if (g_flag && !ft_strcmp(g_flag, "-w"))
	{
		ft_printf("Ways:\n");
		print_ways(way, room, index);
	}
}

void		print_movements_2(t_way **way, t_way **tmp, int index)
{
	while ((*tmp)->ant != 0)
	{
		ft_printf("L%d-%s", (*tmp)->ant, (*tmp)->name);
		if ((*tmp)->type == 'e')
		{
			(*tmp)->ant = (*tmp)->prev->ant;
			way[index]->num_ant--;
		}
		else
		{
			(*tmp)->next->ant = (*tmp)->ant;
			if ((*tmp)->prev)
				(*tmp)->ant = (*tmp)->prev->ant;
			else
				(*tmp)->ant = 0;
		}
		if ((*tmp)->prev && (*tmp)->prev->ant != 0)
			ft_printf(" ");
		else
			break ;
		(*tmp) = (*tmp)->prev;
	}
}

int			print_movements(t_way **way, int index, int count)
{
	t_way	*tmp;

	while (way[++index])
	{
		tmp = way[index];
		while (tmp && !tmp->ant)
			tmp = tmp->next;
		while (tmp && tmp->next && tmp->next->ant != 0)
			tmp = tmp->next;
		if (way[index]->num_ant > 0)
			print_movements_2(way, &tmp, index);
		if (way[index]->num_ant > 0)
			count++;
		if (way[index + 1] && way[index + 1]->num_ant > 0)
			ft_printf(" ");
	}
	ft_printf("\n");
	g_count_line++;
	return (count);
}

void		move_ants(t_way **way, int ants, int ant)
{
	t_way	*tmp;
	int		index;
	int		flag;

	flag = 1;
	while (flag)
	{
		index = -1;
		while (way[++index])
		{
			tmp = way[index];
			if (ants > check_path(way, index) && !tmp->ant)
			{
				tmp->ant = ant++;
				way[index]->num_ant++;
				ants--;
			}
		}
		flag = print_movements(way, -1, 0);
	}
	if (g_flag && !ft_strcmp(g_flag, "-c"))
		ft_printf("\t%s\n\t#Here is the number of lines recieved: %d\n",
			way[0]->line_req, g_count_line);
}
