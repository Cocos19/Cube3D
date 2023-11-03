/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:17:46 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/03 16:20:09 by mprofett         ###   ########.fr       */
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
# define PLAYER_RADIUS 5

/*MATH*/

# define PI 3.14159265

typedef struct s_vector
{
	double	x;
	double	y;
}	t_coord;

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
	double	x;
	double	y;
	double	view_angle;
	double	view_field;
}	t_player;

typedef struct s_map
{
	int			mini_map_border_color;
	int			mini_map_floor_color;
	int			mini_map_walls_color;
	int			mini_map_empty_color;
	int			mini_map_player_color;
	int			mini_map_fov_color;
	int			celling_color;
	int			floor_color;
	int			map_height;
	void		*no_texture;
	void		*so_texture;
	void		*we_texture;
	void		*ea_texture;
	char		**tiles;
	t_player	*player;
}	t_map;

/*GRID RULES
'0': empty space
'1': wall
'N': player start face north
'S': player start face south
'E': player start face east
'W': player start face west
' ': void
*/

typedef struct s_display_datas
{
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

/*MAP INIT*/

void	read_map(t_display *display, char *map_name);
int		check_map_validity(t_display *display);
int		update_map_info(t_display *display, char *str, int info);

/*Minimap*/

void	put_pixel_on_minimap(t_img *image, t_map *map, int *x, int *y);
int		pixel_is_in_fov(t_map *map, t_coord *pixel);
double	get_angle_between_player_and_pixel(t_coord *pixel);

#endif
