/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 13:00:25 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/22 05:29:58 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "mlx.h"
# include "math.h"

# define WINX 720
# define WINY 600

# define FOV 60
# define RAD 57.2958

typedef struct	s_env
{
	void		*ptr;
	void		*win;
	void		*img;
	char		*data;
	int			sz_l;
	int			sz_i;
	int			endian;
	int			bpp;

	int			width;
	int			height_t;

	void		*img_text;
	char		*text;
	int			t_l;
	int			t_i;
	int			e_t;
	int			bppt;
	int			text_x;

	int			**map;

	double		camera_x;
	int			camera_y;
	double		camera_z;
	double		camera_alpha;
	int			fov;
	double		screen_dist;

	double		alpha;
	double		x;
	double		y;
	double		dx;
	double		dy;

	double		sensivity;
	double		sprint;

	double		distance;
	int			height;
	int			real_height;
	int			color;
	int			color_sky;
	int			sky;
}				t_env;

int				init_mlx(t_env *e);
int				init_env(t_env *e);

int				parse_map(t_env *e, char *str);
char			**get_map(char *str);
int				**check_map(char **map_str, t_env *e);
int				check_player(int **map, t_env *e);
int				check_player_2(int **map, t_env *e, int size_mem);
int				check_border(int i, int j, int **map);

int				check_wall(t_env *e, int keycode);

int				key_hook(int keycode, void *e_void);
int				red_cross(void);
int				cursor_hook(int x, int y, void *e_void);
void			pixel_put(t_env *e, int x, int y);

void			ray_cast(t_env *e);
void			get_height_and_color(t_env *e, int i);
void			print_column(int i, t_env *e);

#endif
