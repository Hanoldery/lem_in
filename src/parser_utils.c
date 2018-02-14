/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 18:14:04 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/14 10:28:42 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			estimate_room_number(char *entry)
{
	int		i;
	int		count_lines;
	int		count_space;

	count_lines = 0;
	count_space = 0;
	i = 0;
	while (entry[i])
	{
		if (entry[i] == ' ')
			count_space++;
		if (entry[i] == '\n')
		{
			if (count_space == 2)
				count_lines++;
			count_space = 0;
		}
		i++;
	}
	return (count_lines);
}

int			estimate_links_number(char **lines, char *name)
{
	int		i;
	int		del;
	int		count_score;
	char	**line;

	count_score = 0;
	i = 0;
	del = 0;
	while (lines[i])
	{
		if (ft_strfind(lines[i], '-'))
		{
			line = ft_strsplit(lines[i], '-');
			if (ft_strcmp(line[0], name) == 0 || ft_strcmp(line[1], name) == 0)
				count_score++;
			while (line[del])
				free(line[del++]);
			free(line);
			del = 0;
		}
		i++;
	}
	return (count_score);
}

int			make_map_start_end(t_room **map, char *line, int ants)
{
	int		j;

	j = 0;
	while (map[j])
		j++;
	j--;
	if (ft_strcmp(line, "##start") == 0)
	{
		if (struct_start_end_exist(map, -1))
			return (-1);
		map[j]->start_end = -1;
		map[j]->ant = ants;
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		if (struct_start_end_exist(map, 1))
			return (-1);
		map[j]->start_end = 1;
	}
	return (0);
}
