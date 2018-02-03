/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:59:09 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/03 20:13:15 by pgerbaud         ###   ########.fr       */
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
		{
			printf("\tPATTERN number lines_%s_ i%d\n", lines[*i], *i);
			return (1);
		}
		if (lines[*i][j] == ' ' && i != 0)
		{
			line = ft_strsplit(lines[*i], ' ');
			printf("\tPATTERN room lines_%s_ i%d \n", lines[*i], *i);
			if (line[0] && line[1] && line[2] && ft_strisnumber(line[1])
					&& ft_strisnumber(line[2]))
			{
				free(line);
				return (2);
			}
			free(line);
			break ;
		}
		else if (lines[*i][j] == '-' && i != 0)
		{
			printf("\tPATTERN link lines_%s_ i%d\n", lines[*i], *i);
			line = ft_strsplit(lines[*i], '-');
			if (line[0] && line[1] && struct_exist(line[0], map)
					&& struct_exist(line[1], map))
			{
				printf("\tPATTERN link lines_%s_ i%d\n", lines[*i], *i);
				return (free_ret(NULL, NULL, line, 3));
			}
			printf("\tPATTERN link lines_%s_ i%d\n", lines[*i], *i);
			return (free_ret(NULL, NULL, line, 0));
		}
		while (lines[*i][j] == '#' && j == 0)
		{
			if (lines[*i][j + 1] == '#')
				if (!(ft_strcmp(lines[*i], "##start") || ft_strcmp(lines[*i], "##end")))
				{
					printf("\tPATTERN false command lines_%s_ i%d\n", lines[*i], *i);
					return (0);
				}
			printf("\tPATTERN command/comment lines_%s_ i%d\n", lines[*i], *i);
			*i = *i + 1;
			j--;
		}
		j++;
	}
	printf("\tPATTERN broke lines_%s_ i%d\n\n", lines[*i], *i);
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
	if (struct_exist(line[0], map))
		exit (1); //May have to free
	map[j] = new_struct(lines);
	map[j]->ant = 0;
	if (ft_strcmp(lines[i - 1], "##start") == 0)
	{
		map[j]->start_end = -1;
		map[j]->ant = ants;
	}
	map[j]->name = ft_strdup(line[0]);
	map[j]->x = ft_atoi(line[1]);
	map[j]->y = ft_atoi(line[2]);
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
	intmax_t	ants;

	i = 0;
	if (!(room_number = estimate_room_number(entry)))
		exit(1);
	ants = 0;
	map = (t_room **)malloc(sizeof(t_room *) * (room_number + 1));
	while (room_number >= 0)
		map[--room_number + 1] = NULL;
	printf("MAP_INIT 0 ---------------- %p %d\n", map[4], room_number);
	//while (lines[i])
	//{
		start_end = check_start_end(lines, i);
		if (pattern(lines, &i, map) != 1)
			exit (1);
		ants = ft_atoimax(lines[i++]);
		while (lines[i] && pattern(lines, &i, map) == 2)
			get_rooms(map, lines, i++, ants);
		while (lines[i] && pattern(lines, &i, map) == 3)
			get_links(map, lines, i++);
		//if (lines[i] && pattern(lines, &i, map) == 0)
		//	break ;
	//	if (lines[i])
	//		i++;
	//}
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
	return (map);
}
