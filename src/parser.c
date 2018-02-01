/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:59:09 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/01 18:42:15 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			pattern(char **lines, int i)
{
	int		j;
	char	**line;

	line = NULL;
	j = 0;
	while (line[i][j])
	{
		if (line[i][j] == ' ')
		{
			line = ft_strsplit(lines[i + 1], ' ');
			if (line[0] || line[1] || line[2] || ft_strisnumber(line[1])
					|| ft_strisnumber(line[2]))
				return (1);
		}
		else if (line[i][j] == '-')
		{
			line = ft_strsplit(lines[i + 1], ' ');
			if (line[0] || line[1] || struct_exist(line[0])
					|| struct_exist(line[1]))
				return (2);
		}
		j++;
	}
	return (0);
}

void		get_rooms(t_room **map, char **lines, int i)
{
	int		del;
	char	**line;

	line = NULL;
	del = 0;
	line = ft_strsplit(lines[i + 1], ' ');
	map[i]->name = ft_strdup(line[0]);
	map[i]->x = ft_atoi(line[1]);
	map[i]->y = ft_atoi(line[2]);
	while (line[del])
		ft_strdel(&line[del++]);
}

void		get_links(t_room **map, char **lines, int i)
{
	(void)map;
	(void)lines;
	(void)i;
}

t_room		**map_init(t_room **map, char **lines, char *entry)
{
	int			i;
	int			start_end;
	int			room_number;

	i = 0;
	if (!(room_number = estimate_room_number(entry)))
		exit(1);
	map = (t_room **)malloc(sizeof(t_room) * (room_number + 1));
	map[room_number] = NULL;
	while (lines[i])
	{
		start_end = check_start_end(lines, i);
		if (pattern(lines, i) == 0)
			break ;
		if (pattern(lines, i) == 1)
			get_rooms(map, lines, i);
		if (pattern(lines, i) == 2)
			get_links(map, lines, i);
		i++;
	}
	//check_resolvable();
	return (map);
}

t_room		**get_map(void)
{
	t_room		**map;
	int			del;
	char		*entry;
	char		**lines;

	del = 0;
	map = NULL;
	entry = NULL;
	entry = ft_read_standard(500);
	lines = ft_strsplit(entry, '\n');
	map = map_init(map, lines, entry);
	ft_strdel(&entry);
	while (lines[del])
		free(lines[del++]);
	free(lines);
	display_struct(map);
	return (map);
}
