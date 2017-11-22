/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:17:15 by dmelehov          #+#    #+#             */
/*   Updated: 2017/10/27 13:25:30 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		ft_get_diff(t_data *data)
{
	RAY->diffy = sqrt(1 + (RAY->dirx * RAY->dirx) / (RAY->diry * RAY->diry));
	RAY->diffx = sqrt(1 + (RAY->diry * RAY->diry) / (RAY->dirx * RAY->dirx));
	if (RAY->diry < 0)
	{
		RAY->disty = (RAY->posy - data->mapy) * RAY->diffy;
		RAY->stepy = -1;
	}
	else
	{
		RAY->disty = (data->mapy + 1.0 - RAY->posy) * RAY->diffy;
		RAY->stepy = 1;
	}
	if (RAY->dirx < 0)
	{
		RAY->distx = (RAY->posx - data->mapx) * RAY->diffx;
		RAY->stepx = -1;
	}
	else
	{
		RAY->distx = (data->mapx + 1.0 - RAY->posx) * RAY->diffx;
		RAY->stepx = 1;
	}
}

void		ft_get_ray(t_data *data, int n)
{
	CAM->relx = 2 * n / (double)LENGHT - 1;
	RAY->posx = CAM->posx;
	RAY->posy = CAM->posy;
	data->mapx = (int)RAY->posx;
	data->mapy = (int)RAY->posy;
	RAY->dirx = CAM->dirx + CAM->plx * CAM->relx;
	RAY->diry = CAM->diry + CAM->ply * CAM->relx;
	data->hit = 0;
	ft_get_diff(data);
}

void		ft_draw_to_image(t_data *data, int coef)
{
	int			i;
	int			j;
	int			color;

	i = 0;
	while (i < HEIGHT)
	{
		color = ft_color(data, i);
		j = (coef * (data->bpp / 8)) + (i * data->size);
		data->img_addr[j] = mlx_get_color_value(data->mlx, color);
		data->img_addr[j + 1] = mlx_get_color_value(data->mlx, color >> 8);
		data->img_addr[j + 2] = mlx_get_color_value(data->mlx, color >> 16);
		i++;
	}
}

void		ft_calc_ray(t_data *data, int i)
{
	if (!data->side)
		CAM->dist = (data->mapx - RAY->posx + (1 - RAY->stepx) / 2) / RAY->dirx;
	else
		CAM->dist = (data->mapy - RAY->posy + (1 - RAY->stepy) / 2) / RAY->diry;
	RAY->len = (int)(HEIGHT / CAM->dist);
	RAY->start = -(RAY->len) / 2 + HEIGHT / 2;
	RAY->end = RAY->len / 2 + HEIGHT / 2;
	if (RAY->end >= HEIGHT)
		RAY->end = HEIGHT - 1;
	if (RAY->start < 0)
		RAY->start = 0;
	ft_draw_to_image(data, i);
}

void		ft_update_data(t_data *data)
{
	int i;

	i = 0;
	while (i < LENGHT)
	{
		ft_get_ray(data, i);
		while (1)
		{
			if (RAY->disty > RAY->distx)
			{
				RAY->distx += RAY->diffx;
				data->mapx += RAY->stepx;
				data->side = 0;
			}
			else
			{
				RAY->disty += RAY->diffy;
				data->mapy += RAY->stepy;
				data->side = 1;
			}
			if (CURPOS != 0 && CURPOS != 3)
				break ;
		}
		ft_calc_ray(data, i++);
	}
}
