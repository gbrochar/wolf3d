/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 04:04:19 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/22 05:24:30 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_border(int i, int j, int **map)
{
	int		i1;
	int		j1;

	i1 = 0;
	j1 = 0;
	j--;
	i--;
	if (map[i][j] != 1)
		return (1);
	while (i1 != i)
		if (map[i1++][j1] != 1)
			return (1);
	i1 = 0;
	while (i1 != i)
		if (map[i1++][j] != 1)
			return (1);
	i1 = 0;
	while (j1 != j)
		if (map[i1][j1++] != 1)
			return (1);
	j1 = 0;
	while (j1 != j)
		if (map[i][j1++] != 1)
			return (1);
	return (0);
}

int		check_i_j(int **map, int i, int j, t_env *e)
{
	if (map[i][j] == 2)
	{
		e->camera_x = j + 0.5;
		e->camera_z = i + 0.5;
		return (1);
	}
	return (0);
}

int		check_player_2(int **map, t_env *e, int size_mem)
{
	int		i;
	int		j;
	int		player;
	int		size;

	player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		size = 0;
		while (map[i][j] != 255)
		{
			if (check_i_j(map, i, j, e))
				player++;
			size++;
			++j;
		}
		if (size != size_mem)
			return (1);
		++i;
	}
	if (player != 1)
		return (1);
	return (0);
}
