/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:40:00 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/14 17:05:26 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			struct_same_coord(char **line, t_room **map)
{
	int		i;

	i = 0;
	if (ft_atoi(line[1]) > INT_MAX || ft_atoi(line[1]) < 0 ||
		ft_atoi(line[2]) > INT_MAX || ft_atoi(line[2]) < 0)
		return (0);
	while (map && map[i])
	{
		if (map[i]->x == ft_atoi(line[1]) && map[i]->y == ft_atoi(line[2]))
			return (0);
		i++;
	}
	return (1);
}

int			struct_exist(char *name, t_room **map)
{
	int		i;

	i = 0;
	while (map[i] && map[i]->name)
	{
		if (ft_strcmp(map[i]->name, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int			struct_start_end_exist(t_room **map, int start_end)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (map[i]->start_end == start_end)
			return (i);
		i++;
	}
	return (-1);
}

t_room		*new_struct(char **lines)
{
	t_room	*new;

	(void)lines;
	new = (t_room *)malloc(sizeof(t_room));
	new->id = 0;
	new->name = NULL;
	new->links = NULL;
	new->link_nbr = 0;
	new->x = 0;
	new->y = 0;
	new->start_end = 0;
	new->ant = 0;
	new->crossed = 0;
	new->weight = 0;
	return (new);
}

int			struct_size(t_room **map)
{
	int		i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
