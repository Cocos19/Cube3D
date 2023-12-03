/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:34:13 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/03 20:11:27 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*map_text_and_colors(t_display *display, char *next_line, int fd);
static int	is_map_texture_or_color(t_display *display, char *map_line);
static int	map_info_is_complete(t_display *display);
static char	**get_map_tiles(t_display *display, char *next_line, int fd);

void	parse_map(t_display *display, char *map_name)
{
	int		fd;
	char	*path;
	char	*next_line;

	if (ft_strncmp("maps/", map_name, 5) == 0)
		fd = open(map_name, O_RDONLY);
	else
	{
		path = ft_strjoin("maps/", map_name);
		fd = open(path, O_RDONLY);
		free(path);
	}
	if (fd < 0)
		strerror_and_exit(display, "opening map file");
	next_line = get_next_line(fd, 100);
	if (!next_line)
		map_error_and_exit(display, "Empty map file");
	next_line = map_text_and_colors(display, next_line, fd);
	display->map->tiles = get_map_tiles(display, next_line, fd);
	if (!display->map->tiles)
		map_error_and_exit(display, "Empty Map");
	check_map_validity(display);
	if (display->map->player->exist == 0)
		map_error_and_exit(display, "No player on map");
	close(fd);
}

static char	*map_text_and_colors(t_display *display, char *next_line, int fd)
{
	int	info_type;

	info_type = is_map_texture_or_color(display, next_line);
	while (!(info_type == -1) && !(info_type == MAP))
	{
		if (next_line)
			free(next_line);
		next_line = get_next_line(fd, 100);
		if (next_line)
			info_type = is_map_texture_or_color(display, next_line);
	}
	if (!(map_info_is_complete(display) == 0))
	{
		if (info_type == -1)
			map_error_and_exit(display, "Wrong argument format 1");
		else
			map_error_and_exit(display, "Invalid map content");
	}
	if (info_type == -1)
		map_error_and_exit(display, "Invalid map content");
	return (next_line);
}

static int	is_map_texture_or_color(t_display *display, char *map_line)
{
	char	*str;

	str = ft_skip_character(map_line, ' ');
	if (*str == 'N' && *(str + 1) == 'O' && *(str + 2) == ' ' )
		return (update_map_info(display, str + 2, NO));
	else if (*str == 'S' && *(str + 1) == 'O' && *(str + 2) == ' ' )
		return (update_map_info(display, str + 2, SO));
	else if (*str == 'W' && *(str + 1) == 'E' && *(str + 2) == ' ' )
		return (update_map_info(display, str + 2, WE));
	else if (*str == 'E' && *(str + 1) == 'A' && *(str + 2) == ' ' )
		return (update_map_info(display, str + 2, EA));
	else if (*str == 'C' && *(str + 1) == ' ')
		return (update_map_info(display, str + 1, C));
	else if (*str == 'F' && *(str + 1) == ' ')
		return (update_map_info(display, str + 1, F));
	else if (*str == '\n')
		return (EMPTY_LINE);
	else if (*str == '1')
		return (MAP);
	return (-1);
}

static int	map_info_is_complete(t_display *display)
{
	if (display->map->north_texture && display->map->south_texture
		&& display->map->west_texture && display->map->east_texture
		&& display->map->celling_color != -1 && display->map->floor_color != -1)
		return (0);
	return (1);
}

static char	**get_map_tiles(t_display *display, char *next_line, int fd)
{
	char	**temp_tab;
	char	*temp;

	temp_tab = malloc(sizeof(char **));
	if (!temp_tab)
		strerror_and_exit(display, "malloc map tiles");
	temp_tab[0] = NULL;
	while (next_line)
	{
		temp = ft_strndup(next_line, ft_strlen(next_line) - 2);
		free(next_line);
		temp_tab = ft_add_to_str_array(temp_tab, temp);
		next_line = get_next_line(fd, 100);
		if (next_line && next_line[0] == '\n')
			map_error_and_exit(display, "Empty line on map content");
		++display->map->map_height;
	}
	return (temp_tab);
}
