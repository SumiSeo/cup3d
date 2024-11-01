/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:46:32 by sumseo            #+#    #+#             */
/*   Updated: 2024/11/01 16:56:13 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_look_left(t_data *data)
{
	double	old_dir_x;
	double	old_plne_x;

	old_dir_x = data->dirX;
	data->dirX = data->dirX * cos(data->rotSpeed) - data->dirY
		* sin(data->rotSpeed);
	data->dirY = old_dir_x * sin(data->rotSpeed) + data->dirY
		* cos(data->rotSpeed);
	old_plne_x = data->planeX;
	data->planeX = data->planeX * cos(data->rotSpeed) - data->planeY
		* sin(data->rotSpeed);
	data->planeY = old_plne_x * sin(data->rotSpeed) + data->planeY
		* cos(data->rotSpeed);
}

void	move_look_right(t_data *data)
{
	double	old_dir_x;
	double	old_plne_x;

	old_dir_x = data->dirX;
	data->dirX = data->dirX * cos(-data->rotSpeed) - data->dirY
		* sin(-data->rotSpeed);
	data->dirY = old_dir_x * sin(-data->rotSpeed) + data->dirY
		* cos(-data->rotSpeed);
	old_plne_x = data->planeX;
	data->planeX = data->planeX * cos(-data->rotSpeed) - data->planeY
		* sin(-data->rotSpeed);
	data->planeY = old_plne_x * sin(-data->rotSpeed) + data->planeY
		* cos(-data->rotSpeed);
}