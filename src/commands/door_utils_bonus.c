/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:22:53 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/04 18:52:07 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_door	*get_door(t_door *door_lst, int x, int y);

int	get_door_status(t_door *door_lst, int x, int y)
{
	t_door	*door;

	door = get_door(door_lst, x, y);
	if (door)
		return (door->is_open);
	else
		return (-1);
}

void	change_door_status(t_map *map, int *x, int *y)
{
	t_door	*door;

	door = get_door(map->door_lst, *x, *y);
	if (door->is_open == DOOR_IS_OPEN)
		door->is_open = DOOR_IS_CLOSED;
	else
		door->is_open = DOOR_IS_OPEN;
}

static t_door	*get_door(t_door *door_lst, int x, int y)
{
	t_door	*temp;

	temp = door_lst;
	while (temp)
	{
		if (temp->x == x && temp->y == y)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	add_to_door_lst(t_display *display, int *x, int *y)
{
	t_door	*new_door;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		strerror_and_exit(display, "malloc on door list");
	new_door->x = *x;
	new_door->y = *y;
	new_door->is_open = DOOR_IS_CLOSED;
	new_door->next = NULL;
	if (!display->map->door_lst)
		display->map->door_lst = new_door;
	else
	{
		new_door->next = display->map->door_lst;
		display->map->door_lst = new_door;
	}
}
