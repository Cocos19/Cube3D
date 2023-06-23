/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:27:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/23 13:49:51 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_display(t_display *display, char *map_name)
{

	display->mlx = mlx_init();
	if (!display->mlx)
		strerror_and_exit(display, "mlx init");
	display->win = mlx_new_window(display->mlx, WIDTH, HEIGHT, map_name);
	if (!display->win)
		strerror_and_exit(display, "mlx_new_window");
	display->map = malloc(sizeof(t_map));
	if (!display->map)
		strerror_and_exit(display, "malloc map");
	encode_pixel_rgb(&display->map->celling_color, 50, 200, 100);
	encode_pixel_rgb(&display->map->celling_color, 200, 100, 50);
	display->old_img = NULL;
	display->new_img = NULL;
}

int	main(int argc, char **argv)
{
	t_display	*display;

	display = malloc(sizeof(t_display));
	if (!display)
		strerror_and_exit(display, "malloc display");
	init_display(display, "cub3D");
	mlx_loop_hook (display->mlx, &ft_loop_hook, display);
	mlx_key_hook (display->win, &ft_key_hook, display);
	mlx_hook(display->win, 17, 0, &ft_mlx_hook, display);
	mlx_loop(display->mlx);
	(void) argc;
	(void) argv;
	return (0);
}
