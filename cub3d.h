/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:17:46 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/20 15:48:46 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

/*DISPLAY*/

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define TEXTURE_WIDTH 128
# define TEXTURE_HEIGHT 128
# define SPRITE_WIDTH 32
# define SPRITE_HEIGHT 96
# define MOUSE_ORIGIN_X 960
# define MOUSE_ORIGIN_Y 540

/*MAP PARSING*/

# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define C 5
# define F 6
# define EMPTY_LINE 7
# define MAP 8

/*MINIMAP*/

# define MINIMAP_CENTER_X 1795
# define MINIMAP_CENTER_Y 125
# define MINIMAP_DIAMETER 250
# define MINIMAP_SCALE 20
# define PLAYER_RADIUS 5

/*MATH*/

# define PI 3.14159265

/*KEYS AND BUTTONS*/

# define ESCAPE 53
# define TURN_LEFT 123
# define TURN_RIGHT 124
# define MOVE_FORWARD 13
# define MOVE_BACKWARD 1
# define STRAF_LEFT 0
# define STRAF_RIGHT 2
# define INTERACT 14
# define RIGHT_CLICK 1

/*HOOKS MASKS*/

#define KEYPRESS 2
#define KEYRELEASE 3
#define BUTTONPRESS 4
#define DESTROYNOTIFY 17

/*PLAYER*/

# define HALF_FOV 0.5759586532
# define FOV 1.1519173063 //implentation with angle method value is in radian
# define ROTATION_SPEED 0.1
# define MOVE_SPEED 0.1
# define INTERACT_REACH 3

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_dot
{
	double	x;
	double	y;
}	t_dot;

typedef struct s_dot_index
{
	int	x;
	int	y;
}	t_dot_index;

typedef struct s_sprite
{
	double			x;
	double			y;
	double			dist;
	struct s_sprite	*next;
}	t_sprite;

typedef struct s_ray
{
	t_vector	direction;
	t_vector	side_distance;
	t_vector	delta_distance;
	t_dot_index	origin;
	int			step_x;
	int			step_y;
} t_ray;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	int			exist;
	int			is_moving;
	int			is_strafing;
	int			is_turning;
	t_dot		*position;
	t_vector	*direction;
	t_vector	*plane;
}	t_player;

typedef struct s_map
{
	int			mini_map_border_color;
	int			mini_map_floor_color;
	int			mini_map_walls_color;
	int			mini_map_empty_color;
	int			mini_map_player_color;
	int			mini_map_fov_color;
	int			mini_map_door_color;
	int			mini_map_pillar_color;
	int			celling_color;
	int			floor_color;
	int			map_height;
	int			nbr_sprites;
	t_sprite	*sprites_lst;
	void		*no_texture;
	void		*so_texture;
	void		*we_texture;
	void		*ea_texture;
	void		*sprite_texture;
	char		**tiles;
	t_player	*player;
}	t_map;

typedef struct s_display_datas
{
	int		mouse_x;
	int		mouse_enabled;
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*old_img;
	t_img	*new_img;
}	t_display;

/*ERROR HANDLING*/

void	map_error_and_exit(t_display *display, char *error_msg);
void	strerror_and_exit(t_display *display, char *error_msg);

/*MEMORY FREE*/

void	free_display(t_display *display);

/*IMAGE MANAGEMENT*/

void	encode_pixel_rgb(int *pixel, uint8_t red, uint8_t green, uint8_t blue);
void	render_image(t_img *image, t_display *display);
int		pixel_is_in_minimap(double x, double y);
int		pixel_is_in_minimap_border(double x, double y);
void	put_pixel_on_img(t_img *image, int x, int y, int color);
t_img	*init_image(t_display *display);

/*LOOPS ANF HOOKS*/

int		ft_mlx_hook(t_display *display);
int		ft_loop_hook(t_display *display);
int		ft_key_hook(int key, t_display *display);
int		ft_key_press_hook(int key, t_display *display);
int		ft_key_release_hook(int key, t_display *display);
int		ft_mouse_hook(int key, int x, int y, t_display *display);

/*MAP INIT*/

void	parse_map(t_display *display, char *map_name);
int		check_map_validity(t_display *display);
int		update_map_info(t_display *display, char *str, int info);
int		init_player_infos(t_display *display, char c, int i, int j);

/*Minimap*/

void	put_pixel_on_minimap(t_img *image, t_map *map, t_dot *pixel);
int		pixel_is_in_fov(t_map *map, t_dot *pixel);
int		minimap_raycast(t_map *map, t_dot	*pixel);

/*Moves*/

void	move_forward(t_display *display);
void	move_backward(t_display *display);
void	turn_right(t_display *display);
void	turn_left(t_display *display);
void	move_player(t_display *display);
int		open_door(t_map *map);


#endif
