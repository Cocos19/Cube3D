/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:28:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/03 13:59:07 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*init_sprite(t_display *display, char *path)
{
	t_img	*result;
	int		x;
	int		y;

	x = SPRITE_WIDTH;
	y = SPRITE_HEIGHT;
	result = malloc(sizeof(t_img));
	if (!result)
		strerror_and_exit(display, "malloc sprite");
	result->mlx_img = mlx_xpm_file_to_image(display->mlx, path, &x, &y);
	if (!result->mlx_img)
		strerror_and_exit(display, "performing texture extraction");
	result->addr = mlx_get_data_addr(result->mlx_img, &result->bpp,
			&result->line_len, &result->endian);
	if (!result->addr)
		strerror_and_exit(display, "performing sprite get_data_address");
	return (result);
}

void	init_bonus_textures_and_colors(t_display *display)
{
	encode_pixel_rgb(&display->map->minimap_border_color, 145, 85, 61);
	encode_pixel_rgb(&display->map->minimap_floor_color, 220, 208, 186);
	encode_pixel_rgb(&display->map->minimap_walls_color, 145, 85, 61);
	encode_pixel_rgb(&display->map->minimap_empty_color, 110, 208, 186);
	encode_pixel_rgb(&display->map->minimap_player_color, 220, 110, 186);
	encode_pixel_rgb(&display->map->minimap_fov_color, 50, 110, 186);
	encode_pixel_rgb(&display->map->minimap_door_color, 80, 80, 186);
	encode_pixel_rgb(&display->map->minimap_pillar_color, 120, 80, 156);
	display->map->door_texture
		= init_texture_image(display, "./textures/door.xpm");
	display->map->sprite_1 = init_sprite(display, "./textures/spr1.xpm");
	display->map->sprite_2 = init_sprite(display, "./textures/spr2.xpm");
	display->map->sprite_3 = init_sprite(display, "./textures/spr3.xpm");
	display->map->sprite_texture = display->map->sprite_1;
	display->map->nbr_sprites = 0;
}

/*
init_map will parse the file given in argument and setup all the variables
needed by the game. In case of redundancy in map informations,
lack of informations or no respect for the map instructions,
init map will throw an error and exit the program.
The map data structures contain textures,
tiles array and all the players informations needed by the raycasting algorithm
*/

void	init_player(t_display *display)
{
	display->map->player = malloc(sizeof(t_player));
	if (!display->map->player)
		strerror_and_exit(display, "malloc player");
	display->map->player->exist = 0;
	display->map->player->direction = NULL;
	display->map->player->position = NULL;
	display->map->player->plane = NULL;
}

void	init_map(t_display *display, char *map_name)
{
	display->map = malloc(sizeof(t_map));
	if (!display->map)
		strerror_and_exit(display, "malloc map");
	display->map->north_texture = NULL;
	display->map->south_texture = NULL;
	display->map->west_texture = NULL;
	display->map->east_texture = NULL;
	display->map->door_texture = NULL;
	display->map->sprite_1 = NULL;
	display->map->sprite_2 = NULL;
	display->map->sprite_3 = NULL;
	display->map->sprites_array = NULL;
	display->map->door_lst = NULL;
	display->map->tiles = NULL;
	display->map->celling_color = -1;
	display->map->floor_color = -1;
	display->map->map_height = 0;
	init_player(display);
	init_bonus_textures_and_colors(display);
	parse_map(display, map_name);
}

/*init_display is the main data structure in the program, it contain:
	- all data needed by the mlx function (mlx and win)
	- link to 2 images. The rendering will alternatively push one image
		to the window while he other image is rendered (in ordrer to avoid lags)
	- information on mouse directional control
	- all the maps datas (tiles, textures, player informations,...)

We need a super data structure like this because all the mlx hooks functions
allow only on paramater to be passed to the hook functions*/

void	init_display(t_display *display, char *map_name)
{
	display->mlx = mlx_init();
	if (!display->mlx)
		strerror_and_exit(display, "mlx init");
	display->win
		= mlx_new_window(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, map_name);
	if (!display->win)
		strerror_and_exit(display, "mlx_new_window");
	display->screen_img = NULL;
	display->mouse_x = MOUSE_ORIGIN_X;
	display->mouse_enabled = 1;
}
