/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 09:29:05 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/22 01:45:01 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	reverse(double *n, double *old_n)
{
	while (*n < 0)
		(*n)++;
	*n = 1 - *n;
	while (*old_n < 0)
		(*old_n)++;
	*old_n = 1 - *old_n;
}

void	get_color(t_env *e, double x, double y)
{
	double		old_x;
	double		old_y;

	old_x = x - e->dx + e->camera_x;
	old_y = y - e->dy + e->camera_z;
	x += e->camera_x;
	y += e->camera_z;
	if (x < 0)
		reverse(&x, &old_x);
	if (y < 0)
		reverse(&y, &old_y);
	if ((int)old_y != (int)y)
	{
		while (x > 1)
			x--;
		e->text_x = (x / (double)1) * 64;
	}
	else
	{
		while (y > 1)
			y--;
		e->text_x = (y / (double)1) * 64;
	}
}

void	get_height_and_color(t_env *e, int i)
{
	double		x;
	double		y;

	x = e->x / 5000;
	y = e->y / 5000;
	e->dx = x;
	e->dy = y;
	while (e->map[(int)(y + e->camera_z)][(int)(x + e->camera_x)] != 1)
	{
		x += e->dx;
		y += e->dy;
	}
	get_color(e, x, y);
	x *= 64;
	y *= 64;
	e->distance = sqrt((x * x) + (y * y));
	e->distance = (double)e->distance * (double)cos((((double)i / (double)WINX
	* (double)e->fov) - ((double)e->fov / (double)2)) / (double)RAD);
	if (e->distance > 0)
		e->height = (double)(64 * e->screen_dist) / (double)e->distance;
	else
		e->height = WINY;
	if (e->height > WINY || e->height < 0)
		e->height = WINY;
	e->real_height = (double)(64 * e->screen_dist) / (double)e->distance;
}

void	print_column(int column, t_env *e)
{
	int		i;

	i = 0;
	e->color_sky = 0x4444FF;
	e->sky = 1;
	while (i != (WINY / 2) - (e->height / 2))
	{
		pixel_put(e, column, i);
		++i;
	}
	e->sky = 0;
	while (i != (WINY / 2) + (e->height / 2))
	{
		pixel_put(e, column, i);
		++i;
	}
	e->color_sky = 0x00888888;
	e->sky = 1;
	while (i != WINY)
	{
		pixel_put(e, column, i);
		++i;
	}
}

void	ray_cast(t_env *e)
{
	int		i;

	i = 0;
	while (i != WINX)
	{
		e->alpha = (((((double)i / (double)WINX) * (double)e->fov)
					+ e->camera_alpha)) / RAD;
		e->y = cos(e->alpha);
		e->x = sin(e->alpha);
		get_height_and_color(e, i);
		print_column(i, e);
		++i;
	}
	mlx_put_image_to_window(e->ptr, e->win, e->img, 0, 0);
}
