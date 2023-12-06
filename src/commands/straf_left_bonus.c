/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straf_left_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:18:31 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 13:22:08 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include "../../cub3d_bonus.h"

int	straf_left_x_is_allowed(t_map *map)
{
	int	new_x;
	int	y;

	new_x = map->player->position->x - map->player->direction->y * MOVE_SPEED;
	y = map->player->position->y;
	if (map->tiles[new_x][y] == '0'
		|| tile_is_an_open_door(map, &new_x, &y) == 0)
		return (0);
	else
		return (1);
}

int	straf_left_y_is_allowed(t_map *map)
{
	int	x;
	int	new_y;

	x = map->player->position->x;
	new_y = map->player->position->y + map->player->direction->x * MOVE_SPEED;
	if (map->tiles[x][new_y] == '0'
		|| tile_is_an_open_door(map, &x, &new_y) == 0)
		return (0);
	else
		return (1);
}

void	straf_left(t_display *display)
{
	if (straf_left_x_is_allowed(display->map) == 0)
	{
		display->map->player->position->x
			-= display->map->player->direction->y * MOVE_SPEED;
	}
	if (straf_left_y_is_allowed(display->map) == 0)
	{
		display->map->player->position->y
			+= display->map->player->direction->x * MOVE_SPEED;
	}
}
