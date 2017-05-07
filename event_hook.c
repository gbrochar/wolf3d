/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 02:38:27 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/22 05:25:31 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		red_cross(void)
{
	exit(0);
}

int		check_wall(t_env *e, int keycode)
{
	double	c_sin;
	double	c_cos;

	c_sin = sin((e->camera_alpha - e->fov) / RAD) * 0.3;
	c_cos = cos((e->camera_alpha - e->fov) / RAD) * 0.3;
	if (keycode == 13 && e->map[(int)(e->camera_z - c_sin)]
		[(int)(e->camera_x + c_cos)] == 1)
		return (1);
	if (keycode == 1 && e->map[(int)(e->camera_z + c_sin)]
		[(int)(e->camera_x - c_cos)] == 1)
		return (1);
	if (keycode == 0 && e->map[(int)(e->camera_z + c_cos)]
		[(int)(e->camera_x + c_sin)] == 1)
		return (1);
	if (keycode == 2 && e->map[(int)(e->camera_z - c_cos)]
		[(int)(e->camera_x - c_sin)] == 1)
		return (1);
	return (0);
}

void	check_movement(int keycode, t_env *e)
{
	if (keycode == 13 || keycode == 126)
		if (check_wall(e, 13) == 0)
		{
			e->camera_z -= sin((e->camera_alpha - e->fov) / RAD) * e->sprint;
			e->camera_x += cos((e->camera_alpha - e->fov) / RAD) * e->sprint;
		}
	if (keycode == 1 || keycode == 125)
		if (check_wall(e, 1) == 0)
		{
			e->camera_z += sin((e->camera_alpha - e->fov) / RAD) * e->sprint;
			e->camera_x -= cos((e->camera_alpha - e->fov) / RAD) * e->sprint;
		}
	if (keycode == 0 || keycode == 123)
		if (check_wall(e, 0) == 0)
		{
			e->camera_z += cos((e->camera_alpha - e->fov) / RAD) * e->sprint;
			e->camera_x += sin((e->camera_alpha - e->fov) / RAD) * e->sprint;
		}
	if (keycode == 2 || keycode == 124)
		if (check_wall(e, 2) == 0)
		{
			e->camera_z -= cos((e->camera_alpha - e->fov) / RAD) * e->sprint;
			e->camera_x -= sin((e->camera_alpha - e->fov) / RAD) * e->sprint;
		}
}

int		key_hook(int keycode, void *e_void)
{
	t_env	*e;

	e = (t_env *)e_void;
	check_movement(keycode, e);
	if (keycode == 12)
		e->camera_alpha -= 5;
	if (keycode == 14)
		e->camera_alpha += 5;
	if (keycode == 257)
		e->sprint = (e->sprint == 0.1) ? 0.2 : 0.1;
	if (keycode == 53)
	{
		free(e->map);
		exit(0);
	}
	if (keycode == 78 && e->sensivity > 0.2)
		e->sensivity -= 0.1;
	if (keycode == 69 && e->sensivity < 2)
		e->sensivity += 0.1;
	ray_cast(e);
	return (0);
}

int		cursor_hook(int x, int y, void *e_void)
{
	t_env	*e;

	e = (t_env *)e_void;
	y = 0;
	e->camera_alpha = (int)((double)x * e->sensivity) % 360;
	ray_cast(e);
	return (0);
}
