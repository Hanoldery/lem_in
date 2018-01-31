/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgerbaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:56:49 by pgerbaud          #+#    #+#             */
/*   Updated: 2018/01/31 18:52:46 by pgerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
#include <stdio.h>
# include "../libft/includes/libft.h"

typedef struct	s_room {
	int				id;
	char			*name;
	int				*connected_room;
	int				x;
	int				y;
	int				start_end;
	int				ant;
	struct s_room	*next;
	struct s_room	*prev;
}				t_room;

#endif
