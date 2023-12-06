/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:27:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 10:51:13 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_if_arguments_are_valid(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_display	display;

	check_if_arguments_are_valid(argc, argv);
	init_display(&display, argv[1]);
	init_map(&display, argv[1]);
	mlx_loop_hook (display.mlx, &ft_loop_hook, &display);
	mlx_mouse_hide();
	mlx_hook(display.win, BUTTONPRESS, 0, &ft_mouse_hook, &display);
	mlx_hook(display.win, KEYPRESS, 0, &ft_key_press_hook, &display);
	mlx_hook(display.win, KEYRELEASE, 0, &ft_key_release_hook, &display);
	mlx_hook(display.win, DESTROYNOTIFY, 0, &ft_mlx_hook, &display);
	mlx_loop(display.mlx);
	return (0);
}

static void	check_if_arguments_are_valid(int argc, char **argv)
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
