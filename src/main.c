/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:27:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/28 15:33:25 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_map(t_display *display, char *map_name)
{
	display->map = malloc(sizeof(t_map));
	if (!display->map)
		strerror_and_exit(display, "malloc map");
	encode_pixel_rgb(&display->map->mini_map_border_color, 145, 85, 61);
	encode_pixel_rgb(&display->map->mini_map_floor_color, 220, 208, 186);
	display->map->player = malloc(sizeof(t_player));
	if (!display->map->player)
		strerror_and_exit(display, "malloc player");
	display->map->player->x = 0;
	display->map->player->y = 0;
	display->map->player->view_angle = -1;
	display->map->player->view_field = 0;
	display->map->no_texture = NULL;
	display->map->so_texture = NULL;
	display->map->we_texture = NULL;
	display->map->ea_texture = NULL;
	display->map->celling_color = -1;
	display->map->floor_color = -1;
	display->map->map_height = 1;
	read_map(display, map_name);
}

void	init_display(t_display *display, char *map_name)
{
	display->mlx = mlx_init();
	if (!display->mlx)
		strerror_and_exit(display, "mlx init");
	display->win
		= mlx_new_window(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, map_name);
	if (!display->win)
		strerror_and_exit(display, "mlx_new_window");
	init_map(display, map_name);
	display->old_img = NULL;
	display->new_img = NULL;
}

int	main(int argc, char **argv)
{
	t_display	*display;

	display = malloc(sizeof(t_display));
	if (!display)
		strerror_and_exit(display, "malloc display");
	if (!(argc == 2) && ft_strlen(argv[1]) < 5
		&& !(strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5) == 0))
		map_error_and_exit(display, "Wrong arguments passed to the progran");
	init_display(display, argv[1]);
	mlx_loop_hook (display->mlx, &ft_loop_hook, display);
	mlx_key_hook (display->win, &ft_key_hook, display);
	mlx_hook(display->win, 17, 0, &ft_mlx_hook, display);
	mlx_loop(display->mlx);
	(void) argc;
	(void) argv;
	return (0);
}
