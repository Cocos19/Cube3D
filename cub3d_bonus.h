/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angassin <angassin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:17:46 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/06 13:18:23 by angassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/*MINIMAP*/

# define MINIMAP_CENTER_X 1795
# define MINIMAP_CENTER_Y 125
# define MINIMAP_DIAMETER 250
# define MINIMAP_SCALE 20
# define PLAYER_RADIUS 5

/*KEYS AND BUTTONS*/

# define DOOR_IS_OPEN 0
# define DOOR_IS_CLOSED 1

/*IMAGE MANAGEMENT*/

int			pixel_is_in_minimap(double x, double y);
int			pixel_is_in_minimap_border(double x, double y);

/*MINIMAP*/

void		put_pixel_on_minimap(t_img *image, t_map *map, t_dot *pixel);
int			pixel_is_in_fov(t_map *map, t_dot *pixel);
int			minimap_raycast(t_map *map, t_dot	*pixel);

/*Moves*/

int			open_or_close_door(t_map *map);
int			get_door_status(t_door *door_lst, int x, int y);
int			tile_is_an_open_door(t_map *map, int *x, int *y);
void		add_to_door_lst(t_display *display, int *x, int *y);
void		change_door_status(t_map *map, int *x, int *y);

/*Sprites*/

t_sprite	**get_sprites_array(t_display *display, t_sprite *sprites_lst);
void		sort_sprites_array(t_sprite **sprites_array, int first, int last);
void		render_sprites(t_map *map, t_img *screen, t_img *texture);
void		get_sprites_distance(t_map *map);

#endif
