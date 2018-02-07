/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 10:39:27 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/07 18:32:32 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			launch_resolvable(t_room **map)
{
	t_algo		*algo;
	int			size;
	int			start;

	size = 0;
	start = 0;
	printf("LAUNCH_RESOLVE\n");
	while (map[size])
		size++;
	algo = (t_algo *)malloc(sizeof(algo) * 2);
	while (map[start] && map[start]->start_end != -1)
	{
		printf("%s -> %d\n", map[start]->name, map[start]->start_end);
		start++;
	}
	if (!map[start])
	{
		printf("SIZE%d == START%d\n", size, start);
		exit (0); // Verifier avec start sur le dernier parametre
	}
	algo->room_id = start;
	algo->weight = 0;
	algo->steps = 0;
	return (resolvable(map, algo));
}

int			resolvable(t_room **map, t_algo *algo)
{
	int		i;
	int		tmp;
	int		tmp_id;

	tmp = 0;
	tmp_id = 0;
	i = 0;
	printf("\n-----%s---- %d %d %d", map[algo->room_id]->name, map[algo->room_id]->weight, map[algo->room_id]->start_end, algo->steps);
	if (map[algo->room_id]->start_end == 1)
		return (1);
	if (map[algo->room_id]->weight != 0)
		return (map[algo->room_id]->weight + 1);
	algo->steps++;
	while (i < map[algo->room_id]->link_nbr)
	{
		map[algo->room_id]->crossed = 1;
		if (map[map[algo->room_id]->links[i]]->crossed)
		{
			//printf("A.%d.1 CONTINUE (%d)\n", algo->room_id, map[algo->room_id]->links[i]);
			i++;
			continue;
		}
		//printf("\nA.%d.1 --> %d s%d\n", algo->room_id, map[algo->room_id]->links[i], algo->steps);
		tmp_id = algo->room_id;
		algo->room_id = map[algo->room_id]->links[i];
		tmp = resolvable(map, algo);

		//printf("A.%d.2 %d\n", tmp_id, tmp);

		//if (tmp == 0)
		map[algo->room_id]->crossed = 0;
		algo->room_id = tmp_id;
		if ((tmp < map[algo->room_id]->weight || map[algo->room_id]->weight == 0) && tmp != 0)
		{
			map[algo->room_id]->weight = tmp;
		}
		//printf("A.%d.3 weight%d\n", algo->room_id, map[algo->room_id]->weight);

		i++;
	}



	if (map[algo->room_id]->weight == 0)
	{
		algo->steps--;
		printf("%s ->NOTHING\n", map[algo->room_id]->name);
		return (0);
	}
	printf("RETURNED %d\n", map[algo->room_id]->weight + 1);
	return (map[algo->room_id]->weight + 1);
}

void		launch_ants(t_room **map)
{
	(void)map;
}
