/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 13:40:01 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/22 04:44:36 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**get_map(char *str)
{
	int		i;
	int		fd;
	char	*line;
	char	**map;

	i = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		free(line);
	}
	close(fd);
	if (!(map = (char **)malloc((i + 1) * sizeof(char *))))
		return (NULL);
	map[i] = NULL;
	i = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
		map[i++] = line;
	close(fd);
	return (map);
}

int		check_player(int **map, t_env *e)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
		++i;
	while (map[0][j] != 255)
		++j;
	if (check_player_2(map, e, j))
		return (1);
	if (check_border(i, j, map))
		return (1);
	return (0);
}

void	del(char **map_str)
{
	int		i;

	i = 0;
	while (map_str[i])
		free(map_str[i++]);
	free(map_str);
}

int		**check_map(char **map_str, t_env *e)
{
	int		**map;
	int		tab_len;
	int		i;

	if (!map_str)
		return (NULL);
	if (ft_strtab_isdigit(map_str) == 0)
		return (NULL);
	i = 0;
	while (map_str[i])
		++i;
	if (!(map = (int **)malloc((i + 1) * sizeof(int *))))
		return (NULL);
	map[i] = NULL;
	i = -1;
	while (map_str[++i])
	{
		map[i] = ft_atoi_split(map_str[i], ' ', &tab_len);
		map[i][tab_len] = 255;
	}
	del(map_str);
	if (check_player(map, e))
		return (NULL);
	return (map);
}

int		parse_map(t_env *e, char *str)
{
	if (!(e->map = check_map(get_map(str), e)))
		return (1);
	return (0);
}
