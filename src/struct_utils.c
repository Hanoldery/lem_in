/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:40:00 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/13 16:26:02 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		display_struct(t_room **map)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (map[i])
	{
		printf("   ___________ MAP %d ___________\n", map[i]->id);
		printf("NAME _%s_\nLINKS[]\t", map[i]->name);
		while (j < map[i]->link_nbr && map[i]->link_nbr != 0)
			printf("%d -- ", map[i]->links[j++]);
		j = 0;
		printf("\nSTART_END %d\t", map[i]->start_end);
		printf("x%d y%d\t\t", map[i]->x, map[i]->y);
		printf("ants%d\n\n", map[i]->ant);
		i++;
	}
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
	return (0);
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
