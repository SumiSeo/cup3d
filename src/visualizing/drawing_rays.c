/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:19:05 by sumseo            #+#    #+#             */
/*   Updated: 2024/11/07 15:08:27 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_img(t_image *img, int x, int y, int color)
{
	img->data[y * (img->line_length / sizeof(int)) + x] = color;
}

void	verLine(t_data *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		put_pixel_to_img(&info->mlx.map, x, y, color);
		// img->data[y * (img->line_length / sizeof(int)) + x] = color;
		y++;
	}
}

void	draw_floor_ceiling(t_data *info, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	if (draw_end < 0)
		return ;
	while (y < draw_start)
	{
		put_pixel_to_img(&info->mlx.map, x, y, info->mlx.screen->ceiling_color);
		y++;
	}
	y = draw_end + 1;
	while (y < HEIGHT)
	{
		put_pixel_to_img(&info->mlx.map, x, y, info->mlx.screen->floor_color);
		y++;
	}
}

void	draw_rays(t_data *info)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	int		hit;
	int		side;
	int		size_y;
	int		texNum;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
	int		texY;

	size_y = find_len_strs(info->mlx.parsing->map);
	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		rayDirX = info->dirX + info->planeX * cameraX;
		rayDirY = info->dirY + info->planeY * cameraX;
		mapX = (int)info->posX;
		mapY = (int)info->posY;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		hit = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (info->mlx.parsing->map[mapX][mapY] != '0')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		// texNum = info->mlx.parsing->map[mapX][mapY] - '0';
		texNum = 6;
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;
		step = 1.0 * texHeight / lineHeight;
		texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			color = info->texture[texNum][texHeight * texY + texX];
			// printf("color %d\n", color);
			if (side == 1)
				color = (color >> 1) & 8355711;
			put_pixel_to_img(&info->mlx.map, x, y, color);
			// info->buf[y][x] = color;
			// info->re_buf = 1;
		}
		// verLine(info, x, drawStart, drawEnd, color);
		draw_floor_ceiling(info, x, drawStart, drawEnd);
		x++;
	}
	mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win,
		info->mlx.map.img_ptr, 0, 0);
}
