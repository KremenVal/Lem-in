/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:16:20 by vkremen           #+#    #+#             */
/*   Updated: 2019/02/13 15:16:24 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"

typedef struct		s_room
{
	struct s_room	*next;
	struct s_room	*prev;
	struct s_link	*links;
	int				x;
	int				y;
	int				ants;
	int				visit;
	int				block;
	char			type;
	char			*name;
	char			*line_req;
}					t_room;

typedef struct		s_link
{
	struct s_room	*link;
	struct s_link	*next;
}					t_link;

typedef struct		s_ret
{
	struct s_ret	*next;
	char			*line;
}					t_ret;

typedef struct		s_way
{
	struct s_way	*next;
	struct s_way	*prev;
	int				ant;
	int				num_ant;
	int				len_path;
	char			type;
	char			*name;
	char			*line_req;
}					t_way;

typedef struct		s_path
{
	struct s_path	*next;
	struct s_room	*room;
}					t_path;

/*
**reading.c
*/

int					g_count_line;
char				*g_flag;
void				reading_input(t_room **room, t_ret **ret, int fd);
void				reading_ants(t_room **room, t_ret **ret, int fd,
									char *line);
void				reading_rooms(t_room **room, t_ret **ret, int fd,
									char **line);
int					reading_rooms_next(t_room **room, t_ret **ret, int fd,
									char *line);
int					reading_links(t_room **room, t_ret **ret, int fd,
									char *line);

/*
**checking.c
*/

void				check_command_and_comment(t_room **room, t_ret **ret,
									char *line);
int					check_name(char *line, int i, int j, int num);
int					check_name_room(char *line, int index);
void				check_same_link(t_room **room, char *room_1, char *room_2,
									char *line);
int					check_path(t_way **way, int i);

/*
**error_management.c
*/

void				error_management1(int i, char *line);
void				error_management2(int i, char *line);
void				error_management3(int i, char *line);
void				error_management4(int i, char *line);
void				error_management5(int i, char *line);

/*
**add_list.c
*/

void				add_line(t_ret **ret, char *line);
void				add_room(t_room **room, char *line, int len, char type);
void				add_room_and_check(t_room **room, t_room *new, char *line);
void				add_room_check(t_room **room, t_room **new, char *line);
void				add_link(t_room **room, char *room_1, char *room_2);

/*
**validation.c
*/

int					check_start(t_room **room, t_ret **ret, int fd, char *line);
int					check_end(t_room **room, t_ret **ret, int fd, char *line);
void				check_start_and_end(t_room **room, int count_s,
									int count_e);
void				check_link(t_room **room, t_ret **ret, char *line);
int					count_pathes(t_room **room);

/*
**helpful_function.c
*/

void				free_mass(char **mass);
int					count_space(char *line);
t_link				*find_link(t_room **room, char *name);
t_room				*find_end(t_room **room);
void				clear_room(t_room **room);

/*
**breadth_first_search.c
*/

t_way				**breadth_first_search(t_room **room, t_ret *ret,
									int count_path);
void				find_path(t_room **room, t_way **way, t_path *stack,
									t_link *link);
void				find_path_2(t_room **room, t_way **way, t_path **stack);
int					add_path(t_path **stack);
void				create_way(t_way **way, t_room **room, int len);

/*
**main.c
*/

void				main_2(int *fd, int argc, char **argv);
void				shortest_way(t_room *room, t_ret *ret, int ants);
void				check_room(t_room *room);

/*
**print_result.c
*/

void				print_ways(t_way **way, t_room *room, int index);
void				print_input_and_ways(t_ret *ret, t_way **way, t_room *room,
									int index);
void				print_movements_2(t_way **way, t_way **tmp, int index);
int					print_movements(t_way **way, int index, int count);
void				move_ants(t_way **way, int ants, int ant);

/*
**some_bonuses.c
*/

void				usage(void);

#endif
