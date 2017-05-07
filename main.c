/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 13:01:43 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/22 05:29:43 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_texture(t_env *e)
{
	if (!(e->img_text = mlx_new_image(e->ptr, WINX, WINY)))
	{
		mlx_destroy_window(e->ptr, e->win);
		free(e->ptr);
		return (1);
	}
	if (open("textures/stone.xpm", O_RDONLY) == -1)
		return (1);
	e->img_text = mlx_xpm_file_to_image(e->ptr, "textures/stone.xpm",
		&(e->width), &(e->height_t));
	if (!(e->text = mlx_get_data_addr(e->img_text, &e->bppt, &e->t_l, &e->e_t)))
	{
		mlx_destroy_image(e->ptr, e->img_text);
		mlx_destroy_window(e->ptr, e->win);
		free(e->ptr);
		return (1);
	}
	e->t_i = ft_strlen(e->data);
	return (0);
}

int		init_mlx(t_env *e)
{
	if (!(e->ptr = mlx_init()))
		return (1);
	if (!(e->win = mlx_new_window(e->ptr, WINX, WINY, "wolf3d")))
	{
		free(e->ptr);
		return (1);
	}
	if (!(e->img = mlx_new_image(e->ptr, WINX, WINY)))
	{
		mlx_destroy_window(e->ptr, e->win);
		free(e->ptr);
		return (1);
	}
	if (!(e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sz_l, &e->endian)))
	{
		mlx_destroy_image(e->ptr, e->img);
		mlx_destroy_window(e->ptr, e->win);
		free(e->ptr);
		return (1);
	}
	e->sz_i = ft_strlen(e->data);
	mlx_hook(e->win, 2, 1L << 1, key_hook, e);
	mlx_hook(e->win, 6, 1L << 1, cursor_hook, e);
	mlx_hook(e->win, 17, 1L << 1, red_cross, e);
	return (0);
}

int		init_env(t_env *e)
{
	int		i;

	i = 0;
	e->fov = FOV;
	e->screen_dist = (double)((double)WINX / (double)2) / (double)tan(30 / RAD);
	e->camera_alpha = 0;
	e->camera_y = 32;
	e->sensivity = 1;
	e->sprint = 0.1;
	return (get_texture(e));
}

int		main(int argc, char **argv)
{
	t_env	e;

	if (argc == 2)
	{
		if (parse_map(&e, argv[1]))
			ft_error("parsing error\n");
		if (init_mlx(&e))
			ft_error("mlx initialisation error\n");
		if (init_env(&e))
			ft_error("texture not found\n");
		ray_cast(&e);
		mlx_loop(e.ptr);
	}
	else
		ft_putstr("usage: ./wolf3d file_name\n");
	return (0);
}
