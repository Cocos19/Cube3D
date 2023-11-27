/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:28:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/27 16:06:19 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_sprite(t_display *display)
{
	int	x;
	int	y;

	x = SPRITE_WIDTH;
	y = SPRITE_HEIGHT;
	display->map->sprite_texture = malloc(sizeof(t_img));
	if (!display->map->sprite_texture)
		strerror_and_exit(display, "malloc sprite");
	display->map->sprite_texture->mlx_img
		= mlx_xpm_file_to_image(display->mlx, "./textures/spr.xpm", &x, &y);
	if (!display->map->sprite_texture->mlx_img)
		strerror_and_exit(display, "performing texture extraction");
	display->map->sprite_texture->addr
		= mlx_get_data_addr(display->map->sprite_texture->mlx_img,
			&display->map->sprite_texture->bpp,
			&display->map->sprite_texture->line_len,
			&display->map->sprite_texture->endian);
}

void	init_minimap_colors_and_sprite(t_display *display)
{
	encode_pixel_rgb(&display->map->minimap_border_color, 145, 85, 61);
	encode_pixel_rgb(&display->map->minimap_floor_color, 220, 208, 186);
	encode_pixel_rgb(&display->map->minimap_walls_color, 145, 85, 61);
	encode_pixel_rgb(&display->map->minimap_empty_color, 110, 208, 186);
	encode_pixel_rgb(&display->map->minimap_player_color, 220, 110, 186);
	encode_pixel_rgb(&display->map->minimap_fov_color, 50, 110, 186);
	encode_pixel_rgb(&display->map->minimap_door_color, 80, 80, 186);
	encode_pixel_rgb(&display->map->minimap_pillar_color, 120, 80, 156);
}

/*
init_map will parse the file given in argument and setup all the variables
needed by the game. In case of redundancy in map informations,
lack of informations or no respect for the map instructions,
init map will throw an error and exit the program.
The map data structures contain textures,
tiles array and all the players informations needed by the raycasting algorithm
*/

void	init_map(t_display *display, char *map_name)
{
	display->map = malloc(sizeof(t_map));
	if (!display->map)
		strerror_and_exit(display, "malloc map");
	init_minimap_colors_and_sprite(display);
	init_sprite(display);
	display->map->player = malloc(sizeof(t_player));
	if (!display->map->player)
		strerror_and_exit(display, "malloc player");
	display->map->player->exist = 0;
	display->map->north_texture = NULL;
	display->map->south_texture = NULL;
	display->map->west_texture = NULL;
	display->map->east_texture = NULL;
	display->map->nbr_sprites = 0;
	display->map->celling_color = -1;
	display->map->floor_color = -1;
	display->map->map_height = 0;
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

t_display	*init_display(char *map_name)
{
	t_display	*display;

	display = malloc(sizeof(t_display));
	if (!display)
		strerror_and_exit(display, "malloc display");
	display->mlx = mlx_init();
	if (!display->mlx)
		strerror_and_exit(display, "mlx init");
	display->win
		= mlx_new_window(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, map_name);
	if (!display->win)
		strerror_and_exit(display, "mlx_new_window");
	display->old_img = NULL;
	display->new_img = NULL;
	display->mouse_x = MOUSE_ORIGIN_X;
	display->mouse_enabled = 1;
	return (display);
}
