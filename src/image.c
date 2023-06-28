/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:48:37 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/28 15:32:49 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	encode_pixel_rgb(int *pixel, uint8_t red, uint8_t green, uint8_t blue)
{
	*pixel = (red << 16 | green << 8 | blue);
}

void	put_pixel_on_img(t_img *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->addr + (y * image->line_len + x * (image->bpp / 8));
	*(int *)pixel = color;
}

t_img	*init_image(t_display *display)
{
	t_img	*result;

	result = malloc(sizeof(t_img));
	if (!result)
		strerror_and_exit(display, "init_image");
	result->mlx_img = mlx_new_image(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!result->mlx_img)
		strerror_and_exit(display, "mlx_new_image");
	result->addr = mlx_get_data_addr(result->mlx_img, &result->bpp,
			&result->line_len, &result->endian);
	if (!result->addr)
		strerror_and_exit(display, "mlx_get_data_addr");
	return (result);
}

void	render_background(t_img *image, t_display *display)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
			{
				if (pixel_is_in_minimap_border(x, y) == 0)
					put_pixel_on_img(image, x, y,
						display->map->mini_map_border_color);
				else if (pixel_is_in_minimap(x, y) == 0)
					put_pixel_on_img(image, x, y,
						display->map->mini_map_floor_color);
				else
					put_pixel_on_img(image, x, y,
						display->map->celling_color);
			}
			else
				put_pixel_on_img(image, x, y, display->map->floor_color);
		}
	}
}
