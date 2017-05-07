/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_isdigit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 08:48:47 by gbrochar          #+#    #+#             */
/*   Updated: 2016/05/31 08:50:05 by gbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strtab_isdigit(char **strtab)
{
	int		i;
	int		j;

	i = 0;
	while (strtab[i])
	{
		j = 0;
		while (strtab[i][j])
		{
			if (strtab[i][j] != ' ' && ft_isdigit(strtab[i][j] == 0))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
