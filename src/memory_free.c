/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:30:11 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/01 10:40:02 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_display(t_display *display)
{
	if (display->mlx && display->win)
		mlx_clear_window(display->mlx, display->win);
	if (display->win)
		mlx_destroy_window(display->mlx, display->win);
	if (display->mlx)
		free(display->mlx);
	free(display);
}

void	map_error_and_exit(t_display *display, char *error_msg)
{
	if (display)
		free_display(display);
	ft_printf("Error\n%s\n", error_msg);
	exit (EXIT_FAILURE);
}

void	strerror_and_exit(t_display *display, char *error_msg)
{
	if (display)
		free_display(display);
	ft_printf("Error when %s: %s\n", error_msg, strerror(errno));
	exit (EXIT_FAILURE);
}
