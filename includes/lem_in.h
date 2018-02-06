/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:56:49 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/06 17:28:52 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
#include <stdio.h>
# include "../src/libft/includes/libft.h"
//Change Makefile, it's not compiling on change of ft_strfind
typedef struct	s_room {
	int				id;
	char			*name;
	int				*links;
	int				link_nbr;
	int				x;
	int				y;
	int				start_end;
	int				ant;
}				t_room;

t_room			**get_map(void);
t_room			**map_init(t_room **map, char **lines, char *entry);
void			launch_ants(t_room **map);

/*
 * STRUCT UTILS
 */
void			display_struct(t_room **map);
t_room			*new_struct(char **lines);
int				struct_exist(char *name, t_room **map);
int				struct_start_end_exist(t_room **map, int s);

/*
 * PARSER UTILS
 */
int				check_start_end(char **lines, int i);
int				estimate_room_number(char *entry);
int				estimate_links_number(char **lines, char *name);

/*
 * OUPUT
 */
int				free_ret(t_room **map, char **lines, char **line, int ret);

/*
 * ALGO
 */
int				resolvable(t_room **map, int room_id, int weight, int step);

#endif
