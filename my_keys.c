/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:02:46 by dmelehov          #+#    #+#             */
/*   Updated: 2017/10/27 12:07:48 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static	void		ft_vert_move(t_data *data, int i)
{
	double	x;
	double	y;
	double	z;
	double	w;

	y = CAM->posy;
	x = CAM->posx;
	z = CAM->dirx * MOVESPEED * i;
	w = CAM->diry * MOVESPEED * i;
	if ((MAP)[(int)y][(int)(x + z)] == 0
		|| (MAP)[(int)y][(int)(x + z)] == 3)
		CAM->posx += z;
	if ((MAP)[(int)(y + w)][(int)x] == 0
		|| (MAP)[(int)(y + w)][(int)x] == 3)
		CAM->posy += w;
}

static	void		ft_horiz_move(t_data *data, int i)
{
	double	x;
	double	y;
	double	z;
	double	w;

	x = CAM->dirx;
	y = CAM->plx;
	z = cos(0.17 * i);
	w = sin(0.17 * i);
	CAM->dirx = x * z - CAM->diry * w;
	CAM->diry = x * w + CAM->diry * z;
	CAM->plx = y * z - CAM->ply * w;
	CAM->ply = y * w + CAM->ply * z;
}

int					ft_draw_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx, LENGHT, HEIGHT);
	data->img_addr = mlx_get_data_addr(data->img, &(data->bpp),
		&(data->size), &(data->endian));
	ft_update_data(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}

static	void		ft_door(t_data *data)
{
	if ((MAP)[DY][DX] == 2)
		(MAP)[DY][DX] = 3;
	else if ((MAP)[DY][DX] == 3)
		(MAP)[DY][DX] = 2;
}

int					ft_my_keys(int key, t_data *data)
{
	if (key == ESC)
		exit(0);
	if (key == UP)
		ft_vert_move(data, 1);
	if (key == DOWN)
		ft_vert_move(data, -1);
	if (key == LEFT)
		ft_horiz_move(data, 1);
	if (key == RIGHT)
		ft_horiz_move(data, -1);
	if (key == SPACE)
		ft_door(data);
	ft_draw_image(data);
	return (0);
}
