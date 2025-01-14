/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:56:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/11/18 12:56:26 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

short int	start_colors(char *str)
{
	short int	i;

	i = -1;
	while (str[++i] && str[i] != 'C' && str[i] != 'F')
		;
	while (str[++i] && str[i] == ' ')
		;
	return (i);
}
