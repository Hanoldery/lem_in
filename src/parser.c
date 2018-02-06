/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:59:09 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/06 17:28:54 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			pattern(char **lines, int *i, t_room **map)
{
	int		j;
	char	**line;

	line = NULL;
	j = 0;
	while (lines[*i][j])
	{
		if (ft_isnumber(lines[*i]))
			return (1);
		if (lines[*i][j] == ' ' && i != 0)
		{
			line = ft_strsplit(lines[*i], ' ');
			if (line[0] && line[1] && line[2] && ft_strisnumber(line[1])
					&& ft_strisnumber(line[2]) && !line[3])
			{
				free(line);
				return (2);
			}
			free(line);
			break ;
		}
		else if (lines[*i][j] == '-' && i != 0)
		{
			line = ft_strsplit(lines[*i], '-');
			if (line[0] && line[1] && struct_exist(line[0], map) >= 0
					&& struct_exist(line[1], map) >= 0 && !line[2]
					&& ft_strcmp(line[0], line[1]) != 0)
				return (free_ret(NULL, NULL, line, 3));
			return (free_ret(NULL, NULL, line, 0));
		}
		while (lines[*i][j] == '#' && j == 0)
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

	j = 0;
	line = NULL;
	del = 0;
	while (map[j])
		j++;
	line = ft_strsplit(lines[i], ' ');
	if (struct_exist(line[0], map) >= 0)
		exit (1); //May have to free
	map[j] = new_struct(lines);
	map[j]->ant = 0;
	if (ft_strcmp(lines[i - 1], "##start") == 0)
	{
		if (struct_start_end_exist(map, -1))
			exit (1);
		map[j]->start_end = -1;
		map[j]->ant = ants;
	}
	if (ft_strcmp(lines[i - 1], "##end") == 0)
	{
		if (struct_start_end_exist(map, 1))
			exit (1);
		map[j]->start_end = 1;
	}
	map[j]->name = ft_strdup(line[0]);
	map[j]->x = ft_atoi(line[1]);
	map[j]->y = ft_atoi(line[2]);
	while (line[del])
		ft_strdel(&line[del++]);
}

int		get_links(t_room **map, char **lines, int i)
{
	char	**line;
	int		repeat;
	int		index;
	int		index_2;

	index_2 = 0;
	repeat = 0;
	index = 0;
	line = ft_strsplit(lines[i], '-');
	while (repeat < 2)
	{
		index = struct_exist(line[repeat], map);
		if (!map[index]->links)
			map[index]->links = (int *)malloc(sizeof(int) *
				estimate_links_number(lines, map[index]->name));
		while (index_2 < map[index]->link_nbr)
			if (map[index]->links[index_2++] == struct_exist(line[!repeat], map))
				return 0;
		map[index]->links[map[index]->link_nbr] = struct_exist(line[!repeat], map);
		map[index]->link_nbr++;
		repeat++;
	}
	return (1);
}

t_room		**map_init(t_room **map, char **lines, char *entry)
{
	int			i;
	int			start_end;
	int			room_number;
	intmax_t	ants;

	i = 0;
	if (!(room_number = estimate_room_number(entry)))
		exit(1);
	ants = 0;
	map = (t_room **)malloc(sizeof(t_room *) * (room_number + 1));
	while (room_number >= 0)
		map[--room_number + 1] = NULL;
	start_end = check_start_end(lines, i);
	if (pattern(lines, &i, map) != 1 || ft_atoimax(lines[i]) < 1 ||
			ft_atoimax(lines[i]) > 2147483647)
		exit (1);
	ants = ft_atoimax(lines[i++]);
	while (lines[i] && pattern(lines, &i, map) == 2)
		get_rooms(map, lines, i++, ants);
	while (lines[i] && pattern(lines, &i, map) == 3)
		if (!get_links(map, lines, i++))
			break;
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
	//check_resolvable();
	ft_strdel(&entry);
	while (lines[del])
		free(lines[del++]);
	free(lines);
	display_struct(map);
	printf("\nFINAL :\n %d\n", resolvable(map, 0, 0, 0));
	return (map);
}
