/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:17:03 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/22 01:50:27 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_y_text(t_env *e, int y)
{
	int		y_text;

	if (e->real_height <= 240)
	{
		y_text = (WINY - e->height) / 2;
		y_text = y - y_text;
		y_text = (double)y_text / (double)e->height * 64;
	}
	else
	{
		y_text = (e->real_height - WINY) / 2;
		y_text += y;
		y_text = (double)y_text / (double)e->real_height * 64;
	}
	return (y_text);
}

void	pixel_put(t_env *e, int x, int y)
{
	int		index;
	int		index_text;
	int		y_text;

	y_text = get_y_text(e, y);
	index = (x * (e->bpp / 8)) + (y * e->sz_l);
	index_text = (e->text_x * (e->bppt / 8)) + (y_text * e->t_l);
	if (e->sky == 0)
	{
		e->data[index + 2] = e->text[index_text + 2];
		e->data[index + 1] = e->text[index_text + 1];
		e->data[index] = e->text[index_text];
	}
	else
	{
		e->data[index + 2] = e->color_sky / (256 * 256);
		e->data[index + 1] = (e->color_sky / 256) % 256;
		e->data[index] = e->color_sky % 256;
	}
}
