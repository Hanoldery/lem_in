/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 18:14:04 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/14 18:16:15 by pgerbaud         ###   ########.fr       */
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
			return (pattern_room(lines, i));
		else if (lines[*i][j] == '-' && i != 0)
			return (pattern_link(lines, map, i));
		while (lines[*i] && lines[*i][j] == '#' && j == 0)
			if (pattern_comment(lines, i, &j) == 0)
				return (0);
		j++;
	}
	if (!lines[*i])
		return (0);
	else
		return (-1);
}

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
		if (struct_start_end_exist(map, -1) != -1)
			return (-1);
		map[j]->start_end = -1;
		map[j]->ant = ants;
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		if (struct_start_end_exist(map, 1) != -1)
			return (-1);
		map[j]->start_end = 1;
	}
	return (0);
}

int			empty_lines(char *entry)
{
	int		i;

	i = 0;
	while (entry[i])
	{
		if (entry[i] == '\n' && entry[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}
