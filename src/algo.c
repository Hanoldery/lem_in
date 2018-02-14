/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:39:27 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/14 18:23:16 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		backtrack_resolvable(t_room **map, t_algo *algo, int *i)
{
	int		tmp;
	int		tmp_id;

	tmp = 0;
	tmp_id = 0;
	map[algo->room_id]->crossed = 1;
	if (map[map[algo->room_id]->links[*i]]->crossed)
	{
		*i = *i + 1;
		return ;
	}
	tmp_id = algo->room_id;
	algo->room_id = map[algo->room_id]->links[*i];
	tmp = resolvable(map, algo);
	algo->room_id = tmp_id;
	if ((tmp < map[algo->room_id]->weight ||
				map[algo->room_id]->weight == 0) && tmp != 0)
		map[algo->room_id]->weight = tmp;
	*i = *i + 1;
}

int			resolvable(t_room **map, t_algo *algo)
{
	int		i;

	i = 0;
	if (map[algo->room_id]->start_end == 1)
		return (1);
	if (map[algo->room_id]->weight != 0)
		return (map[algo->room_id]->weight + 1);
	algo->steps++;
	while (i < map[algo->room_id]->link_nbr)
		backtrack_resolvable(map, algo, &i);
	if (map[algo->room_id]->weight == 0)
	{
		algo->steps--;
		return (0);
	}
	map[algo->room_id]->crossed = 0;
	return (map[algo->room_id]->weight + 1);
}

int			get_lowest_cost_path(t_room **map, int index)
{
	int		i;
	int		lowest;

	i = 0;
	if (!map[index]->links)
		return (0);
	lowest = map[index]->links[i];
	while (i < map[index]->link_nbr)
	{
		if ((map[map[index]->links[i]]->weight <=
					map[lowest]->weight)
			&& (map[map[index]->links[i]]->weight != 0 ||
				map[map[index]->links[i]]->start_end == 1))
			lowest = map[index]->links[i];
		i++;
	}
	return (lowest);
}

void		move_ant(t_room **map, int i, int *moves, int *name_factor)
{
	int		next;

	next = 0;
	next = get_lowest_cost_path(map, i);
	if (map[next]->ant == 1 && !map[next]->crossed && map[next]->start_end != 1
			&& struct_size(map) > 2)
		move_ant(map, next, moves, name_factor);
	if (map[i]->ant && map[i]->start_end != 1
			&& (map[next]->ant == 0 || map[next]->start_end == 1)
			&& !map[i]->crossed)
	{
		if (*moves >= 0)
			ft_putstr(" ");
		ft_putstr("L");
		ft_putnbr(*name_factor);
		ft_putstr("-");
		ft_putstr(map[next]->name);
		map[i]->ant--;
		map[next]->ant++;
		*moves = *moves + 1;
		if (map[next]->start_end != 1)
			map[next]->crossed = 1;
	}
	*name_factor = *name_factor + 1;
}

int			launch_ants(t_room **map)
{
	int		i;
	int		name_factor;
	int		total_ants;
	int		moves;

	i = struct_start_end_exist(map, -1);
	name_factor = 1;
	total_ants = map[struct_start_end_exist(map, -1)]->ant;
	ft_putstr("\n");
	while (map[struct_start_end_exist(map, 1)]->ant != total_ants)
	{
		moves = -1;
		while (map[i])
		{
			move_ant(map, i, &moves, &name_factor);
			name_factor = map[struct_start_end_exist(map, 1)]->ant + 1;
			i++;
		}
		ft_putstr("\n");
		i = 0;
		while (map[i])
			map[i++]->crossed = 0;
		i = struct_start_end_exist(map, -1);
	}
	return (1);
}
