/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:27:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/24 16:59:07 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_minimap_colors_and_sprite(t_display *display)
{
	int	x;
	int	y;

	x = SPRITE_WIDTH;
	y = SPRITE_HEIGHT;
	encode_pixel_rgb(&display->map->mini_map_border_color, 145, 85, 61);
	encode_pixel_rgb(&display->map->mini_map_floor_color, 220, 208, 186);
	encode_pixel_rgb(&display->map->mini_map_walls_color, 145, 85, 61);
	encode_pixel_rgb(&display->map->mini_map_empty_color, 110, 208, 186);
	encode_pixel_rgb(&display->map->mini_map_player_color, 220, 110, 186);
	encode_pixel_rgb(&display->map->mini_map_fov_color, 50, 110, 186);
	encode_pixel_rgb(&display->map->mini_map_door_color, 80, 80, 186);
	encode_pixel_rgb(&display->map->mini_map_pillar_color, 120, 80, 156);
	display->map->sprite_texture = malloc(sizeof(t_img));
	if (!display->map->sprite_texture)
		strerror_and_exit(display, "malloc sprite");
	display->map->sprite_texture->mlx_img
		= mlx_xpm_file_to_image(display->mlx, "./textures/pillar.xpm", &x, &y);
	display->map->sprite_texture->addr = mlx_get_data_addr(display->map->sprite_texture->mlx_img, &display->map->sprite_texture->bpp,
			&display->map->sprite_texture->line_len, &display->map->sprite_texture->endian);
	display->map->gun_texture = init_gun_image(display, "./textures/gun1.xpm");
	display->map->gun_texture2 = init_gun_image(display, "./textures/gun2.xpm");
	if (!display->map->sprite_texture)
		strerror_and_exit(display, "performing texture extraction");
}

/*init_map will parse the file given in argument and setup all the variables needed by the game.
In case of redundancy in map informations, lack of informations or no respect for the map instructions, init map will throw an error and exit the program
The map data structures contain textures, tiles array and all the players informations needed by the raycasting algorythm*/

void	init_map(t_display *display, char *map_name)
{
	display->map = malloc(sizeof(t_map));
	if (!display->map)
		strerror_and_exit(display, "malloc map");
	init_minimap_colors_and_sprite(display);
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
	- link to 2 images. The rendering will alternatively push one image to the window while he other image is rendered (in ordrer to avoid lags)
	- information on mouse directional control
	- all the maps datas (tiles, textures, player informations,...)

We need a super data structure like this because all the mlx hooks functions allow only on paramater to be passed to the hook functions*/

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

void	check_if_arguments_are_valid(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strlen(argv[1]) < 5
		|| !(strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5) == 0))
	{
		printf("Invalid Map Format\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_display	*display;

	check_if_arguments_are_valid(argc, argv);
	display = init_display(argv[1]);
	init_map(display, argv[1]);
	mlx_loop_hook (display->mlx, &ft_loop_hook, display);
	mlx_mouse_hide();
	mlx_hook(display->win, BUTTONPRESS, 0, &ft_mouse_hook, display);
	mlx_hook(display->win, KEYPRESS, 0, &ft_key_press_hook, display);
	mlx_hook(display->win, KEYRELEASE, 0, &ft_key_release_hook, display);
	mlx_hook(display->win, DESTROYNOTIFY, 0, &ft_mlx_hook, display);
	mlx_loop(display->mlx);
	return (0);
}
