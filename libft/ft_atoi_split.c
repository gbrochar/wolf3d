/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 08:52:54 by gbrochar          #+#    #+#             */
/*   Updated: 2016/06/21 22:19:03 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_atoi_split(char *str, char c, int *tab_len)
{
	int		*tab;
	char	**str_tab;
	int		i;

	if (!str || ft_isdigit(c))
		return (NULL);
	str_tab = ft_strsplit(str, c);
	i = 0;
	while (str_tab[i])
		++i;
	if (!(tab = (int *)malloc((i + 1) * sizeof(int))))
		return (NULL);
	*tab_len = i;
	i = -1;
	while (str_tab[++i])
		tab[i] = atoi(str_tab[i]);
	i = 0;
	while (str_tab[i])
		free(str_tab[i++]);
	free(str_tab);
	return (tab);
}
