/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:39:27 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/06 18:17:59 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			resolvable(t_room **map, int room_id, int weight, int step)
{
	int		i;
	int		tmp;

	tmp = 0;
	i = 0;
	printf("A.%d.0\n", room_id);
	if (step > 1000)
		return (0);
	while (i < map[room_id]->link_nbr)
	{
		printf("A.%d.1\n", room_id);
		
		tmp = resolvable(map, map[room_id]->links[i], weight, ++step);
		printf("A.%d.2\n", room_id);
		if (tmp != 0 && tmp < weight)
			weight = tmp;
		printf("A.%d.3\n", room_id);
		i++;
	}
	printf("A.%d.4\n", room_id);
	if (map[room_id]->start_end == 1)
		return (1);
	printf("A.%d.5\n", room_id);
	if (weight == 0)
		return (0);
	printf("A.%d.6\n", room_id);
	return (weight + 1);
}

void		launch_ants(t_room **map)
{
	(void)map;
}
