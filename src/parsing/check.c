/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:55:25 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/03 10:55:00 by mprofett         ###   ########.fr       */
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

int	is_a_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (0);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (-1);
}

void	update_player_view(t_display *display, char c, int i, int j)
{
	if ((c == 'N' || c == 'S' || c == 'W' || c == 'E')
		&& display->map->player->view_angle != (double)-1)
		map_error_and_exit(display, "More than one player on map");
	else if (c == 'N')
		display->map->player->view_angle = 90;
	else if (c == 'S')
		display->map->player->view_angle = 270;
	else if (c == 'W')
		display->map->player->view_angle = 180;
	else if (c == 'E')
		display->map->player->view_angle = 0;
	display->map->player->x = j + 0.5;
	display->map->player->y = i + 0.5;
}

int	check_map_validity(t_display *display)
{
	int	i;
	int	j;
	int	char_type;

	i = -1;
	while (display->map->tiles[++i])
	{
		j = -1;
		while (display->map->tiles[i][++j])
		{
			char_type = is_a_valid_char(display->map->tiles[i][j]);
			if (char_type == 1)
			{
				update_player_view(display, display->map->tiles[i][j], i, j);
				display->map->tiles[i][j] = '0';
			}
			else if (char_type < 0)
				map_error_and_exit(display, "Invalid character on map");
			if (!(check_if_tile_is_surrounded(display, i, j) == 0))
				map_error_and_exit(display, "Map not surrounded by walls");
		}
	}
	if (display->map->player->view_angle == (double)-1)
		map_error_and_exit(display, "No player on map");
	return (0);
}
