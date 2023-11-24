/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:48:37 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/24 17:10:20 by mprofett         ###   ########.fr       */
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

t_img	*init_gun_image(t_display *display, char *path)
{
	t_img	*result;
	int		x;
	int		y;

	x = 768;
	y = 768;
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

void	render_minimap(t_img *image, t_display *display)
{
	int		x;
	int		y;
	t_dot	pixel;

	x = MINIMAP_CENTER_X - MINIMAP_DIAMETER / 2;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < MINIMAP_DIAMETER)
		{
			if (pixel_is_in_minimap_border(x, y) == 0)
				put_pixel_on_img(image, x, y,
					display->map->mini_map_border_color);
			else if (pixel_is_in_minimap(x, y) == 0)
			{
				pixel.x = x;
				pixel.y = y;
				put_pixel_on_minimap(image, display->map, &pixel);
			}
		}
	}
}

void	render_background(t_img *image, t_display *display)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
			{
					put_pixel_on_img(image, x, y,
						display->map->celling_color);
			}
			else
				put_pixel_on_img(image, x, y, display->map->floor_color);
		}
	}
}

void	raycast(t_map *map, int *x, t_img *img)
{
	double		cameraX;
	t_vector	ray_direction;
	t_vector	side_distance;
	t_vector	delta_distance;
	t_dot_index	map_location;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;

	cameraX = 2 * *x / (double)(SCREEN_WIDTH) - 1;
	ray_direction.x = map->player->direction->x + map->player->plane->x * cameraX;
	ray_direction.y = map->player->direction->y + map->player->plane->y * cameraX;
	map_location.x = (int)map->player->position->x;
	map_location.y = (int)map->player->position->y;
	hit = 0;
	stepX = 0;
	stepY = 0;
	if (ray_direction.x == 0)
		delta_distance.x = 1e30;
	else
		delta_distance.x = fabs(1 / ray_direction.x);
	if (ray_direction.y == 0)
		delta_distance.y = 1e30;
	else
		delta_distance.y = fabs(1 / ray_direction.y);
	if (ray_direction.x < 0)
	{
		stepX = -1;
		side_distance.x = (map->player->position->x - map_location.x) * delta_distance.x;
	}
	else
	{
		stepX = 1;
		side_distance.x = (map_location.x + 1.0 - map->player->position->x) * delta_distance.x;
	}
	if (ray_direction.y < 0)
	{
		stepY = -1;
		side_distance.y = (map->player->position->y - map_location.y) * delta_distance.y;
	}
	else
	{
		stepY = 1;
		side_distance.y = (map_location.y + 1.0 - map->player->position->y) * delta_distance.y;
	}
	while(hit == 0)
	{
		if (side_distance.x < side_distance.y)
		{
			side_distance.x += delta_distance.x;
			map_location.x += stepX;
			side = 0;
		}
		else
		{
			side_distance.y += delta_distance.y;
			map_location.y += stepY;
			side = 1;
		}
		if (map->tiles[map_location.x][map_location.y] == '1')
			hit = 1;
		else if (map->tiles[map_location.x][map_location.y] == 'D')
			hit = 2;
	}
	if(side == 0)
		map->player->walls_perp_distance[*x] = (side_distance.x - delta_distance.x);
	else
		map->player->walls_perp_distance[*x] = (side_distance.y - delta_distance.y);

	//

	double	wall_x;
	t_dot_index	texture_position;

	if (side == 0)
		wall_x = map->player->position->y + map->player->walls_perp_distance[*x] * ray_direction.y;
	else
		wall_x = map->player->position->x + map->player->walls_perp_distance[*x] * ray_direction.x;
	wall_x -= floor((wall_x));
	texture_position.x = (int)(wall_x * TEXTURE_WIDTH);
	if ((side == 0 && ray_direction.x > 0) || (side == 1 && ray_direction.y < 0))
		texture_position.x = TEXTURE_WIDTH - texture_position.x - 1;

	//

	int lineHeight = (int)(SCREEN_HEIGHT / map->player->walls_perp_distance[*x]);
	int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	if(drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
	if(drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;
	// while (drawStart < drawEnd)
	// {
	// 	if (hit == 1)
	// 		put_pixel_on_img(img, *x, drawStart, map->mini_map_fov_color);
	// 	else
	// 		put_pixel_on_img(img, *x, drawStart, map->mini_map_door_color);
	// 	++drawStart;
	// }

	double	step;
	double	texture_dist;

	step = 1.0 * TEXTURE_HEIGHT / lineHeight;
	texture_dist = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
	while (drawStart < drawEnd)
	{
		texture_position.y = (int)texture_dist;
		texture_dist += step;
		if ((*(int *)(map->north_texture->addr + (map->north_texture->line_len * texture_position.y + texture_position.x * (map->north_texture->bpp / 8))) & 0x00FFFFFF) != 0)
			put_pixel_on_img(img, *x, drawStart, *(int *)(map->north_texture->addr + (map->north_texture->line_len * texture_position.y + texture_position.x * (map->north_texture->bpp / 8))));
		++drawStart;
	}
}

void	render_image(t_img *image, t_display *display)
{
	int	x;

	render_background(image, display);
	x = -1;
	while(++x < SCREEN_WIDTH)
		raycast(display->map, &x, image);
	// render_sprites(display->map, image, display->map->sprite_texture);
	render_minimap(image, display);
}
