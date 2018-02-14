/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:59:09 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/14 10:32:50 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			pattern(char **lines, int *i, t_room **map)
{
	int		j;
	char	**line;

	line = NULL;
	j = 0;
	if (lines[*i][j] == 'L')
		return (-1);
	while (lines[*i] && lines[*i][j])
	{
		if (ft_isnumber(lines[*i]))
			return (1);
		if (lines[*i][j] == ' ' && i != 0)
		{
			line = ft_strsplit(lines[*i], ' ');
			if (line[0] && line[1] && line[2] && ft_strisnumber(line[1])
					&& ft_strisnumber(line[2]) && !line[3])
			{
				ft_strtabdel(&line);
				return (2);
			}
			ft_strtabdel(&line);
			return (-1);
		}
		else if (lines[*i][j] == '-' && i != 0)
		{
			line = ft_strsplit(lines[*i], '-');
			printf("PATTERN %s\n", lines[*i]);
			if (line[0] && line[1] && struct_exist(line[0], map) >= 0
					&& struct_exist(line[1], map) >= 0 && !line[2]
					&& ft_strcmp(line[0], line[1]) != 0)
				return (free_ret(NULL, NULL, line, 3));
			return (free_ret(NULL, NULL, line, 0));
		}
		while (lines[*i] && lines[*i][j] == '#' && j == 0)
		{
			if (lines[*i][j + 1] == '#')
				if (!(ft_strcmp(lines[*i], "##start")
							|| ft_strcmp(lines[*i], "##end")) || *i == 0)
					return (0);
			*i = *i + 1;
			j--;
		}
		j++;
	}
	return (0);
}

void		get_rooms(t_room **map, char **lines, int i, int ants)
{
	int		del;
	char	**line;
	int		j;
	int		before;

	j = 0;
	line = NULL;
	del = 0;
	before = 1;
	while (map[j])
		j++;
	line = ft_strsplit(lines[i], ' ');
	if (struct_exist(line[0], map) >= 0)
		exit (free_ret(map, lines, line, -1));
	map[j] = new_struct(lines);
	map[j]->ant = 0;
	while (lines[i - before][0] == '#' &&
			ft_strcmp(lines[i - before], "##start") != 0 &&
			ft_strcmp(lines[i - before], "##end") != 0 && i - before > 0)
		before++;
	if (make_map_start_end(map, lines[i - before], ants) == -1)
		exit(free_ret(map, lines, line, -1));
	map[j]->name = ft_strdup(line[0]);
	map[j]->x = ft_atoi(line[1]);
	map[j]->y = ft_atoi(line[2]);
	ft_strtabdel(&line);
}

int		get_links(t_room **map, char **lines, int i)
{
	char	**line;
	int		repeat;
	int		index;

	repeat = 0;
	index = 0;
	line = ft_strsplit(lines[i], '-');
	while (repeat < 2)
	{
		index = struct_exist(line[repeat], map);
		if (!map[index]->links)
			map[index]->links = (int *)malloc(sizeof(int) *
				estimate_links_number(lines, map[index]->name));
		if (ft_intintab(map[index]->links, map[index]->link_nbr,
					struct_exist(line[!repeat], map)) != -1)
			break ; //Wasn't like that before
		map[index]->links[map[index]->link_nbr] = struct_exist(line[!repeat], map);
		map[index]->link_nbr++;
		repeat++;
	}
	ft_strtabdel(&line);
	return (1);
}

t_room		**map_init(t_room **map, char **lines, char *entry)
{
	int			i;
	int			room_number;
	intmax_t	ants;
	int			patt;

	i = 0;
	if (!(room_number = estimate_room_number(entry)))
		exit (free_ret(map, lines, NULL, -1));
	ants = 0;
	patt = 0;
	map = (t_room **)malloc(sizeof(t_room *) * (room_number + 1));
	while (room_number >= 0)
		map[--room_number + 1] = NULL;
	if (pattern(lines, &i, map) != 1 || ft_atoimax(lines[i]) < 1 ||
			ft_atoimax(lines[i]) > 2147483647)
		exit (free_ret(map, lines, NULL, -1));
	ants = ft_atoimax(lines[i++]);
	while (lines[i] && (patt = pattern(lines, &i, map) == 2))
		get_rooms(map, lines, i++, ants);
	if (patt == -1)
		exit (free_ret(map, lines, NULL, -1));
	while (lines[i] && (patt = pattern(lines, &i, map) == 3))
		if (!get_links(map, lines, i++))
			break;
	return (map);
}

t_room		**get_map(void)
{
	t_room		**map;
	char		*entry;
	char		**lines;
	int			start;

	start = 0;
	map = NULL;
	entry = NULL;
	if (!(entry = ft_read_standard(500)))
		exit (free_ret(map, NULL, NULL, -1));
	lines = ft_strsplit(entry, '\n');
	map = map_init(map, lines, entry);
	while (map[start] && map[start]->start_end != -1)
		start++;
	if (!map[start])
		exit (free_ret(map, lines, NULL, -1));
	ft_strtabdel(&lines);
	launch_resolvable(map, entry);
	return (map);
}
