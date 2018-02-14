/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:27:14 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/02/14 10:28:09 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_ret(t_room **map, char **lines, char **line, int ret)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map && map[i])
	{
		if (map[i]->name)
			ft_strdel(&map[i]->name);
		if (map[i]->links) // May bring problems
			free(map[i]->links);
		free(map[i]);
		i++;
	}
	if (ret < 0)
		ft_putstr("ERROR\n");
	if (map)
		free(map);
	ft_strtabdel(&lines);
	ft_strtabdel(&line);
	return ((ret < 0) ? -ret : ret);
}
