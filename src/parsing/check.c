/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:25 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/24 12:06:10 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_tiles_around(t_display *display, int i, int j)
{
	if ((int)ft_strlen(display->map->tiles[i - 1]) < j + 1
		|| (int)ft_strlen(display->map->tiles[i + 1]) < j + 1
		|| display->map->tiles[i][j - 1] == ' '
		|| display->map->tiles[i][j + 1] == ' '
		|| display->map->tiles[i - 1][j] == ' '
		|| display->map->tiles[i + 1][j] == ' ')
		return (1);
	return (0);
}

int	check_if_tile_is_surrounded(t_display *display, int i, int j)
{
	char	c;

	c = display->map->tiles[i][j];
	if (i == 0 || i == display->map->map_height)
	{
		if (!(c == '1' || c == ' '))
			return (1);
	}
	else if (j == 0 || j == (int)ft_strlen(display->map->tiles[i]) - 1)
	{
		if (!(c == '1' || c == ' '))
			return (1);
	}
	else if (!(c == '1' || c == ' '))
		return (check_tiles_around(display, i, j));
	return (0);
}

int	tile_is_valid(t_display *display, char c, int i, int j)
{
	if (!(check_if_tile_is_surrounded(display, i, j) == 0))
		map_error_and_exit(display, "Map not surrounded by walls");
	if (c == '0' || c == '1' || c == ' ' || c == 'D')
		return (0);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	else if (c == 'P')
		return (2);
	return (-1);
}

t_sprite *get_sprite(t_display *display, t_sprite *sprites_lst, int x, int y)
{
	t_sprite	*new;

	new = malloc(sizeof(t_sprite));
	if (!new)
		strerror_and_exit(display, "malloc new sprite position");
	new->x = x + 0.5;
	new->y = y + 0.5;
	new->dist = 0;
	new->next = sprites_lst;
	sprites_lst = new;
	++display->map->nbr_sprites;
	return (sprites_lst);
}

int	check_map_validity(t_display *display)
{
	int			i;
	int			j;
	int			char_type;
	t_sprite	*sprites_lst;

	i = -1;
	sprites_lst = NULL;
	while (display->map->tiles[++i])
	{
		j = -1;
		while (display->map->tiles[i][++j])
		{
			char_type = tile_is_valid(display, display->map->tiles[i][j], i, j);
			if (char_type == 1)
				init_player_infos(display, display->map->tiles[i][j], i, j);
			else if (char_type == 2)
				sprites_lst = get_sprite(display, sprites_lst, i, j);
			else if (char_type < 0)
				map_error_and_exit(display, "Invalid character on map");
		}
	}
	if (display->map->player->exist == 0)
		map_error_and_exit(display, "No player on map");
	display->map->sprites_array = get_sprites_array(display, sprites_lst);
	return (0);
}
