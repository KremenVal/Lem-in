/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:38:47 by vkremen           #+#    #+#             */
/*   Updated: 2019/03/06 17:38:55 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		error_management5(int i, char *line)
{
	if (i == 14)
	{
		ft_printf("Error: Link cann't have the same room - |%s|\n", line);
		exit(1);
	}
	else if (i == 15)
	{
		ft_printf("Error: This link already exist - |%s|\n", line);
		exit(1);
	}
	else if (i == 16)
	{
		ft_printf("Error: Start and End aren't connected\n");
		exit(1);
	}
	else if (i == 17)
	{
		ft_printf("Error: Room %s doesn't exist\n", line);
		exit(1);
	}
	else if (i == 18)
	{
		ft_printf("Error: Incorrect filename\n");
		exit(1);
	}
}

void		error_management4(int i, char *line)
{
	if (i == 9)
	{
		ft_printf("Error: Rooms cannot have the same coordinates - |%s|\n",
			line);
		exit(1);
	}
	else if (i == 10)
	{
		ft_printf("Error: Command start already exist\n");
		exit(1);
	}
	else if (i == 11)
	{
		ft_printf("Error: Command end already exist\n");
		exit(1);
	}
	else if (i == 5)
	{
		(!ft_strcmp(line, "##start")
			? ft_printf("Error: No room for ##start\n")
			: ft_printf("Error: No room for ##end\n"));
		exit(1);
	}
	else
		error_management5(i, line);
}

void		error_management3(int i, char *line)
{
	int		index;

	index = -1;
	if (i == 6)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] != '#')
			error_management1(2, line);
		i = 0;
		while (line[++index])
			if (line[index] == '#')
				i++;
		if (i == 1 || i > 2)
			ft_printf("Error: Bad name for comment - |%s|\n", line);
		else
			ft_printf("Error: Bad name for command - |%s|\n", line);
		exit(1);
	}
	else
		error_management4(i, line);
}

void		error_management2(int i, char *line)
{
	if (i == 12)
	{
		ft_printf("Error: Command start has not been entered\n");
		exit(1);
	}
	else if (i == 13)
	{
		ft_printf("Error: Command end has not been entered\n");
		exit(1);
	}
	else if (i == 7)
	{
		ft_printf("Error: Bad input for link - |%s|\n", line);
		exit(1);
	}
	else if (i == 8)
	{
		ft_printf("Error: Rooms cannot have the same name - |%s|\n", line);
		exit(1);
	}
	else
		error_management3(i, line);
}

void		error_management1(int i, char *line)
{
	if (i == 1)
	{
		ft_printf("Error: Bad ants input - |%s|\n", line);
		exit(1);
	}
	else if (i == 2)
	{
		ft_printf("Error: Bad input for room - |%s|\n", line);
		exit(1);
	}
	else if (i == 3)
	{
		ft_printf("Error: No room for ##start\n");
		exit(1);
	}
	else if (i == 4)
	{
		ft_printf("Error: No room for ##end\n");
		exit(1);
	}
	else
		error_management2(i, line);
}
