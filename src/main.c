/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:59:02 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/01 14:58:09 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_all(t_room **map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		free(map[i]->name);
		free(map[i]);
	}
	free(map);
	*map = NULL;
}

int		main(void)
{
	t_room		**map;

	map = get_map();
	launch_ants(map);
	free_all(map);
	return (0);
}
