/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:56:49 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/01 18:30:43 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
#include <stdio.h>
# include "../src/libft/includes/libft.h"

typedef struct	s_room {
	int				id;
	char			*name;
	int				*links;
	int				link_number;
	int				x;
	int				y;
	int				start_end;
	int				ant;
}				t_room;

t_room			**get_map(void);
t_room			**map_init(t_room **map, char **lines, char *entry);
void			launch_ants(t_room **map);

void			display_struct(t_room **map);

/*
 * PARSER UTILS
 */
int				check_start_end(char **lines, int i);
int				estimate_room_number(char *entry);


/*
 * OUPUT
 */
int				free_ret(t_room **map, char **lines, char **line, char *entry);

#endif
