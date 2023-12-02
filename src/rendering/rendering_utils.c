/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:38:15 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/05 15:48:06 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	encode_pixel_rgb(int *pixel, uint8_t red, uint8_t green, uint8_t blue)
{
	*pixel = (red << 16 | green << 8 | blue);
}

t_img	*init_texture_image(t_display *display, char *path)
{
	t_img	*result;
	int		x;
	int		y;

	x = TEXTURE_WIDTH;
	y = TEXTURE_HEIGHT;
	result = malloc(sizeof(t_img));
	if (!result)
		strerror_and_exit(display, "malloc texture");
	result->mlx_img = mlx_xpm_file_to_image(display->mlx, path, &x, &y);
	if (!result->mlx_img)
		strerror_and_exit(display, "texture_mlx_new_image");
	result->addr = mlx_get_data_addr(result->mlx_img, &result->bpp,
			&result->line_len, &result->endian);
	if (!result->addr)
		strerror_and_exit(display, "texture_mlx_get_data_addr");
	return (result);
}

void	put_pixel_on_img(t_img *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->addr + (y * image->line_len + x * (image->bpp / 8));
	*(int *)pixel = color;
}

int	get_pixel_color(t_img *texture, t_dot_index *texture_position)
{
	int	texture_index;

	texture_index = texture->line_len * texture_position->y
		+ texture_position->x * texture->bpp / 8;
	return (*(int *)(texture->addr + texture_index));
}

t_img	*init_screen_image(t_display *display)
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
