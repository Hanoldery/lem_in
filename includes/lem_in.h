/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:56:49 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/13 16:15:18 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
#include <stdio.h>
# include "../src/libft/includes/libft.h"
//Change Makefile, it's not compiling on change of ft_strfind
//Afficher ERROR quand c'est pas bon
typedef struct	s_room {
	int				id;
	char			*name;
	int				*links;
	int				link_nbr;
	int				x;
	int				y;
	int				start_end;
	int				ant;
	int				crossed;
	int				weight;
}				t_room;

typedef struct	s_algo {
	int			room_id;
	int			weight;
	int			steps;
}				t_algo;

t_room			**get_map(void);
t_room			**map_init(t_room **map, char **lines, char *entry);

/*
 * STRUCT UTILS
 */
void			display_struct(t_room **map);
t_room			*new_struct(char **lines);
int				struct_exist(char *name, t_room **map);
int				struct_size(t_room **map);
int				struct_start_end_exist(t_room **map, int s);

/*
 * PARSER UTILS
 */
//int				check_start_end(char **lines, int i);
int				estimate_room_number(char *entry);
int				estimate_links_number(char **lines, char *name);
int				make_map_start_end(t_room **map, char *line, int ants);

/*
 * OUPUT
 */
int				free_ret(t_room **map, char **lines, char **line, int ret);

/*
 * ALGO
 */
int				resolvable(t_room **map, t_algo *algo);
int				launch_resolvable(t_room **map, char *entry);
int				launch_ants(t_room **map);

#endif
