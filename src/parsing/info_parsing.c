/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:17:42 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 15:51:32 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_img	*load_texture(t_display *display, char *str)
{
	t_img	*result;
	char	*path;
	char	*start;
	int		i;

	start = str;
	i = 0;
	while (*(str + i) != '\0' && *(str + i) != '\n' && *(str + i) != ' ')
		++i;
	path = ft_strndup(start, i - 1);
	if (!path)
		strerror_and_exit(display, "malloc texture info");
	str = str + i;
	str = ft_skip_character(str, ' ');
	if (str && !(*str == '\n' || *str == '\0'))
		map_error_and_exit(display, "Wrong argument format");
	result = init_texture_image(display, path);
	free(path);
	return (result);
}

char	*get_numeric_argument(t_display *display, char *str, int *nbr)
{
	char	*start;
	char	*str_to_convert;
	int		i;

	i = 0;
	start = str;
	while (ft_isdigit((unsigned char)*(str + i)))
		++i;
	str_to_convert = ft_strndup(start, i - 1);
	if (ft_atoi(str_to_convert, nbr) != 0)
		map_error_and_exit(display, "Wrong argument format");
	else if (*nbr > 255 || *nbr < 0)
		map_error_and_exit(display, "Wrong argument format");
	str = str + i;
	str = ft_skip_character(str, ' ');
	free(str_to_convert);
	return (str);
}

int	get_color_info(t_display *display, char *str)
{
	int	result;
	int	r;
	int	g;
	int	b;

	str = get_numeric_argument(display, str, &r);
	str = get_numeric_argument(display, str, &g);
	str = get_numeric_argument(display, str, &b);
	if (*str != '\n' && *str != '\0')
		map_error_and_exit(display, "Wrong argument format");
	encode_pixel_rgb(&result, r, g, b);
	return (result);
}

int	update_map_info(t_display *display, char *str, int info)
{
	str = ft_skip_character(str, ' ');
	if (info == NO && !display->map->north_texture)
		display->map->north_texture = load_texture(display, str);
	else if (info == SO && !display->map->south_texture)
		display->map->south_texture = load_texture(display, str);
	else if (info == WE && !display->map->west_texture)
		display->map->west_texture = load_texture(display, str);
	else if (info == EA && !display->map->east_texture)
		display->map->east_texture = load_texture(display, str);
	else if (info == C && display->map->celling_color == -1)
		display->map->celling_color = get_color_info(display, str);
	else if (info == F && display->map->floor_color == -1)
		display->map->floor_color = get_color_info(display, str);
	else
		map_error_and_exit(display, "Wrong argument format");
	return (info);
}
