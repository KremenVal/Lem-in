/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:29:26 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/06 17:29:28 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		check_room(t_room *room)
{
	if (!room->next && !room->links && !room->x && !room->y && !room->ants
		&& !room->type && !room->name)
		error_management1(18, "");
	else if (!room->next || !room->links || !room->x || !room->y || !room->ants
		|| !room->type || !room->name)
	{
		ft_printf("Error: Not enough data\n");
		exit(1);
	}
}

void		shortest_way(t_room *room, t_ret *ret, int ants)
{
	int		ant;

	ant = 1;
	print_input_and_ways(ret, NULL, room, -1);
	while (ant <= ants)
	{
		ft_printf("L%d-%s", ant, room->name);
		if (ant < ants)
			ft_printf(" ");
		ant++;
	}
	ft_printf("\n");
	if (g_flag && !ft_strcmp(g_flag, "-c"))
	{
		ft_printf("\t#Here is the number of lines recieved: 1\n");
		ft_printf("\t#Here is the number of lines recieved: %d\n",
			g_count_line + 1);
	}
	exit(1);
}

void		main_2(int *fd, int argc, char **argv)
{
	if (argc > 1 && !ft_strcmp(argv[1], "-help"))
		usage();
	if (argc > 1)
	{
		if (ft_strcmp(argv[1], "-w") != 0 && ft_strcmp(argv[1], "-c") != 0)
			(*fd) = open(argv[1], O_RDONLY);
		if (argc == 3)
			g_flag = ft_strdup(argv[2]);
		else if (!ft_strcmp(argv[1], "-w") || !ft_strcmp(argv[1], "-c"))
			g_flag = ft_strdup(argv[1]);
	}
}

int			main(int argc, char **argv)
{
	t_room	*room;
	t_way	**way;
	t_ret	*ret;
	int		fd;

	fd = 0;
	g_flag = NULL;
	g_count_line = 0;
	main_2(&fd, argc, argv);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	ret = NULL;
	reading_input(&room, &ret, fd);
	check_room(room);
	if (!room->line_req)
		room->line_req = ft_strdup("#Here is the number of lines required: 0");
	way = breadth_first_search(&room, ret, 1);
	if (!way[0])
		error_management1(16, "");
	print_input_and_ways(ret, way, room->next, -1);
	move_ants(way, room->ants, 1);
	return (0);
}
