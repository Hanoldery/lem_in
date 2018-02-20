/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 16:02:39 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/14 16:12:35 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			pattern_room(char **lines, int *i)
{
	char	**line;

	line = ft_strsplit(lines[*i], ' ');
	if (line[0] && line[1] && line[2] && ft_strisnumber(line[1])
			&& ft_strisnumber(line[2]) && !line[3]
			&& ft_strcountchar(lines[*i], ' ') == 2)
	{
		ft_strtabdel(&line);
		return (2);
	}
	ft_strtabdel(&line);
	return (-1);
}
int			pattern_link(char **lines, t_room **map, int *i)
{
	char	**line;

	line = ft_strsplit(lines[*i], '-');
	if (line[0] && line[1] && struct_exist(line[0], map) >= 0
			&& struct_exist(line[1], map) >= 0 && !line[2]
			&& ft_strcmp(line[0], line[1]) != 0
			&& ft_strcountchar(lines[*i], '-') == 1)
		return (free_ret(NULL, NULL, line, 3));
	return (free_ret(NULL, NULL, line, 0));
}

int			pattern_comment(char **lines, int *i, int *j)
{
	if (lines[*i][*j + 1] == '#')
		if (!(ft_strcmp(lines[*i], "##start")
					|| ft_strcmp(lines[*i], "##end")) || *i == 0)
			return (0);
	*i = *i + 1;
	*j = *j - 1;
	return (1);
}
