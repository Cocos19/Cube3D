/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:45:45 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/20 15:48:39 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_sprites_distance(t_map *map)
{
	t_sprite *temp;

	temp = map->sprites_lst;
	while(temp)
	{
		temp->dist = pow(map->player->position->x - temp->x, 2)
			+ pow(map->player->position->y - temp->y, 2);
		temp = temp->next;
	}
}
